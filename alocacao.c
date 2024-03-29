//Inclusão de bibliotecas do sistema
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Inclusão de bibliotecas próprias
#include "alocacao.h"

char* Alocacao_alocaVetor (int tamanhoVetor) {
	//Variáveis
	char *vetor;
	//Aloca o vetor
	vetor = (char*) malloc(sizeof(char)*tamanhoVetor);
	//Vetor não foi alocado
	if(vetor == NULL) {
		/* ERRO */
	}
	//Retorno
	return vetor;
}

char** Alocacao_alocaMatriz (int numLinhas, int tamanhoLinha) {
	//Variáveis
	char **matriz;
	int iLinha;
	//Aloca a matriz
	matriz = (char**) malloc(sizeof(char*) * numLinhas);
	//Matriz não foi alocada
	if(matriz == NULL) {
		/* ERRO_NAO_ALOCADO */
	}
	//Aloca vetores
	else {
		//Aloca cada vetor da matriz
		for(iLinha = 0; iLinha < numLinhas; iLinha++) {
			matriz[iLinha] = (char*) malloc(sizeof(char) * tamanhoLinha);
			//Vetor não foi alocado
			if(matriz[iLinha] == NULL){
				/* ERRO_NAO_ALOCADO */
			}
		}
	}
	//Retorno
	return matriz;	
}
