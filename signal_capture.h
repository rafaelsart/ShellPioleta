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



/**
* Captura o sinal de Interrupção Assistida (SIGTSTP) e trata-o
* 
@param signum ID do processo que recebeu o sinal
*
@param *info Informações detalhadas do processo que recebeu o sinal
*
@param *context Não utilizado
*
@return void
*/
void Signal_capturaSigTSTP (int signum, siginfo_t *info, void *context);



/**
* Captura o sinal de Alteração de um Processo-Filho (SIGCHLD) e trata-o
* 
@param signum ID do processo que recebeu o sinal
*
@param *info Informações detalhadas do processo que recebeu o sinal
*
@param *context Não utilizado
*
@return void
*/
void Signal_capturaSigCHLD (int signum, siginfo_t *info, void *context);



/**
* Efetua a instalação dos Handlers dos sinais desejados
*
@return void
*/
void Signal_Instalacao(void);
