#ifndef PATH_H_INCLUDED
#define PATH_H_INCLUDED
#endif

//Inclusão de bibliotecas do sistema
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
* Conjunto de definições de PATH
*/
#define PATH_TAMANHO 128
#define PATH_NUMDIR 16

/*
* Struct: PathHeader { char**, int }
* Descrição: Define uma matriz de diretórios
* Dados:
* 1) FullPath: Corresponde à matriz com todos diretórios do Current Working Directory
* 2) numPaths: Armazena o número de diretórios
*/
typedef struct path {
	char **FullPath;
	int numPaths;
}PathHeader;

//Lista GLOBAL de Paths
PathHeader ListaPath;

/*
* Função: Path_recuperaCaminho (PathHeader*)
* Descrição: Dado uma string alocada, procura o Current Working Directory e salva cada diretório em um elemento da Matriz
*/
void Path_recuperaCaminho (PathHeader *ListaPath);

/*
* Função: Path_imprimeCaminho (PathHeader)
* Descrição: Imprime todos diretórios da Matriz
*/
char* Path_imprimeCaminho (PathHeader ListaPath);
