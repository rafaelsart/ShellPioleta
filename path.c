//Inclusão de bibliotecas do sistema
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

//Inclusão de bibliotecas próprias
#include "erros.h"
#include "alocacao.h"
#include "path.h"

/*
* Função: Path_recuperaCaminho (PathHeader*, char)
* Descrição: Dado uma string alocada, procura o Current Working Directory e salva cada diretório em um elemento da Matriz
*/
void Path_recuperaCaminho (PathHeader *ListaPath) {
	//Variáveis	
	char *tokenPath;
	char *DiretorioAtual;
	
	//Aloca Diretório Atual
	DiretorioAtual = Alocacao_alocaVetor(PATH_NUMDIR*PATH_TAMANHO);

	//Alocado com sucesso
	if(DiretorioAtual != NULL) {
		//Recupera o diretório atual
		DiretorioAtual = getcwd(DiretorioAtual, PATH_NUMDIR*PATH_TAMANHO);
		printf("OIII %s\n", DiretorioAtual);
		//Quebra o PATH em diretórios
		tokenPath = (char*) strtok(DiretorioAtual, "/");

		//Rotina de split
		while(tokenPath != NULL) {
			//Salva path
			strcpy(ListaPath->FullPath[ListaPath->numPaths],tokenPath);

			//Percorre o token
			tokenPath = (char*) strtok(NULL, "/");

			//Incrementa o número de paths
			ListaPath->numPaths++;
		}
		//Libera memória alocada
		free(tokenPath);
	}
	//Não-alocado
	else {
		//ERRO_NAO_ALOCADO
	}
}

/*
* Função: Path_imprimeCaminho (PathHeader)
* Descrição: Imprime todos diretórios da Matriz
*/
char* Path_imprimeCaminho (PathHeader ListaPath) {
	//Variáveis
	int iContador;
	char *DiretorioAtual;

	//Aloca Diretório Atual
	DiretorioAtual = Alocacao_alocaVetor(PATH_NUMDIR*PATH_TAMANHO);
	
	//Alocado com sucesso
	if(DiretorioAtual != NULL) {
		//Inicializa DiretorioAtual
		strcpy(DiretorioAtual,"");

		//Rotina
		for(iContador=0;iContador<ListaPath.numPaths;iContador++) {
			strcat(DiretorioAtual,"/");
			strcat(DiretorioAtual,ListaPath.FullPath[iContador]);
		}
	}

	//Não-alocado
	else {
		//ERRO_NAO_ALOCADO
	}

	//Retorno
	return DiretorioAtual;
}
