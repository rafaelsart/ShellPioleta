//Inclusão de bibliotecas do sistema
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
* Função: flushKeys(char)
* Descrição: Limpa o buffer reservado para determinadas teclas
*/
void Tela_flushKeys(char *tecla);

/*
* Função: Tela_apagaCaracteres(int)
* Descrição: Apaga conjuntos de caracteres do buffer impresso em tela
*/
void Tela_apagaCaracteres(int numCaracteres);

/*
* Função: Terminal_imprimeShell(char*, char*)
* Descrição: Imprime em vermelho o nome de usuário e o diretório atual
*/
void Tela_imprimeShell(char* Usuario, char* Diretorio);
