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

/*
* Função: initializeVector(void)
* Descrição: Aloca e retorna um vetor
*/
char *initializeVector(void) {
	//Variáveis	
	char *v;
	//Aloca o vetor 'v'
	v = (char *) malloc(sizeof(char)*1024);
	//Vetor não foi alocado
	if(v == NULL){
		printf("memory");
	}

	return v;
}

/*
* Função: initializeMatrix(void)
* Descrição: Aloca e retorna uma matriz
*/
char **initializeMatrix(void) {
	//Variáveis
	char **trix;
	int i;
	//Aloca a matriz 'trix'
	trix = (char **) malloc (sizeof(char) * 101);
	//Aloca cada vetor (linha) da matriz 'trix'
	for(i=0; i < 101; i++){
		trix[i] = (char *) malloc(sizeof(char) * 101);
	}
	return trix;
}

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
char* readLine(char *buffer, char **trix, int commandLine) {
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

			if(commandLine - linesOver > 0) {
				for(j=0; trix[commandLine-linesOver][j] != '\0'; j++) {
					buffer[j] = trix[commandLine-linesOver][j];
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
		else if(key[0] == 27 && key[1] == 91 && key[2] == 65 && linesOver > 0 && commandLine-linesOver > 1) {
			//Zera buffer das teclas
			flushKeys(key);
			//Apaga o buffer
			eraseWord(buffer);
			
			linesOver++;

			for(j=0; trix[commandLine-linesOver][j] != '\0'; j++) {
				buffer[j] = trix[commandLine-linesOver][j];
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
			for(j = 0; trix[commandLine - linesOver][j] != '\0'; j++){
				buffer[j] = trix[commandLine - linesOver][j];
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
* Função: parseLine (char*, char**, int)
* Descrição: Parseia uma Linha de Comando na Matriz
*/
int parseLine (char *v, char **trix, int commandLine) {
	int column;

	for(column=0; v[column] != '\0'; column++) {
		trix[commandLine][column] = v[column];	
	}
	
	trix[commandLine][column] = '\0';
	//Retorno
	return 0;
}

/*
* Função: runCommand (char*, char&, int, char**, char**, int)
* Descrição: * IMPLEMENTAR *
*/
int runCommand (char *path, char *v, int parNum, char **aux, char **trix, int runBg) {
	//Variáveis
	char temp[1000], temp2[1000];
	int i, j, k, status, pipe_to_file;
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
				if (i>= parNum)
					if (pipe_to_file==0) freopen ("/dev/tty", "a", stdout);
				else {
					dup2(fds[1], 1);
					close(fds[0]);
				}
				if (execv(args[0], args) == -1) {
					i=0;
					while (path[i]!='\0') {
						if (path[i]==':') {
							temp2[0]='\0';
							strcat(temp2, temp);
							strcat(temp2, "/");
							strcat(temp2, aux[0]);
							if (execv(temp2, args) != -1) break;
							temp[0]='\0';
							i++;
						}
						strncat(temp, (path+i), 1);
						i++;
					}
					if (path[i]=='\0') perror("ERRO");
				}
				exit(0);
			}      
		}
	}
	//Processo-pai
	else {
		/* IMPLEMENTAR */
	}
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
int interpreter (char *v, char **trix, char *path) {
	//Variáveis	
	int i, j, k, parNum, runBg;
	char **aux, c, last, comm[51];
	char currentPath[101];
	//Aloca a matriz 'aux'
	aux = (char**) malloc (sizeof(char) * 101);
	//Aloca cada vetor (linha) da matriz 'aux'
	for(i=0; i < 101; i++) {
		aux[i] = (char *) malloc(sizeof(char) * 101);
	}
	//Condições iniciais
	last = 0;
	k = 0;
	//Percorre o argumento
	for(i=0; v[i] != '\0'; i++){
		//Salva caractere atual em 'c'
		c = v[i];
		if(c == ' ') {
			for(j = last; j < i; j++) aux[k][j-last] = v[j];
			//Completa linha k da matriz 'aux' com caractere de escape: final de string
			aux[k][j-last] = '\0';
			//Incrementa última posição
			last = i+1;
			//Incrementa k
			k++;
		}
	}

	for(i = last; v[i] != '\0'; i++) {
		aux[k][i-last] = v[i];
	}
	//Completa linha k da matriz 'aux' com caractere de escape: final de string
	aux[k][i-last] = '\0';
	/* REVISAR */
	k++;

	k--;
	//Identifica o número do parâmetro
	parNum = k;
	while(k >= 0){
		for(j=0; aux[k][j] != '\0'; j++){
			comm[j] = aux[k][j];
		}
		comm[j] = '\0';
		k--;

		//printf("%s",comm);

		//Só há um parâmetro
		if(parNum == 0){
			//pwd
			if(strcmp(comm, "pwd") == 0) {
				getcwd(currentPath, 1000);
				printf("%s\n", currentPath);
			}
			//exit
			if(strcmp(comm, "exit") == 0 || strcmp(comm, "quit") == 0) {
				exit(0);
			}
			//cd
			if(strcmp(comm, "cd") == 0) {
				printf("Escolha o diretorio\n");
				/* IMPLEMENTAR */
			}
			//jobs
			if(strcmp(comm, "jobs") == 0) {
				Jobs_imprimeJobs(Jobs);
			}
			//terminate
			if (strcmp(comm, "terminate")==0) {
				/* IMPLEMENTAR */
			}
			
			if (strcmp(comm, "stop")==0) {
				/* IMPLEMENTAR */
			}
			
			if (strcmp(comm, "bg")==0) {
				/* IMPLEMENTAR */			
			}
			
			if (strcmp(comm, "fg")==0) {
				/* IMPLEMENTAR */	
			}
		}
		else {
			runBg = 0;
			runCommand(path, v, parNum, aux, trix, runBg);
		}
	}

	return 0;
}

int main(void) {
	//Variáveis
	int i, j, loopProgram, commandLine;
	char c, *v, **trix, *path, *currentPath;
	int count;	
	Job *Job;

	//Envia sinal de interrupção
	signal(SIGINT, Signal_capturaSigInt);
	//Envia sinal de parada assistida
	signal(SIGTSTP, Signal_capturaSigTSTP);
	
	//Propriedades do nó-cabeça Jobs
	Jobs.primeiroJob = NULL;
	Jobs.ultimoJob = NULL;
	Jobs.numJobs = 0;

	//Inicializa Tratamento de Linha de Comando
	trix = initializeMatrix();

	//Inicializa Tratamento de Argumento
	v = initializeVector();

	//Condições iniciais
	loopProgram = 1;
	commandLine = 1;

	//Aloca vetor 'path'
	path = (char *) malloc(sizeof(char) * 101);

	//Diretório atual
	currentPath =  (char *) malloc(sizeof(char) * 101);
	path = getenv("PATH");

	/* printf("%s", path); */
	
	//Limpa a tela
	system("clear");
	
	//Execução da rotina principal
	while(loopProgram) {
		//Retorna o diretório atual
		getcwd(currentPath, 1000);

		//Imprime diretório atual em vermelho		
		Color_red(currentPath);
		
		// Interpretando a Linha de Comando
		for(i=0; i < 101; i++){
			v[i] = '\0';
		}		

		//Ativa o modo não-canônico
		Canonical_setNonCanonicalMode();

		/*for(i=0; c != '\n'; i++){
			c = getchar();

			v[i] = c;
		}	
		v[i] = '\0';
		c = 'x';  para evitar lixo */

		//Lê a Linha de Comando
		v = readLine(v, trix, commandLine);

		//Retorna ao modo canônico
		Canonical_setCanonicalMode();
		
		//printf("%s\n", v);
		//printf("%s", v); /* - teste - imprime a linha de comando */
		

		//Armazena tamanho da Linha de Comando
		count = strlen(v);

		//printf("%d\n", count);

		//Parseia Linha de Comando
		parseLine(v, trix, commandLine);
		
		//for(i=0; trix[commandLine][i] != '\0'; i++){
		//	printf("%c", trix[commandLine][i]);
		//}
		//printf("\n");

		//Interpreta Linha de Comando
		interpreter(v, trix, path);
		
		//Incrementa Linha de Comando
		commandLine++;			
	}

	//Libera memória alocada em 'v'
	free(v);

	//Retorno
	return 1;
}
