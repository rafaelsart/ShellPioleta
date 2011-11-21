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
* Função: capturaSigTSTP (int, siginfo_t*, void)
* Descrição: * IMPLEMENTAR *
*/
void Signal_capturaSigTSTP (int signum, siginfo_t *info, void *context);

/*
* Função: capturaSigCHLD (int, siginfo_t*, void)
* Descrição: * IMPLEMENTAR *
*/
void Signal_capturaSigCHLD (int signum, siginfo_t *info, void *context);

/*
* Função: Signal_instalacao (void)
* Descrição: Efetua a instalação dos handlers
*/
void Signal_Instalacao(void);
