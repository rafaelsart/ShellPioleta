#ifndef SIGNAL_CAPTURE_H_INCLUDED
#define SIGNAL_CAPTURE_H_INCLUDED
#endif

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



/*
* Função		: Signal_capturaSigTSTP (int, siginfo_t, void*)
* Descrição		: Captura o sinal de Interrupção Assistida (SIGTSTP) e trata-o
* Parâmetros:
* int signum		: ID do processo que recebeu o sinal
* siginfo_t *info	: Informações detalhadas do processo que recebeu o sinal
* void *context		: Não utilizado
* Retorno		: void
*/
void Signal_capturaSigTSTP (int signum, siginfo_t *info, void *context);



/*
* Função		: Signal_capturaSigCHLD (int, siginfo_t, void*)
* Descrição		: Captura o sinal de Alteração de um Processo-Filho (SIGCHLD) e trata-o
* Parâmetros:
* int signum		: ID do processo que recebeu o sinal
* siginfo_t *info	: Informações detalhadas do processo que recebeu o sinal
* void *context		: Não utilizado
* Retorno		: void
*/
void Signal_capturaSigCHLD (int signum, siginfo_t *info, void *context);



/*
* Função	: Signal_instalacao (void)
* Descrição	: Efetua a instalação dos Handlers dos sinais desejados
* Parâmetros	: void
* Retorno	: void
*/
void Signal_Instalacao(void);
