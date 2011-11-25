#ifndef TERMINAL_H_INCLUDED
#define TERMINAL_H_INCLUDED
#endif

//Inclusão de bibliotecas do sistema
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

//Definições do Terminal
#define TERMINAL_TAMANHODIRETORIO 128
#define TERMINAL_TAMANHOPATH 512
#define TERMINAL_TAMANHOUSUARIO 32
#define TERMINAL_NUMLINHAS 128
#define TERMINAL_TAMANHOLINHA 512
#define TERMINAL_TAMANHOPALAVRA 32



/** Variável global Path */
char **Path;



/**
* Insere uma Linha de Comando no Conjunto das Linhas de Comando (Histórico)
* 
@param *LinhaComando Linha de Comando digitada pelo usuário
*
@param **LinhasComando Conjunto das Linhas de Comando (Histórico)
*
@param numLinhasComando Número de Linhas de Comando
*
@return void
*/
void Terminal_insereLinhaNoHistorico (char *LinhaComando, char **LinhasComando, int numLinhasComando);



/** BEGIN TEST
char* compararTab(char *buffer);
END TEST*/



/**
* Processa as Teclas de Navegação de Histórico enviadas pelo usuário durante a composição da Linha de Comando
* 
@param **LinhasComando Conjunto das Linhas de Comando
*
@param *LinhaComando Linha de Comando (a ser modificada)
*
@param *tecla	 Buffer contendo a Tecla capturada
*
@param *contadorTeclas Número de caracteres da Linha de Comando em composição (a ser modificado)
*
@param *linesOver Número de Linhas além da atual (a ser modificado)
*
@param numLinhasComando Número de Linhas de Comando
*
@return void
*/
void Terminal_processaTeclaHistorico (char **LinhasComando, char *LinhaComando, char *tecla, int *contadorTeclas, int *linesOver, int numLinhasComando);



/**
* Processa as Teclas de Comando enviadas pelo usuário durante a composição da Linha de Comando
* 
@param *LinhaComando Linha de Comando digitada pelo usuário até este instante
*
@param *tecla	 Buffer contendo a Tecla capturada
*
@param contadorTeclas Número de caracteres da Linha de Comando em composição
*
@return void
*/
void Terminal_processaTeclaComando (char *LinhaComando, char *tecla, int contadorTeclas);



/**
* Processa a Linha de Comando inserida pelo usuário, no modo Não-Canônico
* 
@param **LinhasComando Conjunto das Linhas de Comando
*
@param numLinhasComando Número de Linhas de Comando
*
@return Linha de Comando processada
*/
char* Terminal_processaLinha (char **LinhasComando, int numLinhasComando);



/**
* Interpreta a Linha de Comando digitada e executa os comandos conforme necessário
* 
@param *LinhaComando Linha de Comando digitada
*
@param **LinhasComando Conjunto de Linhas de Comando (para verificação de '&' da linha anterior)
*
@return void
*/
void Terminal_InterpretaLinhaComando (char *LinhaComando, char **LinhasComando);
