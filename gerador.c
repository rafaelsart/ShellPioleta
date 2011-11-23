#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(void) {
	int i, j, k, stopDentro, stopFora, tamanho;
	FILE *arquivo;
	char *bufferFora, *bufferDentro;

	stopFora = stopDentro = 0;
	printf("\n");
	arquivo = fopen("listaComandos.txt", "r+");


	if(arquivo != NULL){
		while (stopFora != 1) {
			bufferFora = (char *) malloc (sizeof(char) * 256);
			
			if(fgets(bufferFora, 300, arquivo) != NULL) {
				bufferFora[strlen(bufferFora) - 1] = '\0';

				if(strcmp(bufferFora, "") != 0){
					printf("%s \n", bufferFora);
				}
					
			}
			else {
				stopFora = 1;
			}
		
			free(bufferFora);
		}

		fclose(arquivo);
	}
	else {
		printf("Nao foi possivel abrir o arquivo\n");
	}
	
	

 	return 0;
}
