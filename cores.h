#ifndef CORES_H_INCLUDED
#define CORES_H_INCLUDED
#endif

/* IMPLEMENTAR INCLUDES */

/*
* Conjunto de definições de cores seguindo a Tabela ANSI
*/
#define C_RED		"\033[91m"
#define C_GREEN        	"\033[92m"
#define C_ORANGE     	"\033[93m"
#define C_BLUE         	"\033[94m"
#define C_PINK         	"\033[95m"
#define C_CYAN        	"\033[96m"
#define C_WHITE       	"\033[97m"
#define C_BLACK        	"\033[90m"
#define RESTORE       	"\033[00m"

/*
* Função: red (char[])
* Descrição: Imprime uma string na tela, em vermelho
*/
void red (char string[]);

/*
* Função: green (char[])
* Descrição: Imprime uma string na tela, em verde
*/
void green (char string[]);

/*
* Função: orange (char[])
* Descrição: Imprime uma string na tela, em laranja
*/
void orange (char string[]);

/*
* Função: blue (char[])
* Descrição: Imprime uma string na tela, em azul
*/
void blue(char string[]);

/*
* Função: pink (char[])
* Descrição: Imprime uma string na tela, em rosa
*/
void pink(char string[]);

/*
* Função: cyan (char[])
* Descrição: Imprime uma string na tela, em ciano
*/
void cyan(char string[]);

/*
* Função: white (char[])
* Descrição: Imprime uma string na tela, em branco
*/
void white (char string[]);

/*
* Função: black (char[])
* Descrição: Imprime uma string na tela, em preto
*/
void black (char string[]);
