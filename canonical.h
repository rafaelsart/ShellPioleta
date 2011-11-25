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



/**
* Coloca o Terminal em Modo Não-Canônico
*
@return void
*/
void Canonical_setNonCanonicalMode (void);



/**
* Coloca o Terminal em Modo Canônico
*
@return void
*/
void Canonical_setCanonicalMode(void);
