/* IMPLEMENTAR INCLUDES */

/*
* Função: red (char[])
* Descrição: Imprime uma string na tela, em vermelho
*/
void red (char string[]) {
	printf("%s%s $%s ", C_RED, string, RESTORE);
}

/*
* Função: green (char[])
* Descrição: Imprime uma string na tela, em verde
*/
void green (char string[]) {
	printf("%s%s $%s ", C_GREEN, string, RESTORE);
}

/*
* Função: orange (char[])
* Descrição: Imprime uma string na tela, em laranja
*/
void orange (char string[]) {
	printf("%s%s $%s ", C_ORANGE , string, RESTORE);
}

/*
* Função: blue (char[])
* Descrição: Imprime uma string na tela, em azul
*/
void blue(char string[]) {
	printf("%s%s $%s ", C_BLUE, string, RESTORE);
}

/*
* Função: pink (char[])
* Descrição: Imprime uma string na tela, em rosa
*/
void pink(char string[]) { 
	printf("%s%s $%s ", C_PINK, string, RESTORE);
}

/*
* Função: cyan (char[])
* Descrição: Imprime uma string na tela, em ciano
*/
void cyan(char string[]) {
	printf("%s%s $%s ", C_CYAN, string, RESTORE);
}

/*
* Função: white (char[])
* Descrição: Imprime uma string na tela, em branco
*/
void white (char string[]) { 
	printf("%s%s $%s ", C_WHITE, string, RESTORE);
}

/*
* Função: black (char[])
* Descrição: Imprime uma string na tela, em preto
*/
void black (char string[]) {
	printf("%s%s $%s  ", C_BLACK, string, RESTORE);
}
