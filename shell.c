//Inclusão de bibliotecas do sistema
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#include <termios.h>
#include <errno.h>
#include <sys/wait.h>

//Inclusão de bibliotecas próprias
#include "colors.h"
#include "tela.h"
#include "erros.h"
#include "alocacao.h"
#include "jobs.h"
#include "signal_capture.h"
#include "canonical.h"

/*
* Conjunto de definições de Terminal
*/
#define TERMINAL_TAMANHODIRETORIO 128
#define TERMINAL_TAMANHOPATH 512
#define TERMINAL_TAMANHOUSUARIO 32
#define TERMINAL_NUMLINHAS 128
#define TERMINAL_TAMANHOLINHA 1024
#define TERMINAL_TAMANHOPALAVRA 32

/* Path */
char **Path;

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

int Comando_isBuiltIn(char **Parametro){
	if(strcmp(Parametro[0], "cd") == 0){
		return 1;
	}

	if(strcmp(Parametro[0], "exit") == 0){
		return 1;
	}
	
	if(strcmp(Parametro[0], "bg") == 0){
		return 1;
	}

	if(strcmp(Parametro[0], "fg") == 0){
		return 1;
	}
	
	if(strcmp(Parametro[0], "jobs") == 0){

		return 1;
	}

	if(strcmp(Parametro[0], "quit") == 0){
		return 1;
	}

	return 0;
}

void Comando_rodaBuiltIn(char **Parametro){
	//puts(Parametro[1]);
	//exit
	if(strcmp(Parametro[0], "exit") == 0 || strcmp(Parametro[0], "quit") == 0) {
		//Sai do terminal				
		exit(0);
	}
	//cd
	if(strcmp(Parametro[0], "cd") == 0) {
		if(Parametro[1] != NULL)		
			if(strcmp(Parametro[1],"") != 0)
						if (chdir(Parametro[1]) == -1) perror("ERRO");
	}
	//jobs
	if(strcmp(Parametro[0], "jobs") == 0) {
		Jobs_imprimeJobs(Jobs);
	}

	//bg
	if (strcmp(Parametro[0], "bg") == 0) {
		//int bgId;
		//sprintf(bgId, "%s", Parametro[1]);
		//Jobs_colocaJobEmBackground(Jobs, bgId);
	}
	
	//fg
	if (strcmp(Parametro[0], "fg") == 0) {
		//int fgId;
		//sprintf(fgId, "%s", Parametro[1]);
		//Jobs_colocaJobEmBackground(Jobs, fgId);
	}
}

/*
* Função: Comando_rodaLinhaComando (char*, char**, int, int)
* Descrição: Roda os comandos não built-in
*/
int Comando_rodaLinhaComando (char **Parametro, int runForeground) {
	//Variáveis
	pid_t pidNovoProcesso;
	char *tokenPath;
	int iContador, iPath = 0;

	//char **tokenized = get_command_tokens(commands[i], &foreground);

	//Cria processo-filho
	pidNovoProcesso = fork();

	//Falha na criação
	if(pidNovoProcesso == -1) {
		perror("Nao foi possivel criar novo processo\n");
		exit(0);
	}
	//Processo ativo
	else if(pidNovoProcesso == 0) {
		//Aloca caminho
		Path = (char**) malloc(((strlen(getenv("PATH"))/2)+2)*sizeof(char*));

		//Quebra PATH em diretórios
		tokenPath = (char*) strtok(getenv("PATH"), ":");

		while(tokenPath != NULL) {
			//Aloca caminho
			Path[iPath] = (char*) malloc(strlen(tokenPath)/*+strlen(Parametro[0])*/+1);
			strcpy(Path[iPath],"");
			//Salva caminho
			strcat(Path[iPath], tokenPath);
			//Percorre o token
			tokenPath = (char*) strtok(NULL, ":");
			//Incrementa o número de palavras
			iPath++;
		}
		//Executa comando
		for(iContador=0;iContador<iPath;iContador++) {
			char Caminho[(strlen(Path[iContador])+strlen(*Parametro)+2)];
			strcpy(Caminho,Path[iContador]);
			strcat(Caminho,"/");
			strcat(Caminho, *Parametro);
			//printf("Parametro[%d]: %s\n",iContador,Parametro[iContador]);
			execv(Caminho, Parametro);
		}
		printf("\n\n");
		Tela_apagaCaracteres(100);
		fprintf(stderr, "\nComando nao reconhecido.\n\n");
		exit(EXIT_FAILURE);
	}
	else {
		//Define ID do grupo de processos
		setpgid(pidNovoProcesso,0);

		//Cria um job e adiciona à lista
		Jobs_adicionaJob(&Jobs, Parametro[0], pidNovoProcesso, FOREGROUND, RODANDO);

		if(runForeground == FOREGROUND) waitpid(pidNovoProcesso, NULL, 0);

	}

	free(Parametro);

	//Retorno
	return 1;
}

/* 
* Função: Terminal_InterpretaLinhaComando (char*, char**, char*)
* Descrição: Interpreta a Linha de Comando digitada
*/
void Terminal_InterpretaLinhaComando (char *LinhaComando, char **LinhasComando) {
	//Variáveis	
	int runForeground, idPalavra, iContador;
	char **Parametro, *Comando, *tokenPalavra, *tokenPalavraAux, *LinhaComandoAux, *LinhaComandoAux2;
	
	//Aloca a matriz de parâmetros
	//Parametro = Alocacao_alocaMatriz((TERMINAL_TAMANHOLINHA),TERMINAL_TAMANHOPALAVRA);

	//Aloca o vetor Comando
	Comando = Alocacao_alocaVetor(TERMINAL_TAMANHOPALAVRA);
		
	//Condições iniciais
	idPalavra = 0;

	//Recupera o último caractere da linha de comando para definir se roda em FOREGROUND ou BACKGROUND
	if(LinhaComando[strlen(LinhaComando)-1] == '&') {
		runForeground = 0;
		//Remove ' &' da linha de comando
		LinhaComandoAux = malloc((strlen(LinhaComando)-2)*sizeof(char));
		strcpy(LinhaComandoAux,LinhaComando);
		strncpy(LinhaComando,LinhaComandoAux,strlen(LinhaComando)-2);
	}
	else runForeground = 1;

	LinhaComandoAux2 = (char*) malloc(strlen(LinhaComando)*sizeof(char));
	strcpy(LinhaComandoAux2,LinhaComando);
	
	//Quebra Linha de Comando em Palavras
	tokenPalavraAux = (char*) strtok(LinhaComandoAux2, " ");
	while(tokenPalavraAux != NULL) {
		//Percorre o token
		tokenPalavraAux = (char*) strtok(NULL, " ");

		//Incrementa o número de palavras
		idPalavra++;
	}
	
	Parametro = malloc(idPalavra*sizeof(char*));
	
	idPalavra = 0;

	//Quebra Linha de Comando em Palavras
	tokenPalavra = (char*) strtok(LinhaComando, " ");
	while(tokenPalavra != NULL) {
		//Aloca parâmetro
		Parametro[idPalavra] = malloc(strlen(tokenPalavra)*sizeof(char));
		//Salva palavra
		strcpy(Parametro[idPalavra], tokenPalavra);

		//Percorre o token
		tokenPalavra = (char*) strtok(NULL, " ");

		//Incrementa o número de palavras
		idPalavra++;
	}

	if(idPalavra >=0 ) strcpy(Comando, Parametro[0]);

	if(!Comando_isBuiltIn(Parametro)){
		//Roda comando
		Comando_rodaLinhaComando(Parametro, runForeground);
		return;
			
	}
	else Comando_rodaBuiltIn(Parametro);

	//Libera memória alocada
	free(tokenPalavra);
	for(iContador=0;iContador<idPalavra;iContador++) free(Parametro[iContador]);
	free(Parametro);
}

/*
* Função: Terminal_processaLinha (char*, char**, int)
* Descrição: Lê e controla a Linha de Comando, de modo não-canônico
*/
char* Terminal_processaLinha (char **LinhasComando, int idLinhaComando) {
	//Variáveis
	int keyIndex, contadorTeclas, linesOver;
	char caractereDigitado, tecla[3], *LinhaComandoAux, *LinhaComando;
	char *Diretorio, *Usuario;

	//Aloca a Linha de Comando Auxiliar
	LinhaComandoAux = Alocacao_alocaVetor(TERMINAL_TAMANHOLINHA);

	//if(LinhaComando != NULL) free(LinhaComando);	
	
	//Aloca a Linha de Comando
	LinhaComando = Alocacao_alocaVetor(TERMINAL_TAMANHOLINHA);

	//Reseta a Linha de Comando
	strcpy(LinhaComando,"");

	//Reseta a Linha de Comando Auxiliar
	strcpy(LinhaComandoAux, "");

	//Aloca Diretório
	Diretorio = Alocacao_alocaVetor(TERMINAL_TAMANHODIRETORIO);

	//Condições iniciais
	keyIndex = 0;
	linesOver = 0;
	contadorTeclas = 0;

	//Zera buffer das teclas
	Tela_flushKeys(tecla);

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
			Tela_flushKeys(tecla);

			//Linha atual
			if(linesOver == 0) {
				//Gera Linha de Comando Auxiliar
				strcpy(LinhaComandoAux,LinhaComando);

				//Apaga o buffer escrito na tela
				Tela_apagaCaracteres(strlen(LinhaComandoAux));

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
				Tela_apagaCaracteres(strlen(LinhaComando));

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
			Tela_flushKeys(tecla);

			//Apaga o buffer escrito na tela
			Tela_apagaCaracteres(strlen(LinhaComando));
			
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
			Tela_flushKeys(tecla);

			//Limpa a tela
			//system("clear");//
			puts("\n\n\n\n\n\n\n");
			Tela_apagaCaracteres(100);
			

			Usuario = strdup(getenv("USER"));

			getcwd(Diretorio,TERMINAL_TAMANHODIRETORIO*sizeof(char));
		
                	Tela_imprimeShell(Usuario,Diretorio);
		}
		//Comando CTRL+C
		else if((tecla[0] == 3 || tecla[1] == 3 || tecla[2] == 3) && contadorTeclas == 0) {
			//Zera buffer das teclas
			Tela_flushKeys(tecla);

			//IMPLEMENTAR
			//Envia sinal de interrupção
			break;
		}

		//Comando CTRL+D
		else if((tecla[0] == 4 || tecla[1] == 4 || tecla[2] == 4) && contadorTeclas == 0) {
			//Zera buffer das teclas		
			Tela_flushKeys(tecla);
			
			//IMPLEMENTAR
			//Envia sinal de interrupção
			break;
		}

		//Comando CTRL+Z		
		else if((tecla[0] == 26 || tecla[1] == 26 || tecla[2] == 26) && contadorTeclas == 0) {
			//Zera buffer das teclas
			Tela_flushKeys(tecla);

			//IMPLEMENTAR
			//Envia processo atual para BACKGROUND
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

int main(void) {
	//Variáveis
	int loopProgram, idLinhaComando;
	char *LinhaComando, **LinhasComando;
	char *Diretorio, *Usuario;
	
	//Instala sinais
	Signal_Instalacao();
	
	//Propriedades da Lista
	Jobs.primeiroJob = NULL;
	Jobs.ultimoJob = NULL;
	Jobs.numJobs = 0;

	//Aloca Linhas de Comando
	LinhasComando = Alocacao_alocaMatriz(TERMINAL_NUMLINHAS, TERMINAL_TAMANHOLINHA);
	
	//Condições iniciais
	loopProgram = 1;
	idLinhaComando = 0;

	//Aloca Diretório
	Diretorio = Alocacao_alocaVetor(TERMINAL_TAMANHODIRETORIO);

	//Limpa a tela
	puts("\n\n\n\n\n\n\n");

	//Execução da rotina principal
	while(loopProgram) {
		//Aloca Cada Linha de Comando
		LinhaComando = Alocacao_alocaVetor(TERMINAL_TAMANHOLINHA);

		Usuario = strdup(getenv("USER"));
		
		getcwd(Diretorio,TERMINAL_TAMANHODIRETORIO*sizeof(char));
		
                Tela_imprimeShell(Usuario,Diretorio);
		
		//Ativa o modo não-canônico
		Canonical_setNonCanonicalMode();

		//Lê a Linha de Comando
		LinhaComando = Terminal_processaLinha(LinhasComando, idLinhaComando);

		//Retorna ao modo canônico
		Canonical_setCanonicalMode();

		if(LinhaComando != NULL){
			//Insere Linha de Comando no Histórico
			Terminal_insereLinhaNoHistorico(LinhaComando, LinhasComando, idLinhaComando);

			//Interpreta Linha de Comando
			Terminal_InterpretaLinhaComando(LinhaComando, LinhasComando);
		
			//Incrementa Linha de Comando
			idLinhaComando++;

			//Libera memória alocada
			free(LinhaComando);		
		}
	}

	//Retorno
	return 1;
}
