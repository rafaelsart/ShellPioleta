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
#include "signal_capture.h"

//Sigactions TSTP
static struct sigaction TSTP;
static struct sigaction oldTSTP;

//Sigactions CHLD
static struct sigaction CHLD;
static struct sigaction oldCHLD;

/*
* Função: capturaSigTSTP (int)
* Descrição: Captura o signal SIGTSTP
*/
void Signal_capturaSigTSTP (int signum, siginfo_t *info, void *context) {
	//Variáveis
	Job* jobAux;

	//Aloca um elemento struct job
	jobAux = (Job*) malloc(sizeof(struct job));

	//Busca Job em Foreground
	jobAux = Jobs_retornaJobEmForeground(Jobs);
	
	//Não encontrado
	if(jobAux == NULL) printf("Nenhum job em foreground\n!");

	//Encontrado
	else {
		//Define status para background
		jobAux->status = BACKGROUND;
		
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
* Função: capturaSigCHLD (int, siginfo_t)
* Descrição: Captura o signal SIGCHLD
*/
void Signal_capturaSigCHLD (int signum, siginfo_t *info, void *context) {
	//Variáveis	
	int estado;
	Job *jobAux;
	
	//Coloca em espera
	waitpid(info->si_pid, &estado, WUNTRACED | WCONTINUED);

	//Busca PID
	jobAux = Jobs_retornaJobComPID(&Jobs,info->si_pid);

	if (WIFSTOPPED(estado)) {
		jobAux->status = BACKGROUND;
		jobAux->statusExecucao = PAUSADO;
	}
	else if (WIFCONTINUED(estado)) jobAux->statusExecucao = RODANDO;
	else {
		jobAux->status = BACKGROUND;
		jobAux->statusExecucao = TERMINOU;
	}
}

/*
* Função: Signal_instalacao (void)
* Descrição: Efetua a instalação dos handlers
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

/**
 * $name children_sig_setup;
 * $proto void children_sig_setup(void);
 *
 * Restaura os handlers anteriores aa execucao de sig_setup(). Para ser
 * usada nos processos filhos do shell.
 */

void Signal_InstalacaoFilhos(void)
{
    sigaction(SIGTSTP, &oldTSTP, NULL);
    sigaction(SIGCHLD, &oldCHLD, NULL);
}
