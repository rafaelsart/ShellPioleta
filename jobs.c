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
#include "jobs.h"
#include "terminal.h"
#include "tela.h"

/*
* Função	: Jobs_adicionaJob (JobHeader, pid_t)
* Descrição	: Remove a Job buscada da Lista de Jobs
* Parâmetros:
* JobHeader *L	: Nó-Cabeça da Lista de Jobs (modificado em caso de remoção bem-sucedida)
* pid_t pid	: ID da Job a ser buscada
* Retorno	: void
*/
void Jobs_adicionaJob (JobHeader *L, char *comando, pid_t pid, int status, int statusExecucao) {
	//Variáveis
	Job *jobAux;
	Job *jobNovo;

	//Aloca um elemento struct job
	jobAux = (Job*) malloc(sizeof(struct job));

	//Falha na alocação	
	if(jobAux == NULL) return;
	//Alocado com sucesso	
	else {
		//Informações de jobAux
		jobAux->id = L->numJobs;
		jobAux->pid = pid;
		jobAux->comando = (char*) malloc(strlen(comando)*sizeof(char));
		strcpy(jobAux->comando,comando);
		jobAux->status = status;
		jobAux->statusExecucao = statusExecucao;
		jobAux->prox = NULL;

		//Cria primeiro elemento
		if(L->primeiroJob == NULL) {
			L->primeiroJob = jobAux;
			L->ultimoJob = jobAux;
		}
		//Procura o ponto de inserção
		else {
			jobNovo = L->ultimoJob;
			jobNovo->prox = jobAux;
			L->ultimoJob = jobAux;
		}
		//Atualiza número de Jobs
		L->numJobs++;
	}
}

/*
* Função	: Jobs_removeJob (JobHeader, pid_t)
* Descrição	: Remove a Job buscada da Lista de Jobs
* Parâmetros:
* JobHeader *L	: Nó-Cabeça da Lista de Jobs (modificado em caso de remoção bem-sucedida)
* pid_t pid	: ID da Job a ser buscada
* Retorno	: void
*/
void Jobs_removeJob (JobHeader *L, pid_t pid) {
	//Variáveis
	Job *jobAux;
	Job *jobInicio;
	//Armazena o primeiro elemento da lista 
	jobInicio = L->primeiroJob;
	//Lista não-vazia
	if(jobInicio != NULL) {
		//Remoção no início		
		if(jobInicio->pid == pid) {
			//Salva o elemento a ser removido
			jobAux = jobInicio;
			//Atualiza a Lista
			L->primeiroJob = jobInicio->prox;
			//Lista de tamanho 1
			if(L->numJobs == 1) L->ultimoJob = L->primeiroJob;
			//Libera a memória alocada
			free(jobAux);
		}
		//Procura o ponto de remoção
		else {
			//Percorre o primeiro elemento da lista e salva o atual
			jobAux = jobInicio;
			jobInicio = jobInicio->prox;
			while(jobInicio != NULL) {
				if(jobInicio->pid == pid) {
					//Último elemento da lista
					if(jobInicio == L->ultimoJob) L->ultimoJob = jobAux;
					//Atualiza a lista
					jobAux->prox = jobInicio->prox;
					//Libera a memória alocada
					free(jobInicio);
				}
				//Percorre a lista
				jobAux = jobInicio;
				jobInicio = jobInicio->prox;
			}
		}
	}
}

/*
* Função	: Jobs_retornaJobComPID (JobHeader, pid_t)
* Descrição	: Retorna a Job com o PID buscado
* Parâmetros:
* JobHeader *L	: Nó-Cabeça da Lista de Jobs
* pid_t pid	: ID da Job a ser buscada
* Retorno	: Job Buscada
*/
Job* Jobs_retornaJobComPID (JobHeader *L, pid_t pid) {
	//Variáveis	
	Job *jobAux;

	//Copia a lista
	jobAux = L->primeiroJob;

	//Percorre a lista
	while(jobAux != NULL) {
		if(jobAux->pid == pid) return jobAux;
		jobAux = jobAux->prox;
	}
	//Não encontrado
	return NULL;
}
	

/*
* Função	: Jobs_colocaJobEmBackground (JobHeader*, pid_t)
* Procura pela Job de ID pid e coloca em BACKGROUND com as devidas alterações
* Parâmetros:
* JobHeader L	: Nó-Cabeça da Lista de Jobs
* pid_t pid	: ID da Job a ser colocada em BACKGROUND
* Retorno	: void
*/
void Jobs_colocaJobEmBackground (JobHeader *L, pid_t pid) {
	//Variáveis
	Job *jobAux;
	//Copia a lista
	jobAux = L->primeiroJob;
	//Rotina de pesquisa da Lista
	while (jobAux != NULL) {
		//Procura Job desejado	       
		if (jobAux->pid == pid) {
			//O Job já TERMINOU			
			if(jobAux->statusExecucao == TERMINOU) {
				printf("Job ja terminou.\n");
				return;
			}
			//O Job ainda está RODANDO
			else if(jobAux->statusExecucao == RODANDO){
				//Atualiza job
				jobAux->status = BACKGROUND;

				//Continua processo
				kill(jobAux->pid,SIGCONT);
				return;
			}
		}
		//Percorre a lista
		jobAux = jobAux->prox;
	}
	//Job não encontrado
	printf("\nJob nao encontrado.\n");
}

/*
* Função	: Jobs_colocaJobEmForeground (JobHeader*, pid_t)
* Procura pela Job de ID pid e coloca em FOREGROUND com as devidas alterações
* Parâmetros:
* JobHeader L	: Nó-Cabeça da Lista de Jobs
* pid_t pid	: ID da Job a ser colocada em FOREGROUND
* Retorno	: void
*/
void Jobs_colocaJobEmForeground (JobHeader *L, pid_t pid) {
	//Variáveis
	Job *jobAux;
	int estado;

	//Copia a lista
	jobAux = L->primeiroJob;
	//Rotina de pesquisa da Lista
	while (jobAux != NULL) {
		//Procura Job desejado
		if (jobAux->pid == pid) {
			//O Job já terminou			
			if(jobAux->statusExecucao == TERMINOU) {
				printf("Job ja terminou.\n");
				//Retorno
				return;
			}
			
			//O job já está em FOREGROUND
			if(jobAux->status == FOREGROUND) {
				printf("Job ja esta rodando em foreground.\n");
				//Retorno
				return;
			}

			//O job está RODANDO em BACKGROUND
			if(jobAux->statusExecucao == RODANDO && jobAux->status == BACKGROUND) {
				//Atualiza job
				jobAux->status = FOREGROUND;
				jobAux->statusExecucao = RODANDO;

				//Aguarda o filho responder
				waitpid(-1*(jobAux->pid),&estado,WUNTRACED);

				//A Job está PARADA (Comando digitado: Ctrl+Z)
				if (WIFSTOPPED(estado)) {
					//Atualiza status da Job
					jobAux->status = BACKGROUND;
					jobAux->statusExecucao = PAUSADO;
					return;
				}
				//Estado inatingível
				if(WIFCONTINUED(estado)) return;

				//A Job TERMINOU (Programa encerrado)
				jobAux->statusExecucao = TERMINOU;
				jobAux->status = BACKGROUND;

				//Retorno
				return;
			}

			//Atualiza job
			jobAux->status = FOREGROUND;
			jobAux->statusExecucao = RODANDO;

			//Continua a execução da Job
			kill(jobAux->pid,SIGCONT);

			//Retorno
			return;
		}
		//Percorre a lista
		jobAux = jobAux->prox;
	}
	//Job não encontrado
	printf("\nJob nao encontrado.\n");
}

/* 
* Função	: Jobs_retornaJobEmForeground (JobHeader)
* Descrição	: Retorna a Job cujo estado é FOREGROUND
* Parâmetros:
* JobHeader L	: Nó-Cabeça da Lista de Jobs
* Retorno	: Job pertencente à L cujo estado é FOREGROUND
*/
Job* Jobs_retornaJobEmForeground (JobHeader L) {
	//Armazena primeiro elemento da lista
	Job *jobAux = L.primeiroJob;
	//Rotina de pesquisa da Lista
	while (jobAux != NULL) {
		//Procura Job desejado
		if(jobAux->status == FOREGROUND) return jobAux;
		//Percorre a lista
		jobAux = jobAux->prox;
	}
	//Job não encontrado
	return NULL;
}

/*
* Função	: Jobs_imprimeJobs(JobHeader)
* Descrição	: Imprime Lista de Jobs na Tela
* Parâmetros:
* JobHeader L	: Nó-Cabeça da Lista de Jobs
* Retorno	: void
*/
void Jobs_imprimeJobs(JobHeader L) {
	//Variáveis
	int iContador = 0;
	//Armazena primeiro elemento da lista
	Job *jobInicio = L.primeiroJob;
	//Lista vazia
	if(jobInicio == NULL) printf("Lista vazia!\n");
	else {
		//Rotina de pesquisa da Lista
		while (jobInicio != NULL) {
			//Imprime lista formatada
			//Título
			printf("[%d] ", iContador);
			//PID
			printf("PID: %d, ", jobInicio->pid);
			//Comando
			printf("Comando: %s, ", jobInicio->comando);
			//Status
			printf("Status: ");
			if(jobInicio->statusExecucao == RODANDO) printf("RODANDO, ");
			else if(jobInicio->statusExecucao == PAUSADO) printf("PAUSADO, ");
			else if(jobInicio->statusExecucao == TERMINOU) printf("TERMINOU, ");
			//Modo
			if(jobInicio->status==BACKGROUND) printf("BACKGROUND\n");
			else if(jobInicio->status==FOREGROUND) printf("FOREGROUND\n");
			else printf("INDEFINIDO\n");
			//Percorre a lista
			jobInicio = jobInicio->prox;
			//Incrementa o contador
			iContador++;
		}
	}
}
