//Inclusão de bibliotecas do sistema
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Inclusão de bibliotecas próprias
#include "tela.h"
#include "erros.h"
#include "colors.h"

/*
* Função: flushKeys(char)
* Descrição: Limpa o buffer reservado para determinadas teclas
*/
void Tela_flushKeys(char *tecla) {
	tecla[0] = tecla[1] = tecla[2] = 0;
}

/*
* Função: Tela_apagaCaracteres(int)
* Descrição: Apaga conjuntos de caracteres do buffer impresso em tela
*/
void Tela_apagaCaracteres(int numCaracteres) {
	//Variáveis
	int i;
	//Rotina
	for(i = 0; i < numCaracteres; i++) printf("\b \b");
}

/*
* Função: Terminal_imprimeShell(char*, char*)
* Descrição: Imprime em vermelho o nome de usuário e o diretório atual
*/
void Tela_imprimeShell(char* Usuario, char* Diretorio) {
	char* shellLine = (char*) malloc ((strlen(Usuario)+strlen(Diretorio)+2) * sizeof(char));
	sprintf(shellLine,"%s:~%s", Usuario, Diretorio);	
	//Imprime diretório atual em vermelho		
	Color_red(shellLine);
}
