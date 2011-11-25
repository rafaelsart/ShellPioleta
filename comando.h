#ifndef COMANDO_H_INCLUDED
#define COMANDO_H_INCLUDED
#endif

//Inclusão de bibliotecas do sistema
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



/*
* Função		: Comando_isBuiltIn (char**)
* Descrição		: Identifica se a Linha de Comando contém um comando Built-In
* Parâmetros:
* char **Parametro	: Linha de Comando convertida em um vetor para cada palavra
* Retorno		: 1 se o comando for Built-In, e 0 em caso contrário
*/
int Comando_isBuiltIn (char **Parametro);



/*
* Função		: Comando_rodaBuiltIn (char**)
* Descrição		: Executa um comando Built-In
* Parâmetros:
* char **Parametro	: Linha de Comando convertida em um vetor para cada palavra
* Retorno		: void
*/
void Comando_rodaBuiltIn (char **Parametro);



/*
* Função		: Comando_rodaBuiltIn (char**, int, int)
* Descrição		: Executa comandos do Sistema (com exceção dos Built-In)
* Parâmetros:
* char **Parametro	: Linha de Comando convertida em um vetor para cada palavra
* int numParametros	: Número de parâmetros (afim de facilitar a manipulação dos parâmetros
* int status		: Modo de Execução do Comando
* Retorno		: void
*/
void Comando_rodaLinhaComando (char **Parametro, int numParametros, int status);
