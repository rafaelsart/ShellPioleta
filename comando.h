#ifndef COMANDO_H_INCLUDED
#define COMANDO_H_INCLUDED
#endif

//Inclusão de bibliotecas do sistema
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



/**
* Identifica se a Linha de Comando contém um comando Built-In
* 
@param **Parametro Linha de Comando convertida em um vetor para cada palavra
*
@return 1 se o comando for Built-In, e 0 em caso contrário
*/
int Comando_isBuiltIn (char **Parametro);



/**
* Executa um comando Built-In
* 
@param **Parametro Linha de Comando convertida em um vetor para cada palavra
*
@return void
*/
void Comando_rodaBuiltIn (char **Parametro);



/**
* Executa comandos do Sistema (com exceção dos Built-In)
* 
@param **Parametro Linha de Comando convertida em um vetor para cada palavra
*
@param numParametros Número de parâmetros (afim de facilitar a manipulação dos parâmetros
*
@param status Modo de Execução do Comando
*
@return void
*/
void Comando_rodaLinhaComando (char **Parametro, int numParametros, int status);
