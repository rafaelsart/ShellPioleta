#ifndef ALOCACAO_H_INCLUDED
#define ALOCACAO_H_INCLUDED
#endif

//Inclusão de bibliotecas do sistema
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
* Função: Alocacao_alocaVetor (int)
* Descrição: Dado um tamanho inteiro, aloca um vetor
*/
char* Alocacao_alocaVetor (int tamanhoVetor);

/*
* Função: Alocacao_alocaMatriz (int)
* Descrição: Dado dois tamanhos inteiros, aloca uma matriz e cada um de seus vetores
*/
char** Alocacao_alocaMatriz (int numLinhas, int tamanhoLinha);
