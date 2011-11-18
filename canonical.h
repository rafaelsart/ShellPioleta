#ifndef CANONICAL_H_INCLUDED
#define CANONICAL_H_INCLUDED
#endif

//Inclusão de bibliotecas do sistema
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>

struct termios oldtio;

/*
* Função: setNonCanonicalMode (void)
* Descrição: Ativa o modo não-canônico
*/
void Canonical_setNonCanonicalMode (void);

/*
* Função: setCanonicalMode (void)
* Descrição: Ativa o modo canônico
*/
void Canonical_setCanonicalMode(void);
