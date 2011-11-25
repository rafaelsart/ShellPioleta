#ifndef ALOCACAO_H_INCLUDED
#define ALOCACAO_H_INCLUDED
#endif

//Inclusão de bibliotecas do sistema
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



/**
* Aloca um vetor de tamanho pré-determinado e o retorna em caso de sucesso.
* 
@param tamanhoVetor Tamanho do vetor a ser alocado
*
@return Vetor alocado em caso de sucesso, NULO em caso contrário
*/
char* Alocacao_alocaVetor (int tamanhoVetor);



/**
* Aloca uma matriz de tamanho pré-determinado e a retorna em caso de sucesso.
* 
@param numLinhas Número de linhas da matriz (primeira dimensão)
*
@param tamanhoLinha Tamanho da linha da matriz (segunda dimensão)
*
@return Vetor alocado em caso de sucesso, NULO em caso contrário
*/
char** Alocacao_alocaMatriz (int numLinhas, int tamanhoLinha);
