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
#include "jobs.h"
#include "signal_capture.h"
#include "canonical.h"



#define TERMINAL_NUMLINHAS 128
#define TERMINAL_TAMANHOLINHA 1024
#define TERMINAL_TAMANHOPALAVRA 64
#define PATH_TAMANHO 128


/*
* Função: initializeVector(void)
* Descrição: Aloca e retorna um vetor
*/
//char *initializeVector(void) {
//	//Variáveis	
//	char *v;
//	//Aloca o vetor 'v'
//	v = (char *) malloc(sizeof(char)*1024);
//	//Vetor não foi alocado
//	if(v == NULL){
//		printf("memory");
//	}
//
//	return v;
//}

char* alocaVetor (int tamanhoVetor) {
	//Variáveis
	char *vetor;
	//Aloca o vetor
	vetor = (char*) malloc(sizeof(char)*tamanhoVetor);
	//Vetor não foi alocado
	if(vetor == NULL) {
		/* ERRO */
	}
	//Retorno
	return vetor;
}

char** alocaMatriz (int numLinhas, int tamanhoLinha) {
	//Variáveis
	char **matriz;
	int iLinha;
	//Aloca a matriz
	matriz = (char**) malloc(sizeof(char*) * numLinhas);
	//Matriz não foi alocada
	if(matriz == NULL) {
		/* ERRO_NAO_ALOCADO */
	}
	//Aloca vetores
	else {
		//Aloca cada vetor da matriz
		for(iLinha = 0; iLinha < numLinhas; iLinha++) {
			matriz[iLinha] = (char*) malloc(sizeof(char) * tamanhoLinha);
			//Vetor não foi alocado
			if(matriz[iLinha] == NULL){
				/* ERRO_NAO_ALOCADO */
			}
		}
	}
	//Retorno
	return matriz;	
}

/*
* Função: initializeMaLinhasComando(void)
* Descrição: Aloca e retorna uma matriz
*/
//DEPRECATED
//char **initializeMatrix(void) {
//	//Variáveis
//	char **matriz;
//	int i;
//	//Aloca a matriz 'trix'
//	LinhasComando = (char **) malloc (sizeof(char) * 101);
//	//Aloca cada vetor (linha) da matriz 'trix'
//	for(i=0; i < 101; i++){
//		LinhasComando[i] = (char *) malloc(sizeof(char) * 101);
//	}
//	return LinhasComando;
//}

/*
* Função: flushKeys(char)
* Descrição: Limpa o buffer reservado para determinadas teclas
*/
void flushKeys(char *key) {
	key[0] = key[1] = key[2] = 0;
}

/*
* Função: eraseWord(char*)
* Descrição: Apaga conjuntos de caracteres do buffer impresso em tela
*/
void eraseWord(char *bufferAux) {
	//Variáveis
	int i;
	//Rotina
	for(i = 0; i < strlen(bufferAux); i++) printf("\b \b");
}

/*
* Função: readLine(char*, char**, int)
* Descrição: Lê e controla a Linha de Comando, de modo não-canônico
*/
char* readLine(char *buffer, char **LinhasComando, int idLinhaComando) {
	//Variáveis
	char c;
	int i, j, k, keyIndex;
	char key[3];
	char bufferAux[100];
	int linesOver;
	//Condições iniciais
	keyIndex = 0;
	linesOver = 0;
	//Preenche os vetores de buffer com caracteres de escape: final de string
	for(i=0; i < 100; i++){
		buffer[i] = '\0';
		bufferAux[i] = '\0';
	}
	i = j = k = 0;
	//Zera buffer das teclas
	flushKeys(key);
	
	while((c = getchar()))
	{	
		key[keyIndex] = c;
		keyIndex++;
		
		if(keyIndex > 2) keyIndex = 0;
			
		//Cima	
		if(key[0] == 27 && key[1] == 91 && key[2] == 65 && linesOver == 0) {
			//Zera buffer das teclas
			flushKeys(key);
			//Armazena buffer
			for(j=0; j < strlen(buffer); j++){
				bufferAux[j] = buffer[j];
			}
			//Completa a string buffer com '\0'
			bufferAux[j] = '\0';
			//Apaga o buffer
			eraseWord(bufferAux);

			linesOver++;

			if(idLinhaComando - linesOver > 0) {
				for(j=0; LinhasComando[idLinhaComando-linesOver][j] != '\0'; j++) {
					buffer[j] = LinhasComando[idLinhaComando-linesOver][j];
				}
				//Completa a string buffer com '\0'
				buffer[j] = '\0';			
			}
			//Armazena tamanho do buffer
			i = strlen(buffer);
			//Imprime buffer
			printf("%s", buffer);
		}
		//Cima
		else if(key[0] == 27 && key[1] == 91 && key[2] == 65 && linesOver > 0 && idLinhaComando-linesOver > 1) {
			//Zera buffer das teclas
			flushKeys(key);
			//Apaga o buffer
			eraseWord(buffer);
			
			linesOver++;

			for(j=0; LinhasComando[idLinhaComando-linesOver][j] != '\0'; j++) {
				buffer[j] = LinhasComando[idLinhaComando-linesOver][j];
			}
			//Completa a string buffer com '\0'
			buffer[j] = '\0';
			//Armazena tamanho do buffer
			i = strlen(buffer);
			//Imprime buffer
			printf("%s", buffer);
		}
		//Baixo
		else if(key[0] == 27 && key[1] == 91 && key[2] == 66 && linesOver == 1)
		{
			//Zera buffer das teclas
			flushKeys(key);

			eraseWord(buffer);

			linesOver--;
			for(j=0; bufferAux[j] != '\0'; j++){
				buffer[j] = bufferAux[j];
			}
			buffer[j] = '\0';

			i = strlen(buffer);

			printf("%s", buffer);
		}
		else if(key[0] == 27 && key[1] == 91 && key[2] == 66 && linesOver > 1){
			//Zera buffer das teclas
			flushKeys(key);

			eraseWord(buffer);

			linesOver--;
			for(j = 0; LinhasComando[idLinhaComando - linesOver][j] != '\0'; j++){
				buffer[j] = LinhasComando[idLinhaComando - linesOver][j];
			}
			//Completa a string buffer com '\0'
			buffer[j] = '\0';
			//Armazena tamanho do buffer
			i = strlen(buffer);
			//Imprime buffer
			printf("%s", buffer);
				
		}
		//CTRL+L
		else if(key[0] == 12 || key[1] == 12 || key[2] == 12) {
			//Zera buffer das teclas
			flushKeys(key);
			//Limpa a tela
			system("clear");
			//printf("%s", fullPrompt());
		}
		//CTRL+C
		else if(key[0] == 3 || key[1] == 3 || key[2] == 3) {
			//Zera buffer das teclas
			flushKeys(key);
			strcpy(buffer,"CTRLC");
			break;
		}
		//CTRL+D
		else if(key[0] == 4 || key[1] == 4 || key[2] == 4) {
			//Zera buffer das teclas
			flushKeys(key);
			strcpy(buffer,"CTRLD");
			break;
		}
		//CTRL+Z		
		else if(key[0] == 26 || key[1] == 26 || key[2] == 26)
		{	
			flushKeys(key);
			strcpy(buffer,"CTRLZ");
			break;
		}
		//Nenhuma tecla acima
		else if(key[0] != 27 && key[0] != 12 && key[0] != 4 && key[0] != 26 && key[0] != 3) {
			//Zera buffer das teclas
			flushKeys(key);
			//Imprime as teclas na tela
			if(c >= 32 && c <= 126) 
			{
				printf("%c", c);
				buffer[i++] = c;
				buffer[i] = '\0';
			}
			
			//Enter 
			else if(c == 13)
			{
				//Nada foi digitado
				if(buffer[0] == '\0') break;
				//Algo foi digitado
				else {
					printf("%c\n", c);
					break;
				}		
			}
			//Backspace
			else if(c == 127 && i > 0)
			{
				printf("\b \b");	
				i--;
				buffer[i]='\0';
			}
		}	
	
	}
	return buffer;
}

/* 
* Função: Terminal_insereLinhaNoHistorico (char*, char**, int)
* Descrição: Insere uma Linha de Comando no Histórico de Linhas
*/
int Terminal_insereLinhaNoHistorico (char *LinhaComando, char **LinhasComando, int idLinhaComando) {
	strcpy(LinhasComando[idLinhaComando],LinhaComando);	
	
	//DEPRECATED
	//int column;
	//for(column=0; v[column] != '\0'; column++) {
	//	LinhasComando[idLinhaComando][column] = v[column];	
	//}
	//	
	//LinhasComando[idLinhaComando][column] = '\0';
	
	//printf("\n\nResposta do Terminal_insereLinhaNoHistorico: %s\n\n",LinhasComando[0]);
	
	//Retorno
	return 0;
}

/*
* Função: runCommand (char*, char&, int, char**, char**, int)
* Descrição: * Roda os comandos não built-in *
*/
int runCommand (char *Diretorio, char *v, int parNum, char **aux, char **LinhasComando, int runBg) {
	//Variáveis
	char temp[1000], temp2[1000];
	int i, k, status, pipe_to_file;
	int fds[2];
	pid_t pid, pid2;
	char *args[100];
	//Entrada e Saída
	FILE *ori_stdin = stdin;
	FILE *ori_stdout = stdout;
	FILE *ori_stderr = stderr;

	//Cria novo processo
	pid = fork();
	//Falha na criação do processo
	if(pid<0) printf("Erro na criacao do processo.\n");
	//Processo filho criado
	else if(pid == 0) { 
		//Define o ID do grupo de processos
		setpgid(0,0);
		i = 0;
		//Rotina executada para cada parâmetro
		while(i < parNum) {
			k = 0;
			//Limpa buffer
			fflush(0);
			pipe_to_file = 0;
			while(i < parNum) {
			//Término de um comando
			if (strcmp(aux[i], "|") == 0) {
				i++;
				break;
			}
			//Saída para um arquivo
			else if (strcmp(aux[i], ">") == 0) {
				i++;
				freopen (aux[i], "w", stdout);
				pipe_to_file=1;
			}
			//Entrada de um arquivo
			else if (strcmp(aux[i], "<") == 0) {
				i++;
				freopen (aux[i], "r", stdin);
			}
			//Saída para um arquivo com append
			else if (strcmp(aux[i], ">>") == 0) {
				i++;
				freopen (aux[i], "a", stdout);
				pipe_to_file=1;
			}
			//Saída de erros para um arquivo
			else if (strcmp(aux[i], "2>") == 0) {
				i++;
				freopen (aux[i], "w", stderr);
			}
			else {
				args[k]= aux[i];
				k++;
			}
			i++;
		}
			args[k] = NULL;
			
			/*if(pipe(fds)){
				fprintf(ori_stdout,"Pipe error\n");
			}*/
			
			pid2 = fork();
			if (pid2<0) fprintf(ori_stdout,"Não foi possível executar o fork(), abortando execução do comando");
			//Processo filho			
			else if (pid2==0) {
				dup2(fds[0], 0);
				close(fds[1]);
				if (i>= parNum) exit(0);
			}
			else {
				if (i>= parNum) {
					if (pipe_to_file==0) freopen ("/dev/tty", "a", stdout);
				}
				else {
					dup2(fds[1], 1);
					close(fds[0]);
				}
				if (execv(args[0], args) == -1) {
					i=0;
					while (Diretorio[i]!='\0') {
						if (Diretorio[i]==':') {
							temp2[0]='\0';
							strcat(temp2, temp);
							strcat(temp2, "/");
							strcat(temp2, aux[0]);
							if (execv(temp2, args) != -1) break;
							temp[0]='\0';
							i++;
						}
						strncat(temp, (Diretorio+i), 1);
						i++;
					}
					if (Diretorio[i]=='\0') perror("ERRO");
				}
				exit(0);
			}      
		}
	}
	//Processo-pai
	else {
		/* IMPLEMENTAR */
	}
	/* REVISAR */
	return 1;
}

/* 
* Função: interpreter (char*, char**, char*)
* Descrição: Interpreta a Linha de Comando digitada
* Comentários adicionais:
* A matriz de caracteres 'aux' guardará temporariamente cada comando em uma linha
* O caractere 'c' guardará temporariamente caracteres
* O caractere 'last' guardará temporariamente a posição do último espaço
* O vetor de caracteres 'comm' guardará o comando que será tratado no momento
*/
int Terminal_InterpretaLinhaComando (char *LinhaComando, char **LinhasComando, char *Diretorio) {
	//Variáveis	
	int numParametros, runBg, idPalavra, contadorParametros;
	char **Parametro, Comando[TERMINAL_TAMANHOPALAVRA], *tokenPalavra;
	char DiretorioAtual[101];
	
	//Aloca a matriz 'aux'
	Parametro = alocaMatriz((TERMINAL_TAMANHOLINHA/TERMINAL_TAMANHOPALAVRA),TERMINAL_TAMANHOPALAVRA);
		
	//Condições iniciais
	idPalavra = 0;
	
	//Quebra Linha de Comando em Palavras
	tokenPalavra = alocaVetor(TERMINAL_TAMANHOPALAVRA);
	tokenPalavra = (char*) strtok(LinhaComando, " ");
	while(tokenPalavra != NULL) {
		//Salva palavra
		strcpy(Parametro[idPalavra],tokenPalavra);
		//Percorre o token
		tokenPalavra = (char*) strtok(NULL, " ");
		//Incrementa o número de palavras
		idPalavra++;
	}
		
	//Salva número de parâmetro
	numParametros = idPalavra;

	//Começa o contador na última posição
	contadorParametros = numParametros;
	
	//Rotina para cada palavra
	while(contadorParametros >= 0) {
		//Decrementa contador
		contadorParametros--;

		//Armazena palavra
		strcpy(Comando, Parametro[contadorParametros]);

		//printf("%s",comm);

		//Primeiro parâmetro
		if(contadorParametros == 0){
			//pwd
			if(strcmp(Comando, "pwd") == 0) {
				//Recupera e imprime diretório atual
				getcwd(DiretorioAtual, 1000);
				printf("%s\n", DiretorioAtual);
			}
			//exit
			if(strcmp(Comando, "exit") == 0 || strcmp(Comando, "quit") == 0) {
				//Sai do terminal				
				exit(0);
			}
			//cd
			if(strcmp(Comando, "cd") == 0) {
				/* IMPLEMENTAR */
				//DEPRECATED
				//printf("Escolha o diretorio\n");
				/*
				if (chdir(v[1])==-1) perror("ERRO");
				*/
			}
			//jobs
			if(strcmp(Comando, "jobs") == 0) {
				Jobs_imprimeJobs(Jobs);
			}
			//terminate
			if (strcmp(Comando, "terminate")==0) {
				/* IMPLEMENTAR */
			}
			
			if (strcmp(Comando, "stop")==0) {
				/* IMPLEMENTAR */
			}
			
			if (strcmp(Comando, "bg")==0) {
				/* IMPLEMENTAR */			
			}
			
			if (strcmp(Comando, "fg")==0) {
				/* IMPLEMENTAR */	
			}
		}
		//Demais parâmetros
		else {
			//
			runBg = 0;
			//Roda comando
			runCommand(Diretorio, LinhaComando, contadorParametros, Parametro, LinhasComando, runBg);
		}
	}
	//Retorno
	return 0;
}

int main(void) {
	//Variáveis
	int loopProgram, idLinhaComando;
	//int count;
	//char c;
	char *LinhaComando, **LinhasComando;
	char *Diretorio, *DiretorioAtual;
	Job *Job;

	/* REVISAR */	
	//Envia sinal de interrupção
	signal(SIGINT, Signal_capturaSigInt);
	//Envia sinal de parada assistida
	signal(SIGTSTP, Signal_capturaSigTSTP);
	
	//Propriedades da Lista
	Jobs.primeiroJob = NULL;
	Jobs.ultimoJob = NULL;
	Jobs.numJobs = 0;

	//Aloca Linhas de Comando
	LinhasComando = alocaMatriz(TERMINAL_NUMLINHAS, TERMINAL_TAMANHOLINHA);
	
	//LinhasComando = initializeMaLinhasComando();

	//Aloca Cada Linha de Comando
	LinhaComando = alocaVetor(TERMINAL_TAMANHOLINHA);
		
	//v = initializeVector();

	//Condições iniciais
	loopProgram = 1;
	idLinhaComando = 1;

	//Aloca vetor 'Diretorio'
	Diretorio = alocaVetor(TERMINAL_TAMANHOLINHA);

	//Diretorio = (char *) malloc(sizeof(char) * 101);

	//Aloca Diretório atual
	DiretorioAtual = alocaVetor(TERMINAL_TAMANHOLINHA);

	//DiretorioAtual =  (char *) malloc(sizeof(char) * 101);
	
	Diretorio = getenv("PATH");

	//DEPRECATED
	//printf("%s", Diretorio);
	
	//Limpa a tela
	system("clear");
	
	//Execução da rotina principal
	while(loopProgram) {
		//Retorna o diretório atual
		getcwd(DiretorioAtual, 1000);

		//Imprime diretório atual em vermelho		
		Color_red(DiretorioAtual);
		
		//for(i=0; i < 101; i++){
		//	v[i] = '\0';
		//}		

		//Ativa o modo não-canônico
		Canonical_setNonCanonicalMode();

		//DEPRECATED
		/*for(i=0; c != '\n'; i++){
			c = getchar();

			v[i] = c;
		}	
		v[i] = '\0';
		c = 'x';  para evitar lixo*/

		//Lê a Linha de Comando
		LinhaComando = readLine(LinhaComando, LinhasComando, idLinhaComando);

		//Retorna ao modo canônico
		Canonical_setCanonicalMode();
		
		//DEPRECATED
		//printf("%s\n", v);
		//printf("%s", v); /* - teste - imprime a linha de comando */
		
		//DEPRECATED - Armazena tamanho da Linha de Comando
		//count = strlen(v);
		//printf("%d\n", count);

		//Parseia Linha de Comando
		Terminal_insereLinhaNoHistorico(LinhaComando, LinhasComando, idLinhaComando);
		
		//DEPRECATED
		//for(i=0; LinhasComando[idLinhaComando][i] != '\0'; i++){
		//	printf("%c", LinhasComando[idLinhaComando][i]);
		//}
		//printf("\n");

		//Interpreta Linha de Comando
		Terminal_InterpretaLinhaComando(LinhaComando, LinhasComando, Diretorio);
		
		//Incrementa Linha de Comando
		idLinhaComando++;		
	}

	//Libera memória alocada em 'v'
	free(LinhaComando);

	//Retorno
	return 1;
}
