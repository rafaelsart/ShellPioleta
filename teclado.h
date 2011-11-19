#ifndef TECLADO_H_INCLUDED
#define TECLADO_H_INCLUDED
#endif

//Inclusão de bibliotecas do sistema
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>

/*
* Conjunto de definições de Terminal
*/
#define TERMINAL_NUMLINHAS 128
#define TERMINAL_TAMANHOLINHA 1024
#define TERMINAL_TAMANHOPALAVRA 32



/*
* Função: flushKeys(char)
* Descrição: Limpa o buffer reservado para determinadas teclas
*/
void flushKeys(char *tecla);

/*
* Função: Terminal_apagaCaracteres(int)
* Descrição: Apaga conjuntos de caracteres do buffer impresso em tela
*/
void Terminal_apagaCaracteres(int numCaracteres);

/*
* Função: Terminal_processaLinha (char*, char**, int)
* Descrição: Lê e controla a Linha de Comando, de modo não-canônico
*/
char* Terminal_processaLinha;


