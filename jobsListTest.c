#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Erros */
#define ERRO_SUCESSO 1
#define ERRO_NAO_ENCONTRADO -1
#define ERRO_NAO_ALOCADO -2

/* Status personalizados */
#define BACKGROUND 10
#define FOREGROUND 11

/* Estrutura de job */
typedef struct job {
    int id;
    pid_t pid;
    int status; /* 0 = background; 1 = foreground */
    //char parou; /* IMPLEMENTAR */
    //char *comando; /* IMPLEMENTAR */
    struct job *prox;
}Job;

/* Estrutura do nó-cabeça */
typedef struct jobHeader {
	int numJobs;
	Job *primeiroJob;
	Job *ultimoJob;
}JobHeader;



/* Cria ou adiciona Job à lista*/
int Jobs_adicionaJob(JobHeader *L, pid_t pid, int status) {
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
		jobAux->status = status;
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
		L->numJobs++;
		//Retorna SUCESSO
		return ERRO_SUCESSO;
	}
}

/* Remove Job da lista */
int Jobs_removeJob(JobHeader *L, pid_t pid) {
	//Variáveis
	Job *jobAux;
	Job *jobInicio;
	//Armazena o primeiro elemento da lista 
	jobInicio = L->primeiroJob;
	//Lista não-vazia
	if(jobInicio != NULL) {
		//Remoção no início		
		if(jobInicio->pid == pid) {
			//Refaz a ligação do primeiro Job
			L->primeiroJob = jobInicio->prox;
			//Lista de tamanho 1
			if(L->numJobs == 1) L->ultimoJob = L->primeiroJob;
			//Job não encontrado
			return ERRO_NAO_ENCONTRADO;
		}
		//Procura o ponto de remoção
		else {
			while(jobInicio != NULL) {
				if(jobInicio->prox->pid == pid) {
					//Salva o elemento a ser removido
					jobAux = jobInicio->prox;
					//Atualiza a lista
					jobInicio->prox = jobAux->prox;
					//Libera a memória alocada
					free(jobAux);
				}
				//Percorre a lista
				jobInicio = jobInicio->prox;
			}
			//Job não encontrado
			return ERRO_NAO_ENCONTRADO;
		}
			
	}
}

/* Coloca Job em Background */
int Jobs_colocaJobEmBackground (JobHeader L, pid_t pid) {
	//Armazena primeiro elemento da lista
	Job *jobInicio = L.primeiroElemento;
	
	while (jobInicio != NULL) {
		//Procura Job desejado	       
		if (jobInicio->pid == pid) {
			//Altera status
			jobInicio->status = BACKGROUND;
			//Retorna SUCESSO			
			return ERRO_SUCESSO;
		}
		//Percorre a lista
		jobInicio = jobInicio->prox;
	}
	//Job não encontrado
	return ERRO_NAO_ENCONTRADO;
}

/* Coloca Job em Background */
int Jobs_colocaJobEmBackground (JobHeader L, pid_t pid) {
	//Armazena primeiro elemento da lista
	Job *jobInicio = L.primeiroElemento;
	
	while (jobInicio != NULL) {
		//Procura Job desejado	       
		if (jobInicio->pid == pid) {
			//Altera status
			jobInicio->status = FOREGROUND;
			//Retorna SUCESSO			
			return ERRO_SUCESSO;
		}
		//Percorre a lista
		jobInicio = jobInicio->prox;
	}
	//Job não encontrado
	return ERRO_NAO_ENCONTRADO;
}

/* Retorna PID do Job em Foreground */
pid_t Jobs_retornaJobEmForeground(JobHeader L) {
	//Armazena primeiro elemento da lista
	Job *jobInicio = L.primeiroElemento;
	while (jobInicio != NULL) {
		//Procura Job desejado
		if(jobInicio->status == FOREGROUND) return jobInicio->pid;
		//Percorre a lista
		jobInicio = jobInicio->prox;
	}
	//Job não encontrado
	return ERRO_NAO_ENCONTRADO;
}

/* Imprime Lista de Jobs na Tela */
void Jobs_imprimeJobs(JobHeader L) {
	//Variáveis
	int iContador;
	//Armazena primeiro elemento da lista
	Job *jobInicio = L.primeiroElemento;
	//Lista vazia
	if(jobInicio == NULL) printf("\nLista vazia!\n");
	else {	
		while (jobInicio != NULL) {
			printf("\n");
			//Título
			printf("Job #%d\n", iContador);
			//PID
			printf("PID: %d\n", jobInicio->pid);
			//Status
			printf("Status: ");
			if(jobInicio->status==BACKGROUND) printf("Background\n");
			else if(jobInicio->status==FOREGROUND) printf("Foreground\n");
			else printf("Desconhecido\n");
			jobInicio = jobInicio->prox;
		}
	}
}

int main(void) {
	//Variáveis
	JobHeader L;
	Job *J;
	//Atributos de L
	L->numJobs = 0;
	L->primeiroJob = NULL;
	L->ultimoJob = NULL;
	//Comandos
	J = L.primeiroElemento;
	Jobs_adicionaJob(&L,12,FOREGROUND);
	Jobs_adicionaJob(&L,14,BACKGROUND);
	Jobs_adicionaJob(&L,18,BACKGROUND);
	Jobs_adicionaJob(&L,11,FOREGROUND);
	Jobs_adicionaJob(&L,9,BACKGROUND);
	Jobs_adicionaJob(&L,7,FOREGROUND);
	Jobs_imprimeJobs(L);
	return 1;
}
	
