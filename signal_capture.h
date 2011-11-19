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
* Função: capturaSigTSTP (int signum)
* Descrição: * IMPLEMENTAR *
*/
void Signal_capturaSigTSTP (int signum);

/*
* Função: capturaSigCHLD (int signum, siginfo_t *info)
* Descrição: * IMPLEMENTAR *
*/
void Signal_capturaSigCHLD (int signum, siginfo_t *info);
