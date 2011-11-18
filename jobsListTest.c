#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Erros */
#define ERRO_SUCESSO 1
#define ERRO_NAO_ENCONTRADO -1
#define ERRO_NAO_ALOCADO -2
#define ERRO_LISTA_VAZIA -3

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

/* Coloca Job em Background */
int Jobs_colocaJobEmBackground (JobHeader L, pid_t pid) {
	//Armazena primeiro elemento da lista
	Job *jobInicio = L.primeiroJob;
	
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

/* Coloca Job em Foreground */
int Jobs_colocaJobEmForeground (JobHeader L, pid_t pid) {
	//Armazena primeiro elemento da lista
	Job *jobInicio = L.primeiroJob;
	
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
	Job *jobInicio = L.primeiroJob;
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
	int iContador = 1;
	//Armazena primeiro elemento da lista
	Job *jobInicio = L.primeiroJob;
	//Lista vazia
	if(jobInicio == NULL) printf("\nLista vazia!\n");
	else {	
		while (jobInicio != NULL) {
			//Imprime lista formatada
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
			//Percorre a lista
			jobInicio = jobInicio->prox;
			//Incrementa o contador
			iContador++;
		}
	}
}

int main(void) {
	//Variáveis
	JobHeader L;
	Job *J;
	
	//Atributos de L
	L.numJobs = 0;
	L.primeiroJob = NULL;
	L.ultimoJob = NULL;
	
	//Stress test
	J = L.primeiroJob;
	
	//Remove Job Inexistente
	Jobs_removeJob(&L,12);

	//Cria Lista/Adiciona Job
	Jobs_adicionaJob(&L,12,FOREGROUND);
	
	//Adiciona Jobs
	Jobs_adicionaJob(&L,14,BACKGROUND);
	Jobs_adicionaJob(&L,18,FOREGROUND);
	Jobs_adicionaJob(&L,11,FOREGROUND);
	Jobs_adicionaJob(&L,15,BACKGROUND);
	Jobs_adicionaJob(&L,9,BACKGROUND);
	Jobs_adicionaJob(&L,7,FOREGROUND);
	
	
	//Remove Job do início da Lista
	Jobs_removeJob(&L,12);

	
	//Remove Job do final da Lista
	Jobs_removeJob(&L,7);
	//Remove Job do meio da Lista
	Jobs_removeJob(&L,9);
	//Remove Job inexistente
	Jobs_removeJob(&L,410);
	
	//Coloca Job em Foreground (cujo status é Foreground)
	Jobs_colocaJobEmForeground(L,18);
	//Coloca Job em Foreground (cujo status é Background)
	Jobs_colocaJobEmForeground(L,14);
	//Coloca Jobs Já Removidas em Foreground
	Jobs_colocaJobEmForeground(L,7);
	Jobs_colocaJobEmForeground(L,9);
	Jobs_colocaJobEmForeground(L,12);
	

	//Coloca Job em Background (cujo status é Background)
	Jobs_colocaJobEmBackground(L,15);
	//Coloca Job em Background (cujo status é Foreground)
	Jobs_colocaJobEmBackground(L,18);
	Jobs_colocaJobEmBackground(L,14);
	//Coloca Jobs Já Removidas em Background
	Jobs_colocaJobEmBackground(L,7);
	Jobs_colocaJobEmBackground(L,9);
	Jobs_colocaJobEmBackground(L,12);
	
	//Retorna PID da Job em Foreground
	printf("\n\nJob em Foreground: %d\n\n",Jobs_retornaJobEmForeground(L)); /* 14 */


	//Imprime Jobs
	Jobs_imprimeJobs(	L);
	//Retorno
	return 1;
}
	
