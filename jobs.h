#ifndef JOBS_H_INCLUDED
#define JOBS_H_INCLUDED
#endif

//Inclusão de bibliotecas do sistema
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>

/*
* Conjunto de definições de statuses de Job
*/
#define BACKGROUND 10
#define FOREGROUND 11

/*
* Struct: Job { id, pid, status, *prox }
* Descrição: Define uma lista ligada de Jobs (elemento à elemento, ligados através de um ponteiro)
* Dados:
* 1) id: Corresponde ao número do registro da Job (ordem crescente de criação)
* 2) pid: Corresponde ao ID de sistema da Job
* 3) status: Define o estado da Job (Foreground ou Background)
* 4) *prox: Aponta para o próximo elemento da Lista
*/
typedef struct job {
    int id;
    pid_t pid;
    int status;
    //char parou; /* IMPLEMENTAR */
    char *comando;
    struct job *prox;
}Job;

/*
* Struct: JobHeader { numJobs, *primeiroJob, *ultimoJob }
* Descrição: Define um nó-cabeça à lista ligada de Jobs
* Dados:
* 1) numJobs: Armazena o número de Jobs pertecentes à Lista
* 2) *primeiroJob: Aponta para o primeiro elemento da Lista
* 3) *ultimoJob: Aponta para o último elemento da Lista
*/
typedef struct jobHeader {
	int numJobs;
	Job *primeiroJob;
	Job *ultimoJob;
}JobHeader;

//Lista GLOBAL de Jobs
JobHeader Jobs;

/*
* Função: Jobs_adicionaJob (JobHeader, pid_t, int)
* Descrição: Dado o nó-cabeça da Lista de Jobs:
* 1) Cria uma se a mesma for inexistente e insere a Job no final desta Lista
* 2) Insere a Job no final da Lista
*/
int Jobs_adicionaJob (JobHeader *L, char *comando, pid_t pid, int status);

/*
* Função: Jobs_RemoveJob (JobHeader, pid_t)
* Descrição: Dado um PID, busca a Job correspondente e remove da Lista caso encontre
*/
int Jobs_removeJob (JobHeader *L, pid_t pid);

/*
* Função: Jobs_colocaJobEmBackground (JobHeader, pid_t)
* Dado um PID, busca a Job correspondente e define seu status como BACKGROUND caso encontre
*/
int Jobs_colocaJobEmBackground (JobHeader L, pid_t pid);

/*
* Função: Jobs_colocaJobEmForeground (JobHeader, pid_t)
* Dado um PID, busca a Job correspondente e define seu status como FOREGROUND caso encontre
*/
int Jobs_colocaJobEmForeground (JobHeader L, pid_t pid);

/* 
* Função: Jobs_retornaJobEmForeground (JobHeader)
* Descrição: Retorna PID do Job em Foreground
*/
pid_t Jobs_retornaJobEmForeground (JobHeader L);

/*
* Função: Jobs_imprimeJobs(JobHeader)
* Descrição: Imprime Lista de Jobs na Tela
*/
void Jobs_imprimeJobs(JobHeader L);
