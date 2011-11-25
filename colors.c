//Inclusão de bibliotecas do sistema
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Inclusão de bibliotecas próprias
#include "colors.h"

/*
* Função	: Color_red (char[])
* Descrição	: Imprime uma string na tela, em vermelho
* Parâmetros:
* char string[]	: String a ser impressa
* Retorno	: void
*/
void Color_red (char string[]) {
	printf("%s%s $%s ", C_RED, string, RESTORE);
}

/*
* Função	: Color_red (char[])
* Descrição	: Imprime uma string na tela, em verde
* Parâmetros:
* char string[]	: String a ser impressa
* Retorno	: void
*/
void Color_green (char string[]) {
	printf("%s%s $%s ", C_GREEN, string, RESTORE);
}

/*
* Função	: Color_red (char[])
* Descrição	: Imprime uma string na tela, em laranja
* Parâmetros:
* char string[]	: String a ser impressa
* Retorno	: void
*/
void Color_orange (char string[]) {
	printf("%s%s $%s ", C_ORANGE , string, RESTORE);
}

/*
* Função	: Color_red (char[])
* Descrição	: Imprime uma string na tela, em azul
* Parâmetros:
* char string[]	: String a ser impressa
* Retorno	: void
*/
void Color_blue(char string[]) {
	printf("%s%s $%s ", C_BLUE, string, RESTORE);
}

/*
* Função	: Color_red (char[])
* Descrição	: Imprime uma string na tela, em rosa
* Parâmetros:
* char string[]	: String a ser impressa
* Retorno	: void
*/
void Color_pink(char string[]) { 
	printf("%s%s $%s ", C_PINK, string, RESTORE);
}

/*
* Função	: Color_red (char[])
* Descrição	: Imprime uma string na tela, em ciano
* Parâmetros:
* char string[]	: String a ser impressa
* Retorno	: void
*/
void Color_cyan(char string[]) {
	printf("%s%s $%s ", C_CYAN, string, RESTORE);
}

/*
* Função	: Color_red (char[])
* Descrição	: Imprime uma string na tela, em branco
* Parâmetros:
* char string[]	: String a ser impressa
* Retorno	: void
*/
void Color_white (char string[]) { 
	printf("%s%s $%s ", C_WHITE, string, RESTORE);
}

/*
* Função	: Color_red (char[])
* Descrição	: Imprime uma string na tela, em preto
* Parâmetros:
* char string[]	: String a ser impressa
* Retorno	: void
*/
void Color_black (char string[]) {
	printf("%s%s $%s  ", C_BLACK, string, RESTORE);
}
