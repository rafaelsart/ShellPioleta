#ifndef JOBS_H_INCLUDED
#define JOBS_H_INCLUDED
#endif

//Inclusão de bibliotecas do sistema
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>

//Modos de Execução da Job
#define BACKGROUND 0
#define FOREGROUND 1

//Status de Execução da Job
#define RODANDO 1
#define PAUSADO 0
#define TERMINOU -1



/*
* Estrutura	: Job
* Descrição	: Jobs
* Dados:
* id		: Corresponde ao número do registro da Job (ordem crescente de criação)
* pid		: Corresponde ao ID do processo da Job
* status	: Define o Modo de Execução da Job (FOREGROUND, BACKGROUND)
* statusExecucao: Define o Status da Execução da Job (RODANDO, PAUSADO, TERMINOU)
* *ultimoJob	: Aponta para o último elemento da Lista
* *prox: Aponta para o próximo elemento da Lista
*/
typedef struct job {
	int id;
	pid_t pid;
	int status;
	int statusExecucao;
	char *comando;
	struct job *prox;
} Job;



/*
* Estrutura	: JobHeader
* Descrição	: Nó-cabeça da Lista de Jobs
* Dados:
* numJobs	: Armazena o número de Jobs pertecentes à Lista
* *primeiroJob	: Aponta para o primeiro elemento da Lista
* *ultimoJob	: Aponta para o último elemento da Lista
*/
typedef struct jobHeader {
	int numJobs;
	Job *primeiroJob;
	Job *ultimoJob;
	Job *currentForegroundJob;
} JobHeader;



//Lista GLOBAL de Jobs
JobHeader Jobs;



/*
* Função	: Jobs_adicionaJob (JobHeader, pid_t)
* Descrição	: Remove a Job buscada da Lista de Jobs
* Parâmetros:
* JobHeader *L	: Nó-Cabeça da Lista de Jobs (modificado em caso de remoção bem-sucedida)
* pid_t pid	: ID da Job a ser buscada
* Retorno	: void
*/
void Jobs_adicionaJob (JobHeader *L, char *comando, pid_t pid, int status, int statusExecucao);



/*
* Função	: Jobs_removeJob (JobHeader, pid_t)
* Descrição	: Remove a Job buscada da Lista de Jobs
* Parâmetros:
* JobHeader *L	: Nó-Cabeça da Lista de Jobs (modificado em caso de remoção bem-sucedida)
* pid_t pid	: ID da Job a ser buscada
* Retorno	: void
*/
void Jobs_removeJob (JobHeader *L, pid_t pid);



/*
* Função	: Jobs_retornaJobComPID (JobHeader, pid_t)
* Descrição	: Retorna a Job com o PID buscado
* Parâmetros:
* JobHeader *L	: Nó-Cabeça da Lista de Jobs
* pid_t pid	: ID da Job a ser buscada
* Retorno	: Job Buscada
*/
Job* Jobs_retornaJobComPID (JobHeader *L, pid_t pid);

	

/*
* Função	: Jobs_colocaJobEmBackground (JobHeader*, pid_t)
* Procura pela Job de ID pid e coloca em BACKGROUND com as devidas alterações
* Parâmetros:
* JobHeader L	: Nó-Cabeça da Lista de Jobs
* pid_t pid	: ID da Job a ser colocada em BACKGROUND
* Retorno	: void
*/
void Jobs_colocaJobEmBackground (JobHeader *L, pid_t pid);



/*
* Função	: Jobs_colocaJobEmForeground (JobHeader*, pid_t)
* Procura pela Job de ID pid e coloca em FOREGROUND com as devidas alterações
* Parâmetros:
* JobHeader L	: Nó-Cabeça da Lista de Jobs
* pid_t pid	: ID da Job a ser colocada em FOREGROUND
* Retorno	: void
*/
void Jobs_colocaJobEmForeground (JobHeader *L, pid_t pid);



/* 
* Função	: Jobs_retornaJobEmForeground (JobHeader)
* Descrição	: Retorna a Job cujo estado é FOREGROUND
* Parâmetros:
* JobHeader L	: Nó-Cabeça da Lista de Jobs
* Retorno	: Job pertencente à L cujo estado é FOREGROUND
*/
Job* Jobs_retornaJobEmForeground (JobHeader L);



/*
* Função	: Jobs_imprimeJobs(JobHeader)
* Descrição	: Imprime Lista de Jobs na Tela
* Parâmetros:
* JobHeader L	: Nó-Cabeça da Lista de Jobs
* Retorno	: void
*/
void Jobs_imprimeJobs(JobHeader L);
