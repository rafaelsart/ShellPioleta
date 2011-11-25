#ifndef CANONICAL_H_INCLUDED
#define CANONICAL_H_INCLUDED
#endif

//Inclusão de bibliotecas do sistema
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>

//Estrutura global
struct termios oldtio;



/*
* Função	: Canonical_setNonCanonicalMode (void)
* Descrição	: Coloca o Terminal em Modo Não-Canônico
* Parâmetros	: void
* Retorno	: void
*/
void Canonical_setNonCanonicalMode (void);



/*
* Função	: Canonical_setCanonicalMode (void)
* Descrição	: Coloca o Terminal em Modo Canônico
* Parâmetros	: void
* Retorno	: void
*/
void Canonical_setCanonicalMode(void);
