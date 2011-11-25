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



/**
* Estrutura Job
* Jobs
* Dados:
* id	 Corresponde ao número do registro da Job (ordem crescente de criação)
* pid	 Corresponde ao ID do processo da Job
* status Define o Modo de Execução da Job (FOREGROUND, BACKGROUND)
* statusExecucao: Define o Status da Execução da Job (RODANDO, PAUSADO, TERMINOU)
* *ultimoJob Aponta para o último elemento da Lista
* *prox	 Aponta para o próximo elemento da Lista
*/
typedef struct job {
	int id;
	pid_t pid;
	int status;
	int statusExecucao;
	char *comando;
	struct job *prox;
} Job;



/**
* Estrutura JobHeader
* Nó-cabeça da Lista de Jobs
* Dados:
* numJobs Armazena o número de Jobs pertecentes à Lista
* *primeiroJob Aponta para o primeiro elemento da Lista
* *ultimoJob Aponta para o último elemento da Lista
*/
typedef struct jobHeader {
	int numJobs;
	Job *primeiroJob;
	Job *ultimoJob;
	Job *currentForegroundJob;
} JobHeader;



//Lista GLOBAL de Jobs
JobHeader Jobs;



/**
* Adiciona a Job na Lista de Jobs
* 
@param *L Nó-Cabeça da Lista de Jobs (modificado em caso de remoção bem-sucedida)
*
@param *comando Comando referente à linha de comando
*
@param pid ID da Job a ser adicionada
*
@param status Modo de Execução da Job
*
@param statusExecucao Status de Execucao da Job
*
@return void
*/
void Jobs_adicionaJob (JobHeader *L, char *comando, pid_t pid, int status, int statusExecucao);



/**
* Remove a Job buscada da Lista de Jobs
* 
@param *L Nó-Cabeça da Lista de Jobs (modificado em caso de remoção bem-sucedida)
*
@param pid ID da Job a ser buscada
*
@return void
*/
void Jobs_removeJob (JobHeader *L, pid_t pid);



/**
* Retorna a Job com o PID buscado
* 
@param *L Nó-Cabeça da Lista de Jobs
*
@param pid ID da Job a ser buscada
*
@return Job Buscada
*/
Job* Jobs_retornaJobComPID (JobHeader *L, pid_t pid);

	

/**
* Procura pela Job de ID pid e coloca em BACKGROUND com as devidas alterações
* 
@param L Nó-Cabeça da Lista de Jobs
*
@param pid ID da Job a ser colocada em BACKGROUND
*
@return void
*/
void Jobs_colocaJobEmBackground (JobHeader *L, pid_t pid);



/**
* Procura pela Job de ID pid e coloca em FOREGROUND com as devidas alterações
* 
@param L Nó-Cabeça da Lista de Jobs
*
@param pid ID da Job a ser colocada em FOREGROUND
*
@return void
*/
void Jobs_colocaJobEmForeground (JobHeader *L, pid_t pid);



/** 
* Retorna a Job cujo estado é FOREGROUND
* 
@param L Nó-Cabeça da Lista de Jobs
*
@return Job pertencente à L cujo estado é FOREGROUND
*/
Job* Jobs_retornaJobEmForeground (JobHeader L);



/**
* Imprime Lista de Jobs na Tela
* 
@param L Nó-Cabeça da Lista de Jobs
*
@return void
*/
void Jobs_imprimeJobs(JobHeader L);
