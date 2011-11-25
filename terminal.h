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



/* Variável global Path */
char **Path;



/* 
* Função		: Terminal_insereLinhaNoHistorico (char*, char**, int)
* Descrição		: Insere uma Linha de Comando no Conjunto das Linhas de Comando (Histórico)
* Parâmetros:
* char *LinhaComando	: Linha de Comando digitada pelo usuário
* char **LinhasComando	: Conjunto das Linhas de Comando (Histórico)
* int numLinhasComando	: Número de Linhas de Comando
*/
int Terminal_insereLinhaNoHistorico (char *LinhaComando, char **LinhasComando, int numLinhasComando);



/* BEGIN TEST
char* compararTab(char *buffer);
END TEST*/



/*
* Função		: Terminal_processaTeclaHistorico (char**, char*, char*, int*, int*, int)
* Descrição		: Processa as Teclas de Navegação de Histórico enviadas pelo usuário durante a composição da Linha de Comando
* Parâmetros:
* char **LinhasComando	: Conjunto das Linhas de Comando
* char *LinhaComando	: Linha de Comando (a ser modificada)
* char *tecla		: Buffer contendo a Tecla capturada
* int *contadorTeclas	: Número de caracteres da Linha de Comando em composição (a ser modificado)
* int *linesOver	: Número de Linhas além da atual (a ser modificado)
* int numLinhasComando	: Número de Linhas de Comando
* Retorno		: void
*/
void Terminal_processaTeclaHistorico (char **LinhasComando, char *LinhaComando, char *tecla, int *contadorTeclas, int *linesOver, int numLinhasComando);



/*
* Função		: Terminal_processaTeclaComando (char*, char*, int)
* Descrição		: Processa as Teclas de Comando enviadas pelo usuário durante a composição da Linha de Comando
* Parâmetros:
* char *LinhaComando	: Linha de Comando digitada pelo usuário até este instante
* char *tecla		: Buffer contendo a Tecla capturada
* int contadorTeclas	: Número de caracteres da Linha de Comando em composição
* Retorno		: void
*/
void Terminal_processaTeclaComando (char *LinhaComando, char *tecla, int contadorTeclas);



/*
* Função		: Terminal_processaLinha (char*, int)
* Descrição		: Processa a Linha de Comando inserida pelo usuário, no modo Não-Canônico
* Parâmetros:
* char **LinhasComando	: Conjunto das Linhas de Comando
* int numLinhasComando	: Número de Linhas de Comando
* Retorno		: Linha de Comando processada
*/
char* Terminal_processaLinha (char **LinhasComando, int numLinhasComando);



/*
* Função		: Terminal_InterpretaLinhaComando (char*, char**)
* Descrição		: Interpreta a Linha de Comando digitada e executa os comandos conforme necessário
* Parâmetros:
* char *LinhaComando	: Linha de Comando digitada
* char **LinhasComando	: Conjunto de Linhas de Comando (para verificação de '&' da linha anterior)
* Retorno		: void
*/
void Terminal_InterpretaLinhaComando (char *LinhaComando, char **LinhasComando);
