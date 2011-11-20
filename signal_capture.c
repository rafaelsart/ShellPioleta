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

/*
* Função: capturaSigTSTP (int signum)
* Descrição: * Captura o signal SIGTSTP *
*/
void Signal_capturaSigTSTP (int signum) {
	//Variáveis
	Job* jobAux;

	//Aloca um elemento struct job
	jobAux = (Job*) malloc(sizeof(struct job));

	//Busca Job em Foreground
	jobAux = Jobs_retornaJobEmForeground(Jobs);
	
	//Não encontrado
	if(jobAux == NULL) {
		printf("Nao ha nenhum job em Foreground!");
	}

	//Encontrado
	else {
		jobAux->status = FOREGROUND;

		if(jobAux->statusExecucao != TERMINOU) {
			//Pausa a Job
			jobAux->statusExecucao = PAUSADO;
			//Mata e envia sinal
			kill(jobAux->pid, SIGSTOP);
		}
	}
}

/*
* Função: capturaSigCHLD (int signum)
* Descrição: * IMPLEMENTAR *
*/
void Signal_capturaSigCHLD (int signum, siginfo_t *info) {
	//Variáveis
	//pid_t foreJob;
	//int estado;
	
	//Coloca em espera
	//waitpid(IMPLEMENTAR, &estado, WUNTRACED | WCONTINUED);

	//IMPLEMENTAR
	//update_status(IMPLEMENTAR)
}
