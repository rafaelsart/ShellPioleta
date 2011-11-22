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
* Função: Terminal_insereLinhaNoHistorico (char*, char**, int)
* Descrição: Insere uma Linha de Comando no Histórico de Linhas
*/
int Terminal_insereLinhaNoHistorico (char *LinhaComando, char **LinhasComando, int numLinhasComando) {
	//Insere LinhaComando na Lista de Comandos	
	strcpy(LinhasComando[numLinhasComando],LinhaComando);	
	//Retorno
	return 0;
}

/*
* Função: Terminal_InterpretaLinhaComando (char*, char**)
* Descrição: Interpreta a Linha de Comando digitada
*/
void Terminal_InterpretaLinhaComando (char *LinhaComando, char **LinhasComando) {
	//Variáveis	
	int iContador, numParametros, status;
	char **Parametro, *Comando, *tokenPalavra, *espacoAux;
		
	//Condições iniciais
	iContador = 0;
	numParametros = 0;
	//BACKGROUND
	if(LinhaComando[strlen(LinhaComando)-1] == '&') {
		status = BACKGROUND;
		//Remove ' &' da linha de comando
		LinhaComando[strlen(LinhaComando)-1] = '\0';
		LinhaComando[strlen(LinhaComando)] = '\0';
		//LinhaComando = realloc(LinhaComando,strlen(LinhaComando));
	}
	//FOREGROUND
	else status = FOREGROUND;

	//Encontra número de parâmetros
	espacoAux = strpbrk(LinhaComando," ");
	while(espacoAux != NULL) {
		numParametros++;
		espacoAux = strpbrk(espacoAux+1," ");
	}
	numParametros++;
	//Aloca conjunto de parâmetros
	Parametro = malloc(numParametros*sizeof(char*));

	//Quebra Linha de Comando em Palavras
	tokenPalavra = (char*) strtok(LinhaComando, " ");
	while(tokenPalavra != NULL) {
		//Aloca parâmetro
		Parametro[iContador] = Alocacao_alocaVetor(strlen(tokenPalavra));

		//Salva palavra
		strcpy(Parametro[iContador], tokenPalavra);

		//Percorre o token
		tokenPalavra = (char*) strtok(NULL, " ");

		//Incrementa o número de palavras
		iContador++;
	}
	//Libera memória alocada
	free(tokenPalavra);

	//Aloca Comando
	Comando = Alocacao_alocaVetor(strlen(Parametro[0]));

	//Armazena Comando
	if(iContador >=0 ) strcpy(Comando, Parametro[0]);

	//Comandos Built-In
	if(Comando_isBuiltIn(Parametro)) Comando_rodaBuiltIn(Parametro);
	
	//Demais comandos
	else Comando_rodaLinhaComando(Parametro, status);

	//Libera memória alocada
	//free(tokenPalavra);
	for(iContador=0;iContador<numParametros;iContador++) free(Parametro[iContador]);
	free(Parametro);
}

/*
* Função: Terminal_processaLinha (char*, char**, int)
* Descrição: Lê e controla a Linha de Comando, de modo não-canônico
*/
char* Terminal_processaLinha (char **LinhasComando, int numLinhasComando) {
	//Variáveis
	int keyIndex, contadorTeclas, linesOver;
	char caractereDigitado, tecla[3], *LinhaComando;
	
	//Aloca a Linha de Comando
	LinhaComando = Alocacao_alocaVetor(TERMINAL_TAMANHOLINHA);

	//Reseta a Linha de Comando
	strcpy(LinhaComando,"");

	//Reseta a Linha de Comando Auxiliar
	//strcpy(LinhaComandoAux, "");

	//Condições iniciais
	keyIndex = 0;
	linesOver = 0;
	contadorTeclas = 0;

	//Zera buffer das teclas
	Tela_flushKeys(tecla);

	while ((caractereDigitado = getchar())) {
		//Corrige o problema de formatação quando a última linha de comando continha um '&'
		if(contadorTeclas == 0) {
			if(numLinhasComando>0)
				if(LinhasComando[numLinhasComando-1][strlen(LinhasComando[numLinhasComando-1])-1] == '&')
					Tela_apagaCaracteres(TERMINAL_TAMANHOLINHA);
					//Tela_imprimeShell();
		}
		//Armazena a tecla
		tecla[keyIndex] = caractereDigitado;

		//Incrementa o keyIndex
		keyIndex++;
		
		//Reseta o keyIndex a cada 3 caracteres
		if(keyIndex > 2) keyIndex = 0;


		//Tecla CIMA
		if(tecla[0] == 27 && tecla[1] == 91 && tecla[2] == 65) {
			//Zera buffer das teclas
			Tela_flushKeys(tecla);

			//Linha atual
			if(numLinhasComando-linesOver > 0) {
				//Apaga o buffer escrito na tela
				Tela_apagaCaracteres(TERMINAL_TAMANHOLINHA);
				Tela_imprimeShell();

				//Atualiza o número de linhas além da atual
				linesOver++;

				//Salva a linha anterior em LinhaComando
				strcpy(LinhaComando, LinhasComando[numLinhasComando-linesOver]);

				//Recupera contador de teclas
				contadorTeclas = strlen(LinhaComando);

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
			if(linesOver == 0) strcpy(LinhaComando,"");

			//Penúltima linha ou anterior
			else if(linesOver > 0) {
				linesOver--;
				strcpy(LinhaComando, LinhasComando[numLinhasComando - linesOver]);
			}

			//Recupera contador de teclas
			contadorTeclas = strlen(LinhaComando);

			//Imprime Linha de Comando
			printf("%s", LinhaComando);
		}

		//Comando CTRL+L
		else if((tecla[0] == 12 || tecla[1] == 12 || tecla[2] == 12)) {
			//Zera buffer das teclas
			Tela_flushKeys(tecla);

			//Limpa a tela
			puts("\n\n\n\n\n\n\n");
			Tela_apagaCaracteres(TERMINAL_TAMANHOLINHA);
                	Tela_imprimeShell();
		}

		//Comando CTRL+D
		else if((tecla[0] == 4 || tecla[1] == 4 || tecla[2] == 4) && contadorTeclas == 0) {
			//Zera buffer das teclas		
			Tela_flushKeys(tecla);
			
			//IMPLEMENTAR
			//Envia sinal de interrupção
			break;
		}

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
				//Aloca a Linha de Comando
				//LinhaComando = realloc(LinhaComando,(contadorTeclas+1)*sizeof(char));
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
				else {
					printf("%c\n",caractereDigitado);
					Tela_apagaCaracteres(TERMINAL_TAMANHOLINHA);
					return NULL;
				}
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
