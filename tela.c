//Inclusão de bibliotecas do sistema
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

//Inclusão de bibliotecas próprias
#include "tela.h"
#include "erros.h"
#include "colors.h"
#include "terminal.h"
#include "alocacao.h"

/*
* Função: Tela_flushKeys(char*)
* Descrição: Limpa o buffer reservado para determinadas teclas
*/
void Tela_flushKeys(char *tecla) {
	tecla[0] = tecla[1] = tecla[2] = 0;
}

/*
* Função: Tela_apagaCaracteres(int)
* Descrição: Apaga caracteres do buffer impresso em tela
*/
void Tela_apagaCaracteres(int numCaracteres) {
	//Variáveis
	int i;
	//Rotina
	for(i = 0; i < numCaracteres; i++) printf("\b \b");
}

/*
* Função: Tela_imprimeShell(void)
* Descrição: Imprime em vermelho o nome de usuário e o diretório atual
*/
void Tela_imprimeShell(void) {
	//Variáveis
	char *Usuario, *Diretorio, *shellLine;
		
	//Variável de ambiente: Usuário
	Usuario = Alocacao_alocaVetor(strlen(getenv("USER")));
	Usuario = strdup(getenv("USER"));

	//Diretório
	Diretorio = Alocacao_alocaVetor(TERMINAL_TAMANHODIRETORIO);
	getcwd(Diretorio,TERMINAL_TAMANHODIRETORIO*sizeof(char));

	//ShellLine	
	shellLine = Alocacao_alocaVetor(strlen(Usuario)+strlen(Diretorio)+2);
	sprintf(shellLine,"%s:~%s", Usuario, Diretorio);	
	//Imprime diretório atual em vermelho		
	Color_red(shellLine);
}
