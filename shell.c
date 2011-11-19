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

//Inclusão de bibliotecas próprias
#include "colors.h"
#include "erros.h"
#include "alocacao.h"
#include "path.h"
#include "jobs.h"
#include "signal_capture.h"
#include "canonical.h"

/*
* Conjunto de definições de Terminal
*/
#define TERMINAL_NUMLINHAS 128
#define TERMINAL_TAMANHOLINHA 1024
#define TERMINAL_TAMANHOPALAVRA 32

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
					return NULL;
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

/*
* Função: Terminal_rodaLinhaComando (char*, char**, int, int)
* Descrição: * Roda os comandos não built-in *
*/
int Terminal_rodaLinhaComando (char **caminhos, char **Parametro, int numParametros, int qtdCaminhos, int runForeground) {
	//Variáveis
	pid_t pidNovoProcesso;
	Job* jobAux;
	int i;
	int status;

	i=0;

	//Entrada e Saída
	//FILE *ori_stdin = stdin;
	//FILE *ori_stdout = stdout;
	//FILE *ori_stderr = stderr;
		

		//Cria processo-filho

		pidNovoProcesso = fork();

		//Falha na criação
		if(pidNovoProcesso == -1) {
			//ERRO_NAO_FOI_POSSIVEL_CRIAR

			perror("Nao foi possivel criar novo processo\n");
			exit(0);
		}
		else
		if(pidNovoProcesso > 0){
		//	printf("processo pai %d\n", pidNovoProcesso);

			wait(&status);

			//Processo-pai
			
			//Adiciona Job à Lista
			//Jobs_adicionaJob(Jobs,IMPLEMENTAR,pidNovoProcesso,FOREGROUND,RODANDO);
			
			//Se estiver em FOREGROUND
			//jobAux = Jobs_retornaJobEmForeground(Jobs);
			//if(pidNovoProcesso == jobAux->pid) {
				//Define ID do Grupo de Processos
				//setpgid(pidNovoProcesso, 0);
				//Aguarda o término do Processo
				//waitpid(pidNovoProcesso, NULL, 0);
			//}
		}
		else
		if(pidNovoProcesso == 0){
			//if(pidNovoProcesso == 0) {
			//Define ID do Grupo de Processos
			setpgid(pidNovoProcesso, 0);
			
			//IMPLEMENTAR
			//sigaction(SIGTSTP, &IMPLEMENTAR, NULL);
    			//sigaction(SIGCHLD, &IMPLEMENTAR, NULL);
			

			//IMPLEMENTAR
			for (i=0 ; i < qtdCaminhos ; i++)
			{
				char* fullPath;
				fullPath = Alocacao_alocaVetor(TERMINAL_TAMANHOPALAVRA);

				sprintf(fullPath,"%s/%s",caminhos[i],Parametro[0]);
				execv(fullPath, Parametro);
				printf("\nNUH %s\n", fullPath);
				free(fullPath);
			}		
			//execv(IMPLEMENTAR,IMPLEMENTAR);
			
			//ERRO_COMANDO_NAO_RECONHECIDO
			//fprintf(stderr, "\nComando invalido!\n");

		}	

	
	//}

	//Retorno
	return 1;
}


int isBuiltIn(char **Parametro){
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

int Terminal_rodaBuiltIn(char **Parametro){

	//exit
	if(strcmp(Parametro[0], "exit") == 0 || strcmp(Parametro[0], "quit") == 0) {
		//Sai do terminal				
		exit(0);
	}
	//cd
	if(strcmp(Parametro[0], "cd") == 0) {
		if (chdir(Parametro[1]) == -1) perror("ERRO");
		//printf("\n");
	}
	//jobs
	if(strcmp(Parametro[0], "jobs") == 0) {
		Jobs_imprimeJobs(Jobs);
	}

	//bg
	if (strcmp(Parametro[0], "bg") == 0) {
		Jobs_colocaJobEmBackground(Jobs, Parametro[1]);
	}
	
	//fg
	if (strcmp(Parametro[0], "fg") == 0) {
		Jobs_colocaJobEmBackground(Jobs, Parametro[1]);
	}

	return 0;
}

/* 
* Função: Terminal_InterpretaLinhaComando (char*, char**, char*)
* Descrição: Interpreta a Linha de Comando digitada
*/
int Terminal_InterpretaLinhaComando (char *LinhaComando, char **LinhasComando, char **caminhos, int qtdCaminhos) {
	//Variáveis	
	int numParametros, runForeground, idPalavra, contadorParametros;
	char **Parametro, *Comando, *tokenPalavra;
	
	//Aloca a matriz de parâmetros
	Parametro = Alocacao_alocaMatriz((TERMINAL_TAMANHOLINHA/TERMINAL_TAMANHOPALAVRA),TERMINAL_TAMANHOPALAVRA);

	//Aloca o vetor Comando
	Comando = Alocacao_alocaVetor(TERMINAL_TAMANHOPALAVRA);
		
	//Condições iniciais
	idPalavra = 0;
	contadorParametros = 0;
	
	//Quebra Linha de Comando em Palavras
	tokenPalavra = (char*) strtok(LinhaComando, " ");
	while(tokenPalavra != NULL) {
		//Salva palavra
		strcpy(Parametro[idPalavra], tokenPalavra);

		//Percorre o token
		tokenPalavra = (char*) strtok(NULL, " ");

		printf("param.%s\n", Parametro[idPalavra]);
		//Incrementa o número de palavras
		idPalavra++;
	}

	//Salva número de parâmetro
	numParametros = idPalavra;
	//Começa o contador na última posição
	contadorParametros = numParametros;
	
	/*
	//Rotina para cada palavra
	while(contadorParametros >= 0) {

		//Armazena palavra
		strcpy(Comando, Parametro[contadorParametros]);
		//REVISAR
		runForeground = 1;

		//Decrementa contador
		contadorParametros--;
	}*/

	runForeground = 1;

	if(numParametros >=0 )
		strcpy(Comando, Parametro[0]);

	//printf("\nNUH! %s\n", Comando);

	if(!isBuiltIn(Parametro)){
		//Roda comando
		Terminal_rodaLinhaComando(caminhos, Parametro, numParametros, qtdCaminhos, runForeground);
		free(Parametro);
		printf("Command not found: \n");
		return EXIT_FAILURE;
			
	}
	else {
		Terminal_rodaBuiltIn(Parametro);
	}
	//Libera memória alocada
	free(tokenPalavra);

	//Retorno
	return 0;
}

int main(void) {
	//Variáveis
	int loopProgram, idLinhaComando, qtdCaminhos;
	char *LinhaComando, **LinhasComando;
	char *Diretorio, *DiretorioAtual;
	char **caminhos;
	Job *Job;

	//IMPLEMENTAR
	//signal_setup(IMPLEMENTAR)
	
	//Propriedades da Lista
	Jobs.primeiroJob = NULL;
	Jobs.ultimoJob = NULL;
	Jobs.numJobs = 0;

	//Propriedades do Path
	ListaPath.FullPath = Alocacao_alocaMatriz(PATH_NUMDIR, PATH_TAMANHO);
	ListaPath.numPaths = 0;

	//Aloca Linhas de Comando
	LinhasComando = Alocacao_alocaMatriz(TERMINAL_NUMLINHAS, TERMINAL_TAMANHOLINHA);

	//Aloca Cada Linha de Comando
	LinhaComando = Alocacao_alocaVetor(TERMINAL_TAMANHOLINHA);

	//Condições iniciais
	loopProgram = 1;
	idLinhaComando = 0;

	//Aloca vetor 'Diretorio'
	Diretorio = Alocacao_alocaVetor(TERMINAL_TAMANHOLINHA);

	//Aloca Diretório atual
	DiretorioAtual = Alocacao_alocaVetor(PATH_TAMANHO*PATH_NUMDIR);
	DiretorioAtual = Path_imprimeCaminho(ListaPath);	
	caminhos = Alocacao_alocaMatriz(TERMINAL_NUMLINHAS, TERMINAL_TAMANHOLINHA);

	char* token;
	int c = 0;
	char* caminhoInteiro;

	//Limpa a tela
	system("clear");
	
	//	caminhoInteiro = strdup(getenv("PATH"));
	//	token = strtok(caminhoInteiro,":");
	//	while(token != NULL)
	//	{
	//		caminhos[c]=strdup(token);
	//		printf("%s\n",caminhos[c]);
	//		c++;
	//		token = strtok(NULL,":");
	//	}
	//	qtdCaminhos = c;

	//Execução da rotina principal
	while(loopProgram) {
		//Retorna o diretório atual
		caminhoInteiro = strdup(getenv("PATH"));
		token = strtok(caminhoInteiro,":");
		while(token != NULL)
		{
			caminhos[c]=strdup(token);
			printf("%s\n",caminhos[c]);
			c++;
			token = strtok(NULL,":");
		}
		qtdCaminhos = c;

		Diretorio = strdup(getenv("PWD"));

		//Path_recuperaCaminho(&ListaPath);
		//DiretorioAtual = Path_imprimeCaminho(ListaPath);
	
		char* shellLine = (char*) malloc ((strlen(Diretorio)+2) * sizeof(char));
		sprintf(shellLine,"%s", Diretorio);
				

		//Imprime diretório atual em vermelho		
		Color_red(shellLine);	

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
			Terminal_InterpretaLinhaComando(LinhaComando, LinhasComando, caminhos, qtdCaminhos);
		
			//Incrementa Linha de Comando
			idLinhaComando++;		
		}
	}
	//Libera memória alocada
	free(LinhaComando);

	//Retorno
	return 1;
}
