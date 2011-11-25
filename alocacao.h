#ifndef ALOCACAO_H_INCLUDED
#define ALOCACAO_H_INCLUDED
#endif

//Inclusão de bibliotecas do sistema
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



/*
* Função		: Alocacao_alocaVetor (int)
* Descrição		: Aloca um vetor de tamanho pré-determinado e o retorna em caso de sucesso.
* Parâmetros:
* int tamanhoVetor	: Tamanho do vetor a ser alocado
* Retorno		: Vetor alocado em caso de sucesso, NULO em caso contrário
*/
char* Alocacao_alocaVetor (int tamanhoVetor);



/*
* Função		: Alocacao_alocaMatriz (int)
* Descrição		: Aloca uma matriz de tamanho pré-determinado e a retorna em caso de sucesso.
* Parâmetros:
* int numLinhas		: Número de linhas da matriz (primeira dimensão)
* int tamanhoLinha	: Tamanho da linha da matriz (segunda dimensão)
* Retorno		: Vetor alocado em caso de sucesso, NULO em caso contrário
*/
char** Alocacao_alocaMatriz (int numLinhas, int tamanhoLinha);
