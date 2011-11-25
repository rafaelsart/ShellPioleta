//Inclusão de bibliotecas do sistema
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

//Inclusão de bibliotecas próprias
#include "tela.h"
#include "erros.h" 
#include "alocacao.h"
#include "signal_capture.h"
#include "canonical.h"
#include "terminal.h"
#include "comando.h"
#include "jobs.h"

/* 
* Função		: Terminal_insereLinhaNoHistorico (char*, char**, int)
* Descrição		: Insere uma Linha de Comando no Conjunto das Linhas de Comando (Histórico)
* Parâmetros:
* char *LinhaComando	: Linha de Comando digitada pelo usuário
* char **LinhasComando	: Conjunto das Linhas de Comando (Histórico)
* int numLinhasComando	: Número de Linhas de Comando
*/
int Terminal_insereLinhaNoHistorico (char *LinhaComando, char **LinhasComando, int numLinhasComando) {
	//Insere LinhaComando na Lista de Comandos	
	strcpy(LinhasComando[numLinhasComando],LinhaComando);
	
	//Retorno
	return 0;
}

/* BEGIN TEST
char* compararTab(char *buffer) {
	

	return NULL;
}
END TEST*/

/*
* Função		: Terminal_processaTeclaHistorico (char**, char*, char*, int*, int*, int)
* Descrição		: Processa as Teclas de Navegação de Histórico enviadas pelo usuário durante a composição da Linha de Comando
* Parâmetros:
* char **LinhasComando	: Conjunto das Linhas de Comando
* char *LinhaComando	: Linha de Comando (a ser modificada)
* char *tecla		: Buffer contendo a Tecla capturada
* int *contadorTeclas	: Número de caracteres da Linha de Comando em composição (a ser modificado)
* int *linesOver	: Número de Linhas além da atual (a ser modificado)
* int numLinhasComando	: Número de Linhas de Comando
* Retorno		: void
*/
void Terminal_processaTeclaHistorico (char **LinhasComando, char *LinhaComando, char *tecla, int *contadorTeclas, int *linesOver, int numLinhasComando) {
	//Tecla CIMA
	if(tecla[0] == 27 && tecla[1] == 91 && tecla[2] == 65) {
		//Zera buffer das teclas
		Tela_flushKeys(tecla);

		//Linha atual
		if(numLinhasComando-(*linesOver) > 0) {
			//Apaga o buffer escrito na tela
			Tela_apagaCaracteres(TERMINAL_TAMANHOLINHA);
			Tela_imprimeShell();

			//Atualiza o número de linhas além da atual
			(*linesOver)++;

			//Salva a linha anterior em LinhaComando
			strcpy(LinhaComando, LinhasComando[numLinhasComando-(*linesOver)]);

			//Recupera contador de teclas
			*contadorTeclas = strlen(LinhaComando);

			//Imprime Linha de Comando
			printf("%s", LinhaComando);
		}
	}
	//Tecla BAIXO
	else if(tecla[0] == 27 && tecla[1] == 91 && tecla[2] == 66) {
		//Zera buffer das teclas
		Tela_flushKeys(tecla);

		//Apaga o buffer escrito na tela
		Tela_apagaCaracteres(TERMINAL_TAMANHOLINHA);
		Tela_imprimeShell();


		//Última linha
		if(*linesOver == 0) strcpy(LinhaComando,"");

		//Penúltima linha ou anterior
		else if(*linesOver > 0) {
			(*linesOver)--;
			strcpy(LinhaComando, LinhasComando[numLinhasComando - (*linesOver)]);
		}

		//Recupera contador de teclas
		*contadorTeclas = strlen(LinhaComando);

		//Imprime Linha de Comando
		printf("%s", LinhaComando);
	}
}

/*
* Função		: Terminal_processaTeclaComando (char*, char*, int)
* Descrição		: Processa as Teclas de Comando enviadas pelo usuário durante a composição da Linha de Comando
* Parâmetros:
* char *LinhaComando	: Linha de Comando digitada pelo usuário até este instante
* char *tecla		: Buffer contendo a Tecla capturada
* int contadorTeclas	: Número de caracteres da Linha de Comando em composição
* Retorno		: void
*/
void Terminal_processaTeclaComando (char *LinhaComando, char *tecla, int contadorTeclas) {
	Job *jobAux;

	//Salva em jobAux a job em FOREGROUND
	jobAux = Jobs_retornaJobEmForeground(Jobs);

	//Comando CTRL+L (Limpa a tela)
	if(tecla[0] == 12 || tecla[1] == 12 || tecla[2] == 12) {
		//Zera buffer das teclas
		Tela_flushKeys(tecla);

		//Limpa a tela
		Tela_limpaTela();

		//Imprime a Shell
		Tela_apagaCaracteres(TERMINAL_TAMANHOLINHA);
        	Tela_imprimeShell();

		//Imprime Linha de Comando
		printf("%s",LinhaComando);
	}

	//Comando CTRL+C (Envia SIGINT para o processo em FOREGROUND)
	else if((tecla[0] == 3 || tecla[1] == 3 || tecla[2] == 3) && contadorTeclas == 0) {
		//Zera buffer das teclas
		Tela_flushKeys(tecla);
		
		//Envia sinal de interrupção
		if(Jobs_retornaJobEmForeground(Jobs) != NULL) kill(Jobs_retornaJobEmForeground(Jobs)->pid,SIGINT);
		else {
			printf("Nao ha jobs em foreground!\n");
			Tela_apagaCaracteres(TERMINAL_TAMANHOLINHA);
		}

		//Limpa a linha de comando
		strcpy(LinhaComando,"");

		//Imprime a Shell novamente
		Tela_imprimeShell();
	}

	//Comando CTRL+Z
	else if(tecla[0] == 26 || tecla[1] == 26 || tecla[2] == 26) {
		//Zera buffer das teclas
		Tela_flushKeys(tecla);
		
		//Existe Job em FOREGROUND
		if(jobAux != NULL) {
			//Atualiza a Job
			Jobs_colocaJobEmBackground(&Jobs,jobAux->pid);
			jobAux->statusExecucao = PAUSADO;

			//Envia sinal de Interrupção (SIGSTOP)
			kill(jobAux->pid, SIGSTOP);
		}
		//Não existe nenhuma Job em FOREGROUND
		else {
			printf("Nao ha jobs em foreground!\n");
			Tela_apagaCaracteres(TERMINAL_TAMANHOLINHA);
		}

		//Limpa a linha de comando
		strcpy(LinhaComando,"");

		//Imprime a Shell novamente
		Tela_imprimeShell();
	}
}

/*
* Função		: Terminal_processaLinha (char*, int)
* Descrição		: Processa a Linha de Comando inserida pelo usuário, no modo Não-Canônico
* Parâmetros:
* char **LinhasComando	: Conjunto das Linhas de Comando
* int numLinhasComando	: Número de Linhas de Comando
* Retorno		: Linha de Comando processada
*/
char* Terminal_processaLinha (char **LinhasComando, int numLinhasComando) {
	//Variáveis
	int keyIndex, contadorTeclas, linesOver;
	char caractereDigitado, tecla[3], *LinhaComando;
	
	/*BEGIN TEST
	Variáveis
	int okTab, i, temAbrev, stopTab;
	char *bufferAux, *bufA, *bufB;
	File *tabelaTab;
	stopTab = 0;
	
	tabelaTab = fopen("tabela.txt", "r+");
	if(tabelaTab != NULL) okTab = 1;
	END TEST*/

	//Aloca a Linha de Comando
	LinhaComando = Alocacao_alocaVetor(TERMINAL_TAMANHOLINHA);

	//Reseta a Linha de Comando
	strcpy(LinhaComando,"");

	//Condições iniciais
	keyIndex = 0;
	linesOver = 0;
	contadorTeclas = 0;

	//Zera buffer das teclas
	Tela_flushKeys(tecla);

	//Rotina que captura os caracteres digitados
	while ((caractereDigitado = getchar())) {
		//Corrige o problema de formatação quando a última linha de comando continha um '&'
		if(contadorTeclas == 0) {
			if(numLinhasComando>0)
				if(LinhasComando[numLinhasComando-1][strlen(LinhasComando[numLinhasComando-1])-1] == '&') {
					//Imprime a Shell
					Tela_apagaCaracteres(TERMINAL_TAMANHOLINHA);
					Tela_imprimeShell();
				}
		}

		//Armazena a tecla
		tecla[keyIndex] = caractereDigitado;

		//Incrementa o keyIndex
		keyIndex++;
		
		//Reseta o keyIndex a cada 3 caracteres
		if(keyIndex > 2) keyIndex = 0;

		//Processa Teclas de Navegação de Histórico (CIMA e BAIXO)
		if((tecla[0] == 27 && tecla[1] == 91 && tecla[2] == 65) || (tecla[0] == 27 && tecla[1] == 91 && tecla[2] == 66)) {
			Terminal_processaTeclaHistorico (LinhasComando, LinhaComando, tecla, &contadorTeclas, &linesOver, numLinhasComando);
		}


		//Processa Teclas de Comando (Ctrl+L, Ctrl+C, Ctrl+Z)
		else if((	tecla[0] == 12	|| tecla[1] == 12	|| tecla[2] == 12	||
				tecla[0] == 3	|| tecla[1] == 3	|| tecla[2] == 3	||
				tecla[0] == 26	|| tecla[1] == 26	|| tecla[2] == 26)) {
			Terminal_processaTeclaComando(LinhaComando, tecla, contadorTeclas);
		}
	
		/*BEGIN TEST
		//Processa Tecla Tab
		else if(tecla[0] == 9){
			if(strlen(LinhaComando) > 2 && okTab == 1){
				while(stopTab != 1) {
					bufferAux = (char *) malloc(sizeof(char) * 50);

					if(fgets(bufferAux, 50, tabelaTab) != NULL) {
						bufferAux[strlen(bufferAux) - 1] = '\0';

						bufA = (char *) malloc(sizeof(char) * 50);
						bufB = (char *) malloc(sizeof(char) * 50);

						temAbrev = 0;
						for(i=0; bufferAux[i] != '\0'; i++) {
		
							if(bufferAux[i] == ' ') temAbrev = 1;
						}
					
						if(temAbrev == 1){
							for(i=0; bufferAux[i] != ' '; i++) {
								bufB[i] = bufferAux[i];
							}	
							bufB[i] = '\0';
							i++;

							for(; bufferAux[i] != '\0'; i++) {
								bufA[i] = bufferAux[i];
							}
							bufA[i] = '\0';
	
							if(strcmp(bufA, LinhaComando) == 0){
								printf("%s", bufB);
								Tela_apagaCaracteres(strlen(bufB));
								contadorTeclas = contadorTeclas - strlen(LinhaComando);
								contadorTeclas = contadorTeclas + strlen(bufB);
							}
						}
						free(bufA);
						free(bufB);						
					}
					else {
						stopTab = 1; // acabou a lista
					}
					free(bufferAux);
				}
			} 
		}
		END TEST */

		//Nenhuma tecla acima
		else if(tecla[0] != 27 && tecla[0] != 12 && tecla[0] != 4 && tecla[0] != 26 && tecla[0] != 3) {
			//Zera buffer das teclas
			Tela_flushKeys(tecla);

			//Caracteres imprimíveis
			if(caractereDigitado >= 32 && caractereDigitado <= 126) {				
				//Imprime caractere digitado
				printf("%c", caractereDigitado);

				//Armazena caractere na linha de Comando
				LinhaComando[contadorTeclas] = caractereDigitado;

				//Atualiza contador de teclas digitadas				
				contadorTeclas++;

				//Reseta keyIndex
				keyIndex = 0;

				//Encerra processamento da Linha de Comando
				LinhaComando[contadorTeclas] = '\0';
			}
			
			//Enter 
			else if(caractereDigitado == 13) {
				//Algo foi digitado
				if(strcmp(LinhaComando, "") != 0) printf("%c\n",caractereDigitado);
				//Nada foi digitado
				else {
					printf("%c\n",caractereDigitado);
					Tela_apagaCaracteres(TERMINAL_TAMANHOLINHA);
					return NULL;
				}
				//Encerra o processamento da Linha de Comando
				break;
			}

			//Backspace
			else if(caractereDigitado == 127 && contadorTeclas > 0) {
				//Apaga um caractere da tela
				Tela_apagaCaracteres(1);
				
				//Atualiza contador de teclas digitadas	
				contadorTeclas--;

				//Encerra processamento da Linha de Comando
				LinhaComando[contadorTeclas] = '\0';
			}
		}
	}

	//Retorno
	return LinhaComando;
}

/*
* Função		: Terminal_InterpretaLinhaComando (char*, char**)
* Descrição		: Interpreta a Linha de Comando digitada e executa os comandos conforme necessário
* Parâmetros:
* char *LinhaComando	: Linha de Comando digitada
* char **LinhasComando	: Conjunto de Linhas de Comando (para verificação de '&' da linha anterior)
* Retorno		: void
*/
void Terminal_InterpretaLinhaComando (char *LinhaComando, char **LinhasComando) {
	//Variáveis	
	int iContador, numParametros, Status;
	char **Parametro, *Comando, *tokenPalavra, *espacoAux;
	
	//Condições iniciais
	iContador = 0;
	numParametros = 0;

	//BACKGROUND
	if(LinhaComando[strlen(LinhaComando)-1] == '&') {
		//Define Modo de Execução
		Status = BACKGROUND;

		//Remove ' &' da linha de comando
		LinhaComando[strlen(LinhaComando)-1] = '\0';
		LinhaComando[strlen(LinhaComando)] = '\0';
		Tela_apagaCaracteres(TERMINAL_TAMANHOLINHA);
		//Jobs_imprimeJobs(Jobs);
	}

	//FOREGROUND
	else Status = FOREGROUND;

	//Encontra número de parâmetros
	espacoAux = strpbrk(LinhaComando," ");
	while(espacoAux != NULL) {
		numParametros++;
		espacoAux = strpbrk(espacoAux+1," ");
	}
	numParametros++;

	//Aloca conjunto de parâmetros
	Parametro = malloc(numParametros*sizeof(char*));

	//Limpa parâmetros que ficaram alocados
	while(Parametro[iContador] != NULL) {
		free(Parametro[iContador]);
		iContador++;
	}
	iContador = 0;

	//Quebra Linha de Comando em Palavras
	tokenPalavra = (char*) strtok(LinhaComando, " ");
	if(tokenPalavra == NULL) {
		Parametro[0] = Alocacao_alocaVetor(strlen(LinhaComando));
		strcpy(Parametro[0],LinhaComando);
	}
	else {
		while(tokenPalavra != NULL) {
			//Aloca parâmetro
			Parametro[iContador] = Alocacao_alocaVetor(strlen(tokenPalavra));
		
			//Salva palavra
			strcpy(Parametro[iContador], tokenPalavra);
			
			//Incrementa o número de palavras
			iContador++;

			//Percorre o token
			tokenPalavra = (char*) strtok(NULL, " ");
		}
	}

	//Libera memória alocada
	free(tokenPalavra);

	//Aloca Comando
	Comando = Alocacao_alocaVetor(strlen(Parametro[0]));

	//Armazena Comando
	if(iContador >=0) strcpy(Comando, Parametro[0]);

	//Roda Comando Built-In
	if(Comando_isBuiltIn(Parametro)) Comando_rodaBuiltIn(Parametro);
	
	//Roda Comando do Sistema
	else Comando_rodaLinhaComando(Parametro, numParametros, Status);

	//Libera memória alocada
	free(tokenPalavra);
}
