#include <stdio.h>

int parseLine(char *v, char trix[40][40], int commandLine) {
	int column;

	for(column=0; v[column] != '\0'; column++){
		trix[commandLine][column] = v[column];	
	}
		trix[commandLine][column] = '\0';
}

int main(void) {
	int i, j, loopProgram, commandLine;
	char c, v[40];
	char trix[40][40];

	for(i=0; i < 40; i++){
		for(j=0; j < 40; j++){
			trix[i][j] = 'x';
		} 
	} 

	loopProgram = 1;
	commandLine = 1;

	while(loopProgram){
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

		// interpreter(trix);
				
		commandLine++;			
	}

	return 0;
}
