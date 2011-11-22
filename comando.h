#ifndef COMANDO_H_INCLUDED
#define COMANDO_H_INCLUDED
#endif

//Inclusão de bibliotecas do sistema
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
* Função: Comando_isBuiltIn (char**)
* Descrição: Identifica se a Linha de Comando contém um comando Built-In
*/
int Comando_isBuiltIn (char **Parametro);

/*
* Função: Comando_rodaBuiltIn (char**)
* Descrição: Roda comandos Built-In, definidos na função Comando_isBuiltIn
*/
void Comando_rodaBuiltIn (char **Parametro);

/*
* Função: Comando_rodaLinhaComando (char*, char**, int, int)
* Descrição: Roda os comandos não built-in
*/
int Comando_rodaLinhaComando (char **Parametro, int status);
