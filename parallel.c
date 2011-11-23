#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(void) {
	int i, j, k, stopDentro, stopFora tamanho;
	FILE *arquivo;
	char *bufferFora, *bufferDentro;

	stop = stop2 = 0;
	printf("\n");
	arquivo = fopen("listaComandos.txt", "r+");


	if(arquivo != NULL){

		while (stopFora != 1) {
			bufferFora = (char *) malloc (sizeof(char) * 256);
			
			if(fgets(bufferFora, 300, arquivo) != NULL) {
				tamanho = ftell(arquivo);
					
				rewind(arquivo);
				while(stopDentro != 1) {
					bufferDentro = (char *) malloc (sizeof(char) * 256);
				
					if(fgets(bufferDentro, 300, arquivo) != NULL){
						
						for(j=0; bufferFora[j] != '\0' ; j++){
							for(k=0; bufferDentro[k] != '\0'; k++){
								if(strcmp(bufferFora, bufferDentro) ==0){
									//Compara letra por letra
									//
									// se  for igual ganha 1 ponto
									// senão ganha 0
									// palavra com mais ponto de Dentro é marcada com a palavra de Fora
									// se strlen
										
								}
							}	
						}
					}
					else {
						stopDentro = 1;	
					}
	
					free(bufferDentro);
				}
			
			}
			else {
				stopFora = 1;
			}
		
			fseek(arquivo, tamanho, SEEK_SET);
			free(bufferFora);
		}

		fclose(arquivo);
	}
	else {
		printf("Nao foi possivel abrir o arquivo\n");
	}
	

 	return 0;
}
