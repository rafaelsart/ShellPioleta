#ifndef COLORS_H_INCLUDED
#define COLORS_H_INCLUDED
#endif	

//Inclusão de bibliotecas do sistema
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Definições de Cores seguindo a tabela ANSI
#define C_RED		"\033[91m"
#define C_GREEN        	"\033[92m"
#define C_ORANGE     	"\033[93m"
#define C_BLUE         	"\033[94m"
#define C_PINK         	"\033[95m"
#define C_CYAN        	"\033[96m"
#define C_WHITE       	"\033[97m"
#define C_BLACK        	"\033[90m"
#define RESTORE       	"\033[00m"



/**
* Imprime uma string na tela, em vermelho
* 
@param string[] String a ser impressa
*
@return void
*/
void Color_red (char string[]);



/**
* Imprime uma string na tela, em verde
* 
@param string[] String a ser impressa
*
@return void
*/
void Color_green (char string[]);



/**
* Imprime uma string na tela, em laranja
* 
@param string[] String a ser impressa
*
@return void
*/
void Color_orange (char string[]);



/**
* Imprime uma string na tela, em azul
* 
@param string[] String a ser impressa
*
@return void
*/
void Color_blue(char string[]);



/**
* Imprime uma string na tela, em rosa
* 
@param string[] String a ser impressa
*
@return void
*/
void Color_pink(char string[]);



/**
* Imprime uma string na tela, em ciano
* 
@param string[] String a ser impressa
*
@return void
*/
void Color_cyan(char string[]);



/**
* Imprime uma string na tela, em branco
* 
@param string[] String a ser impressa
*
@return void
*/
void Color_white (char string[]);



/**
* Imprime uma string na tela, em preto
* 
@param string[] String a ser impressa
*
@return void
*/
void Color_black (char string[]);
