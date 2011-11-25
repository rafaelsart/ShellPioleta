//Inclusão de bibliotecas do sistema
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#include <termios.h>
#include <errno.h>
#include <sys/wait.h>

//Inclusão de bibliotecas próprias
#include "jobs.h"
#include "terminal.h"
#include "signal_capture.h"
#include "tela.h"

//Estrutura		: Sigactions correspondentes ao SIGTSTP
static struct sigaction TSTP;
static struct sigaction oldTSTP;

//Estrutura		: Sigactions correspondentes ao SIGCHLD
static struct sigaction CHLD;
static struct sigaction oldCHLD;

/*
* Função		: Signal_capturaSigTSTP (int, siginfo_t, void*)
* Descrição		: Captura o sinal de Interrupção Assistida (SIGTSTP) e trata-o
* Parâmetros:
* int signum		: ID do processo que recebeu o sinal
* siginfo_t *info	: Informações detalhadas do processo que recebeu o sinal
* void *context		: Não utilizado
* Retorno		: void
*/
void Signal_capturaSigTSTP (int signum, siginfo_t *info, void *context) {
	//Variáveis
	Job *jobAux;

	//Busca Job em FOREGROUND
	jobAux = Jobs_retornaJobEmForeground(Jobs);

	//Não encontrado
	if(jobAux == NULL) printf("Nenhum job em foreground\n!");

	//Encontrado
	else {
		//Coloca Job em BACKGROUND
		Jobs_colocaJobEmBackground(&Jobs,jobAux->pid);
		
		//Pausa se a execução não terminou
		if(jobAux->statusExecucao != TERMINOU) {
			//Pausa a Job
			jobAux->statusExecucao = PAUSADO;
			//Mata e envia sinal
			kill(jobAux->pid, SIGSTOP);
		}
	}
}

/*
* Função		: Signal_capturaSigCHLD (int, siginfo_t, void*)
* Descrição		: Captura o sinal de Alteração de um Processo-Filho (SIGCHLD) e trata-o
* Parâmetros:
* int signum		: ID do processo que recebeu o sinal
* siginfo_t *info	: Informações detalhadas do processo que recebeu o sinal
* void *context		: Não utilizado
* Retorno		: void
*/
void Signal_capturaSigCHLD (int signum, siginfo_t *info, void *context) {
	//Variáveis	
	int estado;
	Job *jobAux;

	//Aguarda o filho enviar algum sinal
	waitpid(-1*(info->si_pid),&estado,WUNTRACED | WCONTINUED | WNOHANG);

	//Busca PID
	jobAux = Jobs_retornaJobComPID(&Jobs,info->si_pid);

	//Aguarda o filho enviar um SIGNAL
	waitpid(-1*(info->si_pid),&estado,WUNTRACED | WCONTINUED | WNOHANG);

	//A Job está PARADA (Comando digitado: Ctrl+Z)
	if (WIFSTOPPED(estado)) {
		//Atualiza status da Job
		jobAux->status = BACKGROUND;
		jobAux->statusExecucao = PAUSADO;
	}
	//A Job está RODANDO (Comando digitado: fg)
	else if (WIFCONTINUED(estado)) {
		//Atualiza status da Job
		jobAux->statusExecucao = RODANDO;
		jobAux->status = FOREGROUND;

		//Chama um novo wait que não retornará imediatamente
		waitpid(-1*(info->si_pid),&estado,WUNTRACED | WCONTINUED);
		
	}
	//A Job TERMINOU (Programa encerrado)
	else {
		//Atualiza status da Job
		jobAux->statusExecucao = TERMINOU;
		jobAux->status = BACKGROUND;
	}
}

/*
* Função	: Signal_instalacao (void)
* Descrição	: Efetua a instalação dos Handlers dos sinais desejados
* Parâmetros	: void
* Retorno	: void
*/
void Signal_Instalacao(void) {
	//Configura handler TSTP
	sigemptyset(&TSTP.sa_mask);
	TSTP.sa_flags = SA_SIGINFO;
	TSTP.sa_sigaction = Signal_capturaSigTSTP;

	//Instala handler TSTP
	sigaction(SIGTSTP, &TSTP, &oldTSTP);

	//Configura handler CHLD
	sigemptyset(&CHLD.sa_mask);
	CHLD.sa_flags = SA_SIGINFO;
	CHLD.sa_sigaction = Signal_capturaSigCHLD;

	//Instala handler CHLD
	sigaction(SIGCHLD, &CHLD, &oldCHLD);
}
