#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

char *initializeVector() {
	char *v;

	v = (char *) malloc(sizeof(char)*41);
	if(v == NULL){
		printf("memory");
	}

	return v;
}

char **initializeMatrix(){
	char **trix;
	int i;
	
	trix = (char **) malloc (sizeof(char) * 41);
	for(i=0; i < 41; i++){
		trix[i] = (char *) malloc(sizeof(char) * 41);
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

int interpreter(char *v) {
	int i, j, k;
	char **aux, c, last, comm[20];
	/* aux eh uma matrix auxiliar */
	/* c guarda caracteres temporariamente */
	/* last guarda a posicao do ultimo espaco */

	aux = (char**) malloc (sizeof(char) * 41);
	for(i=0; i < 41; i++) {
		aux[i] = (char *) malloc(sizeof(char) * 41);
	}

	last = 0;
	k = 0;
	
	for(i=0; v[i] != '\0'; i++){
		c = v[i];
			
		if(c == ' '){
			for(j = last; j != i; j++) {
				aux[k][j-last] = v[j]; 
			}
			aux[k][j] = '\0';
			last = i+1;
			k++;
		}
	}

	for(i = last; v[i] != '\0'; i++) {
		aux[k][i] = v[i];
	}
	aux[k][i] = '\0';
	k++;

	k--;
	while(k >= 0){
		for(j=0; aux[k][j] != '\0'; j++){
			comm[j] = aux[k][j];
		}
		comm[j] = '\0';
		k--;

		printf("\n%s\n", comm);
	}

	return 0;
}

int main(void) {
	int i, j, loopProgram, commandLine;
	char c, *v, **trix;
	
	v = initializeVector();
	trix = initializeMatrix();

	loopProgram = 1;
	commandLine = 1;

	while(loopProgram) {
		/* lendo a linha de comando */

		for(i=0; c != '\n'; i++){
			c = getchar();

			v[i] = c;
		}	
		v[i] = '\0';
		c = 'x'; /* para evitar lixo */   

		printf("%s", v); /* - teste - imprime a linha de comando */

		parseLine(v, trix, commandLine);
		
		for(i=0; trix[commandLine][i] != '\0'; i++){
			printf("%c", trix[commandLine][i]);
		}

		interpreter(v);
				
		commandLine++;			
	}

	return 0;
}
