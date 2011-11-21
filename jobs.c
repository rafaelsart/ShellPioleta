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
#include "erros.h"

/*
* Função: Jobs_adicionaJob (JobHeader, pid_t, int)
* Descrição: Dado o nó-cabeça da Lista de Jobs:
* 1) Cria uma se a mesma for inexistente e insere a Job no final desta Lista
* 2) Insere a Job no final da Lista
*/
int Jobs_adicionaJob (JobHeader *L, char *comando, pid_t pid, int status, int statusExecucao) {
	//Variáveis
	Job *jobAux;
	Job *jobNovo;

	//Aloca um elemento struct job
	jobAux = (Job*) malloc(sizeof(struct job));

	//Falha na alocação	
	if(jobAux == NULL) return ERRO_NAO_ALOCADO;
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
		//Retorna SUCESSO
		return ERRO_SUCESSO;
	}
}

/*
* Função: Jobs_RemoveJob (JobHeader, pid_t)
* Descrição: Dado um PID, busca a Job correspondente e remove da Lista caso encontre
*/
int Jobs_removeJob (JobHeader *L, pid_t pid) {
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
			//Job não encontrado
			return ERRO_NAO_ENCONTRADO;
		}
			
	}
	//Lista vazia
	return ERRO_LISTA_VAZIA;
}

/*
* Função: Jobs_retornaJobComPID (JobHeader, pid_t)
* Descrição: Retorna a Job com o PID buscado
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
* Função: Jobs_colocaJobEmBackground (JobHeader, pid_t)
* Dado um PID, busca a Job correspondente e define seu status como BACKGROUND caso encontre
*/
int Jobs_colocaJobEmBackground (JobHeader L, pid_t pid) {
	//Armazena primeiro elemento da lista
	Job *jobInicio = L.primeiroJob;
	//Rotina de pesquisa da Lista
	while (jobInicio != NULL) {
		//Procura Job desejado	       
		if (jobInicio->pid == pid) {
			//O Job já terminou			
			if(jobInicio->statusExecucao == TERMINOU) {
				//ERRO_JOB_JA_TERMINOU
			}

			//O Job ainda existe
			else {
				//Altera status
				jobInicio->status = BACKGROUND;
				jobInicio->statusExecucao = RODANDO;

				//Mata e envia SIGCONT
				kill(jobInicio->pid, SIGCONT);
			
				//Retorna SUCESSO			
				return ERRO_SUCESSO;
			}
		}
		//Percorre a lista
		jobInicio = jobInicio->prox;
	}
	//ERRO_NAO_ENCONTRADO

	//retorno
	return ERRO_NAO_ENCONTRADO;
}

/*
* Função: Jobs_colocaJobEmForeground (JobHeader, pid_t)
* Dado um PID, busca a Job correspondente e define seu status como FOREGROUND caso encontre
*/
int Jobs_colocaJobEmForeground (JobHeader L, pid_t pid) {
	//Armazena primeiro elemento da lista
	Job *jobInicio = L.primeiroJob;
	//Rotina de pesquisa da Lista
	while (jobInicio != NULL) {
		//Procura Job desejado	       
		if (jobInicio->pid == pid) {
			//O Job já terminou			
			if(jobInicio->statusExecucao == TERMINOU) {
				//ERRO_JOB_JA_TERMINOU
			}

			//O Job ainda existe
			else {
				//Altera status
				jobInicio->status = FOREGROUND;
				jobInicio->statusExecucao = RODANDO;

				//Retorna SUCESSO			
				return ERRO_SUCESSO;
			}
		}
		//Percorre a lista
		jobInicio = jobInicio->prox;
	}
	//Job não encontrado
	return ERRO_NAO_ENCONTRADO;
}

/* 
* Função: Jobs_retornaJobEmForeground (JobHeader)
* Descrição: Retorna Job em Foreground
*/
Job* Jobs_retornaJobEmForeground (JobHeader L) {
	//Armazena primeiro elemento da lista
	Job *jobInicio = L.primeiroJob;
	//Rotina de pesquisa da Lista
	while (jobInicio != NULL) {
		//Procura Job desejado
		if(jobInicio->status == FOREGROUND) return jobInicio;
		//Percorre a lista
		jobInicio = jobInicio->prox;
	}
	//Job não encontrado
	return NULL;
}

/*
* Função: Jobs_imprimeJobs(JobHeader)
* Descrição: Imprime Lista de Jobs na Tela
*/
void Jobs_imprimeJobs(JobHeader L) {
	//Variáveis
	int iContador = 1;
	//Armazena primeiro elemento da lista
	Job *jobInicio = L.primeiroJob;
	//Lista vazia
	if(jobInicio == NULL) printf("\nLista vazia!\n\n");
	else {
		//Rotina de pesquisa da Lista
		while (jobInicio != NULL) {
			//Imprime lista formatada
			printf("\n");
			//Título
			printf("Job #%d\n", iContador);
			//PID
			printf("PID: %d\n", jobInicio->pid);
			//Comando
			printf("Comando: %s\n", jobInicio->comando);
			//Status
			printf("Status: ");
			if(jobInicio->status==BACKGROUND) printf("Background\n");
			else if(jobInicio->status==FOREGROUND) printf("Foreground\n");
			else printf("Desconhecido\n");
			//Percorre a lista
			jobInicio = jobInicio->prox;
			//Incrementa o contador
			iContador++;
		}
	}
}
