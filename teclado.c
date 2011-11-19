//Inclusão de bibliotecas do sistema
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#include <termios.h>
#include <errno.h>
#include <sys/wait.h>


#include "teclado.h"

/*
* Função: flushKeys(char)
* Descrição: Limpa o buffer reservado para determinadas teclas
*/
void flushKeys(char *tecla) {
	tecla[0] = tecla[1] = tecla[2] = 0;
}

/*
* Função: Terminal_apagaCaracteres(int)
* Descrição: Apaga conjuntos de caracteres do buffer impresso em tela
*/
void Terminal_apagaCaracteres(int numCaracteres) {
	//Variáveis
	int i;
	//Rotina
	for(i = 0; i < numCaracteres; i++) printf("\b \b");
}

/* 
* Função: Terminal_insereLinhaNoHistorico (char*, char**, int)
* Descrição: Insere uma Linha de Comando no Histórico de Linhas
*/
int Terminal_insereLinhaNoHistorico (char *LinhaComando, char **LinhasComando, int idLinhaComando) {
	//Insere LinhaComando na Lista de Comandos	
	strcpy(LinhasComando[idLinhaComando],LinhaComando);	
	//Retorno
	return 0;
}

/*
* Função: Terminal_processaLinha (char*, char**, int)
* Descrição: Lê e controla a Linha de Comando, de modo não-canônico
*/
char* Terminal_processaLinha (char **LinhasComando, int idLinhaComando) {
	//Variáveis
	int keyIndex, contadorTeclas, linesOver;
	char caractereDigitado, tecla[3], *LinhaComandoAux, *LinhaComando;

	//Aloca a Linha de Comando
	LinhaComando = Alocacao_alocaVetor(TERMINAL_TAMANHOLINHA);

	//Aloca a Linha de Comando Auxiliar
	LinhaComandoAux = Alocacao_alocaVetor(TERMINAL_TAMANHOLINHA);

	//Reseta a Linha de Comando
	strcpy(LinhaComando,"");

	//Reseta a Linha de Comando Auxiliar
	strcpy(LinhaComandoAux, "");

	//Condições iniciais
	keyIndex = 0;
	linesOver = 0;
	contadorTeclas = 0;

	//Zera buffer das teclas
	flushKeys(tecla);

	while ((caractereDigitado = getchar())) {
		//Armazena a tecla
		tecla[keyIndex] = caractereDigitado;

		//Incrementa o keyIndex
		keyIndex++;
		
		//Reseta o keyIndex a cada 3 caracteres
		if(keyIndex > 2) keyIndex = 0;

		//Tecla CIMA
		if(tecla[0] == 27 && tecla[1] == 91 && tecla[2] == 65) {
			//Zera buffer das teclas
			flushKeys(tecla);

			//Linha atual
			if(linesOver == 0) {
				//Gera Linha de Comando Auxiliar
				strcpy(LinhaComandoAux,LinhaComando);

				//Apaga o buffer escrito na tela
				Terminal_apagaCaracteres(strlen(LinhaComandoAux));

				//Atualiza o número de linhas além da atual
				linesOver++;

				//Salva a linha anterior em LinhaComando
				if(idLinhaComando-linesOver > 0) {
					//Recupera a linha anterior
					strcpy(LinhaComando, LinhasComando[idLinhaComando-linesOver]);
					
					//Recupera contador de teclas
					contadorTeclas = strlen(LinhaComando);

					//Imprime Linha de Comando
					printf("%s", LinhaComando);
				
				}

				else {
					strcpy(LinhaComando,"");
				}
			}

			//Linha anterior
			else if(linesOver > 0 && idLinhaComando-linesOver > 0) {
				//Apaga o buffer escrito na tela
				Terminal_apagaCaracteres(strlen(LinhaComando));

				//Atualiza o número de linhas além da atual
				linesOver++;

				//Salva em LinhaComando a linha anterior
				strcpy(LinhaComando, LinhasComando[idLinhaComando - linesOver]);

				//Recupera contador de teclas
				contadorTeclas = strlen(LinhaComando);

				//Imprime Linha de Comando
				printf("%s", LinhaComando);
			}
		}

		//Tecla BAIXO
		else if(tecla[0] == 27 && tecla[1] == 91 && tecla[2] == 66) {
			//Zera buffer das teclas
			flushKeys(tecla);

			//Apaga o buffer escrito na tela
			Terminal_apagaCaracteres(strlen(LinhaComando));
			
			//Penúltima linha
			if(linesOver == 1) {
				//Atualiza o número de linhas além da atual
				linesOver--;
			
				//Salva em LinhaComando a linha em branco
				strcpy(LinhaComando,LinhaComandoAux);

				//Recupera contador de teclas
				contadorTeclas = strlen(LinhaComando);
			}

			//Antepenúltima linha ou anterior
			else if(linesOver > 1){
				//Atualiza o número de linhas além da atual				
				linesOver--;

				//Salva em LinhaComando a próxima linha
				strcpy(LinhaComando, LinhasComando[idLinhaComando - linesOver]);

				//Recupera contador de teclas
				contadorTeclas = strlen(LinhaComando);				
			}

			//Imprime Linha de Comando
			printf("%s", LinhaComando);
		}

		//Comando CTRL+L
		else if((tecla[0] == 12 || tecla[1] == 12 || tecla[2] == 12)) {
			//Zera buffer das teclas
			flushKeys(tecla);

			//Limpa a tela
			system("clear");

			//IMPLEMENTAR
			Color_red(Path_imprimeCaminho(ListaPath));
		}
		//Comando CTRL+C
		else if((tecla[0] == 3 || tecla[1] == 3 || tecla[2] == 3) && contadorTeclas == 0) {
			//Zera buffer das teclas
			flushKeys(tecla);

			//IMPLEMENTAR
			//Envia sinal de interrupção
			break;
		}

		//Comando CTRL+D
		else if((tecla[0] == 4 || tecla[1] == 4 || tecla[2] == 4) && contadorTeclas == 0) {
			//Zera buffer das teclas
			flushKeys(tecla);
			
			//IMPLEMENTAR
			//Envia sinal de interrupção
			break;
		}

		//Comando CTRL+Z		
		else if((tecla[0] == 26 || tecla[1] == 26 || tecla[2] == 26) && contadorTeclas == 0) {
			//Zera buffer das teclas
			flushKeys(tecla);

			//IMPLEMENTAR
			//Envia processo atual para BACKGROUND
			break;
		}

		//Nenhuma tecla acima
		else if(tecla[0] != 27 && tecla[0] != 12 && tecla[0] != 4 && tecla[0] != 26 && tecla[0] != 3) {
			//Zera buffer das teclas
			flushKeys(tecla);

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
				if(strcmp(LinhaComando, "") != 0) {
					printf("%c\n",caractereDigitado);
					
					//IMPLEMENTAR

					//Encerra linha de comando
					
				}
				else {
					printf("%c\n",caractereDigitado);
				}
				break;
			}

			//Backspace
			else if(caractereDigitado == 127 && contadorTeclas > 0) {
				//Apaga um caractere da tela
				Terminal_apagaCaracteres(1);
				
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
