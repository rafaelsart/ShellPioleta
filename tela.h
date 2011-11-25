#ifndef TELA_H_INCLUDED
#define TELA_H_INCLUDED
#endif

//Inclusão de bibliotecas do sistema
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
* Limpa o buffer reservado para determinadas teclas
* 
@param *tecla	 Vetor contendo o buffer das teclas pré-determinadas
@return void
*/
void Tela_flushKeys(char *tecla);



/**
* Apaga um número desejado de caracteres na tela
* 
@param numCaracteres Número de teclas a serem apagadas
*
@return void
*/
void Tela_apagaCaracteres(int numCaracteres);



/**
* Apaga uma linha inteira da tela
* 
@return void
*/
void Tela_apagaLinha(void);



/**
* Limpa a tela do Terminal
* 
@return void
*/
void Tela_limpaTela(void);



/**
* Imprime a Shell
* 
@return void
*/
void Tela_imprimeShell(void);
