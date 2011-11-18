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
* Função: capturaSigInt (int signum)
* Descrição: * IMPLEMENTAR *
*/
/* REVISAR! */
void Signal_capturaSigInt (int signum) {
	//Variáveis
	pid_t foreJob;
	int aux, estado;
	//Captura o Sinal
	signal(SIGINT,Signal_capturaSigInt);
	//Busca Job em Foreground
	foreJob = Jobs_retornaJobEmForeground(Jobs);
	
	//Não encontrado
	if(foreJob == -1) {
		printf("Nao ha nenhum job em Foreground!");
		//Limpa buffer
		fflush(NULL);
	}
	//Encontrado
	else {
		//Envio do Sinal
		if (kill(foreJob * (-1), SIGINT) == -1) perror("ERRO");
		else {
			//Houve mudança
			if(waitpid(foreJob,&estado, WNOHANG | WUNTRACED)>0) {
				//O processo foi parado
				if (WIFSTOPPED(estado)) Jobs_colocaJobEmBackground(Jobs, foreJob);
				else Jobs_removeJob(&Jobs, foreJob);
			}
		}
	}
	//Limpa buffer
	fflush(NULL);
}

/*
* Função: capturaSigInt (int signum)
* Descrição: * IMPLEMENTAR *
*/
/* REVISAR! */
void Signal_capturaSigTSTP (int signum) {
	//Variáveis
	pid_t foreJob;
	int aux, estado;
	//Captura o Sinal
	signal(SIGTSTP,Signal_capturaSigTSTP);
	//Busca Job em Foreground
	foreJob = Jobs_retornaJobEmForeground(Jobs);
	
	//Não encontrado
	if(foreJob == -1) {
		printf("Nao ha nenhum job em Foreground!");
		//Limpa buffer
		fflush(NULL);
	}
	//Encontrado
	else {
		//Envio do Sinal
		if (kill(foreJob * (-1), SIGTSTP) == -1) perror("ERRO");
		else {
			//Houve mudança
			if(waitpid(foreJob,&estado, WNOHANG | WUNTRACED)>0) {
				//O processo foi parado
				if (WIFSTOPPED(estado)) Jobs_colocaJobEmBackground(Jobs, foreJob);
				else Jobs_removeJob(&Jobs, foreJob);
			}
		}
	}
	//Limpa buffer
	fflush(NULL);
}
