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
* Função: capturaSigInt (int signum)
* Descrição: * IMPLEMENTAR *
*/
/* REVISAR! */
void Signal_capturaSigInt (int signum);

/*
* Função: capturaSigTSTP (int signum)
* Descrição: * IMPLEMENTAR *
*/
/* REVISAR! */
void Signal_capturaSigTSTP (int signum);

/*
* Função: capturaSigCHLD (int signum)
* Descrição: * IMPLEMENTAR *
*/
/* REVISAR! */
void Signal_capturaSigCHLD (int signum);
