#ifndef TELA_H_INCLUDED
#define TELA_H_INCLUDED
#endif

//Inclusão de bibliotecas do sistema
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
* Função		: Tela_flushKeys (char*)
* Descrição		: Limpa o buffer reservado para determinadas teclas
* Parâmetros:
* char *tecla		: Vetor contendo o buffer das teclas pré-determinadas
* Retorno		: void
*/
void Tela_flushKeys(char *tecla);



/*
* Função		: Tela_apagaCaracteres (int)
* Descrição		: Apaga um número desejado de caracteres na tela
* Parâmetros:
* int numCaracteres	: Número de teclas a serem apagadas
* Retorno		: void
*/
void Tela_apagaCaracteres(int numCaracteres);



/*
* Função		: Tela_apagaLinha (void)
* Descrição		: Apaga uma linha inteira da tela
* Parâmetros		: void
* Retorno		: void
*/
void Tela_apagaLinha(void);



/*
* Função		: Tela_limpaTela (void)
* Descrição		: Limpa a tela do Terminal
* Parâmetros		: void
* Retorno		: void
*/
void Tela_limpaTela(void);



/*
* Função		: Tela_imprimeShell (void)
* Descrição		: Imprime a Shell
* Parâmetros		: void
* Retorno		: void
*/
void Tela_imprimeShell(void);
