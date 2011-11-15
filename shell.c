#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>

// ANSI-Cores
#define C_RED		"\033[91m"
#define C_GREEN        	"\033[92m"
#define C_ORANGE     	"\033[93m"
#define C_BLUE         	"\033[94m"
#define C_PINK         	"\033[95m"
#define C_CYAN        	"\033[96m"
#define C_WHITE       	"\033[97m"
#define C_BLACK        	"\033[90m"
#define RESTORE       	"\033[00m"
 
// Funcoes de cores
void red (char string[]) {
	printf("%s%s $%s ", C_RED, string, RESTORE);
}
 
void green (char string[]) {
	printf("%s%s $%s ", C_GREEN, string, RESTORE);
}
 
void orange (char string[]) {
	printf("%s%s $%s ", C_ORANGE , string, RESTORE);
}
 
void blue(char string[]) {
	printf("%s%s $%s ", C_BLUE, string, RESTORE);
}
 
void pink(char string[]) { 
	printf("%s%s $%s ", C_PINK, string, RESTORE);
}
 
void cyan(char string[]) {
	printf("%s%s $%s ", C_CYAN, string, RESTORE);
}
 
void white (char string[]) { 
	printf("%s%s $%s ", C_WHITE, string, RESTORE);
}
 
void black (char string[]) {
	printf("%s%s $%s  ", C_BLACK, string, RESTORE);
}

char *initializeVector() {
	char *v;

	v = (char *) malloc(sizeof(char)*101);
	if(v == NULL){
		printf("memory");
	}

	return v;
}

char **initializeMatrix(){
	char **trix;
	int i;
	
	trix = (char **) malloc (sizeof(char) * 101);
	for(i=0; i < 101; i++){
		trix[i] = (char *) malloc(sizeof(char) * 101);
	}
	return trix;
}

int parseLine(char *v, char **trix, int commandLine) {
	int column;

	for(column=0; v[column] != '\0'; column++){
		trix[commandLine][column] = v[column];	
	}
		trix[commandLine][column] = '\0';

	return 0;
}

int runCommand(char *path, char *v, int parNum, char **trix, int runBg) {
	int i, j, k;
	pid_t pid;

	/* Criando novo processo */
	pid = fork();
	if(pid < 0 ) {
		printf("Erro na criacao do processo.\n");
	}
	else
	if(pid == 0) { // Processo Filho
		setpgid(0,0);
		i = 0;
		while(i < parNum) {
			
		}
	}
}

int interpreter(char *v, char **trix, char *path) {
	int i, j, k, parNum, runBg;
	char **aux, c, last, comm[51];
	char currentPath[101];
	/* aux eh uma matrix auxiliar */
	/* c guarda caracteres temporariamente */
	/* last guarda a posicao do ultimo espaco */


	aux = (char**) malloc (sizeof(char) * 101);
	for(i=0; i < 101; i++) {
		aux[i] = (char *) malloc(sizeof(char) * 101);
	}

	last = 0;
	k = 0;
	
	for(i=0; v[i] != '\0'; i++){
		c = v[i];
			
		if(c == ' '){
			for(j = last; j < i; j++) {
				aux[k][j-last] = v[j]; 
			}
			aux[k][j-last] = '\0';
			last = i+1;
			k++;
		}
	}

	for(i = last; v[i] != '\0'; i++) {
		aux[k][i-last] = v[i];
	}
	aux[k][i-last] = '\0';
	k++;

	k--;

	parNum = k;
	while(k >= 0){
		for(j=0; aux[k][j] != '\0'; j++){
			comm[j] = aux[k][j];
		}
		comm[j-1] = '\0';
		k--;
		
		/* se tiver soh 1 parametro */
		if(parNum == 0){
			/* pwd */
			if(strcmp(comm, "pwd") == 0) {
				getcwd(currentPath, 1000);
				printf("%s\n", currentPath);
			}
			if(strcmp(comm, "exit") == 0 || strcmp(comm, "quit") == 0) {
				exit(0);
			}
			if(strcmp(comm, "cd") == 0) {
				printf("Escolha o diretorio\n");
			}
			if(strcmp(comm, "jobs") == 0) {
				printf("Imprimir os jobs\n");
			}
		}
		else {
			runBg = 0;
			runCommand(path, v, parNum, trix, runBg);
		}
	}

	return 0;
}

int main(void) {
	int i, j, loopProgram, commandLine;
	char c, *v, **trix, *path, *currentPath;
	
	trix = initializeMatrix();
	v = initializeVector();

	loopProgram = 1;
	commandLine = 1;

	path = (char *) malloc(sizeof(char) * 101);
	currentPath =  (char *) malloc(sizeof(char) * 101);

	path = getenv("PATH");
	/* printf("%s", path); */

	while(loopProgram) {
		getcwd(currentPath, 1000); /* Caminho para diretorio atual */
		red(currentPath);
		
		/* lendo a linha de comando */
		for(i=0; i < 101; i++){
			v[i] = '\0';
		}		


		for(i=0; c != '\n'; i++){
			c = getchar();

			v[i] = c;
		}	
		v[i] = '\0';
		c = 'x'; /* para evitar lixo */   

		//printf("%s", v); /* - teste - imprime a linha de comando */

		parseLine(v, trix, commandLine);
		
		/*for(i=0; trix[commandLine][i] != '\0'; i++){
			printf("%c", trix[commandLine][i]);
		}*/

		interpreter(v, trix, path);
		
		commandLine++;			
	}

	free(v);		

	return 0;
}
