//Inclusão de bibliotecas do sistema
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

//Inclusão de bibliotecas próprias
#include "tela.h"
#include "alocacao.h"
#include "jobs.h"
#include "signal_capture.h"
#include "canonical.h"
#include "terminal.h"
#include "comando.h"

int Comando_isBuiltIn (char **Parametro) {
	//cd
	if(strcmp(Parametro[0], "cd") == 0) return 1;

	//exit
	if(strcmp(Parametro[0], "exit") == 0 || strcmp(Parametro[0], "quit") == 0) return 1;

	//bg	
	if(strcmp(Parametro[0], "bg") == 0) return 1;

	//fg
	if(strcmp(Parametro[0], "fg") == 0) return 1;

	//bgcurjob
	if(strcmp(Parametro[0], "bgcurjob") == 0) return 1;

	//fgcurjob
	if(strcmp(Parametro[0], "fgcurjob") == 0) return 1;
	
	//jobs
	if(strcmp(Parametro[0], "jobs") == 0) return 1;

	return 0;
}

void Comando_rodaBuiltIn (char **Parametro) {
	//Variáveis
	pid_t pid;

	//exit
	if(strcmp(Parametro[0], "exit") == 0 || strcmp(Parametro[0], "quit") == 0) exit(0);

	//cd
	if(strcmp(Parametro[0], "cd") == 0) {
		if(Parametro[1] != NULL && strcmp(Parametro[1],"") != 0)
			if (chdir(Parametro[1]) == -1) perror("ERRO");
	}

	//jobs
	if(strcmp(Parametro[0], "jobs") == 0) Jobs_imprimeJobs(Jobs);

	//bg
	if (strcmp(Parametro[0], "bg") == 0) {
		if(Parametro[1]) {
			pid = strtol(Parametro[1], NULL, 10);
			Jobs_colocaJobEmBackground(&Jobs,pid);
		}
		else printf("Uso: bg <id>\n");
	}

	//fg
	if (strcmp(Parametro[0], "fg") == 0) {
		if(Parametro[1]) {
			pid = strtol(Parametro[1], NULL, 10);
			Jobs_colocaJobEmForeground(&Jobs,pid);
			//waitpid(pid, NULL, 0);
		}
		else printf("Uso: bg <id>\n");
	}

	//bgcurjob
	if (strcmp(Parametro[0], "bgcurjob") == 0) {
		Jobs_imprimeJobs(Jobs);
		Jobs_colocaJobEmBackground(&Jobs,Jobs.currentForegroundJob->pid);
	}

	//fgcurjob
	if (strcmp(Parametro[0], "fgcurjob") == 0) {
		//waitpid(Jobs.ultimoJob->pid, NULL, 0);
		Jobs_colocaJobEmForeground(&Jobs,Jobs.currentForegroundJob->pid);
	}
}

void Comando_rodaLinhaComando (char **Parametro, int numParametros, int status) {
	//Variáveis
	pid_t pidNovoProcesso;
	char *tokenPath;
	int iContador=0, iPath = 0;

	//Cria processo-filho
	pidNovoProcesso = fork();

	//Falha na criação
	if(pidNovoProcesso == -1) {
		perror("Nao foi possivel criar o processo.\n");
		exit(0);
	}

	//Processo ativo
	else if(pidNovoProcesso == 0) {
		//Aloca caminho
		Path = (char**) malloc(((strlen(getenv("PATH"))/2)+2)*sizeof(char*));

		//Quebra PATH em diretórios
		tokenPath = (char*) strtok(getenv("PATH"), ":");

		//Rotina
		while(tokenPath != NULL) {
			//Aloca e inicializa caminho
			Path[iPath] = Alocacao_alocaVetor(strlen(tokenPath)+1);
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
			//Aloca Caminho
			char Caminho[(strlen(Path[iContador])+strlen(*Parametro)+2)];
			strcpy(Caminho,Path[iContador]);
			strcat(Caminho,"/");
			strcat(Caminho, *Parametro);
			//Desaloca memória
			free(Path[iContador]);
			//Tela_apagaCaracteres(TERMINAL_TAMANHOLINHA);
			execv(Caminho, Parametro);
		}

		//Erro
		fprintf(stderr,"Comando nao reconhecido.\n");
		exit(EXIT_FAILURE);
	}

	//Processo-pai	
	else {
		//Define ID do grupo de processos
		setpgid(pidNovoProcesso,0);

		//Cria um job e adiciona à lista
		Jobs_adicionaJob(&Jobs, Parametro[0], pidNovoProcesso, status, RODANDO);

		//Espera em caso de FOREGROUND
		if(status == FOREGROUND) waitpid(pidNovoProcesso, NULL, 0);
		else {
			Jobs_imprimeJobs(Jobs);
			Tela_apagaCaracteres(TERMINAL_TAMANHOLINHA);
		}
	}

	//Desaloca memória
	free(Path);

	//Retorno
	return;
}
