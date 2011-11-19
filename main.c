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
#include "colors.h"
#include "erros.h"
#include "alocacao.h"
#include "path.h"
#include "jobs.h"
#include "signal_capture.h"
#include "canonical.h"
#include "teclado.h"

/*
* Conjunto de definições de Terminal
*/
#define TERMINAL_NUMLINHAS 128
#define TERMINAL_TAMANHOLINHA 1024
#define TERMINAL_TAMANHOPALAVRA 32

/*
* Função: Terminal_rodaLinhaComando (char*, char**, int, int)
* Descrição: * Roda os comandos não built-in *
*/
int Terminal_rodaLinhaComando (char **caminhos, char **Parametro, int numParametros, int qtdCaminhos, int runForeground) {
	//Variáveis
	pid_t pidNovoProcesso;
	Job* jobAux;
	int i;
	int status;

	i=0;

	//Entrada e Saída
	//FILE *ori_stdin = stdin;
	//FILE *ori_stdout = stdout;
	//FILE *ori_stderr = stderr;
		

		//Cria processo-filho

		pidNovoProcesso = fork();

		//Falha na criação
		if(pidNovoProcesso == -1) {
			//ERRO_NAO_FOI_POSSIVEL_CRIAR

			perror("Nao foi possivel criar novo processo\n");
			exit(0);
		}
		else
		if(pidNovoProcesso > 0){
		//	printf("processo pai %d\n", pidNovoProcesso);

			wait(&status);

			//Processo-pai
			
			//Adiciona Job à Lista
			//Jobs_adicionaJob(Jobs,IMPLEMENTAR,pidNovoProcesso,FOREGROUND,RODANDO);
			
			//Se estiver em FOREGROUND
			//jobAux = Jobs_retornaJobEmForeground(Jobs);
			//if(pidNovoProcesso == jobAux->pid) {
				//Define ID do Grupo de Processos
				//setpgid(pidNovoProcesso, 0);
				//Aguarda o término do Processo
				//waitpid(pidNovoProcesso, NULL, 0);
			//}
		}
		else
		if(pidNovoProcesso == 0){
			//if(pidNovoProcesso == 0) {
			//Define ID do Grupo de Processos
			setpgid(pidNovoProcesso, 0);
			
			//IMPLEMENTAR
			//sigaction(SIGTSTP, &IMPLEMENTAR, NULL);
    			//sigaction(SIGCHLD, &IMPLEMENTAR, NULL);
			

			//IMPLEMENTAR
			for (i=0 ; i < qtdCaminhos ; i++)
			{
				char* fullPath;
				fullPath = Alocacao_alocaVetor(101);

				sprintf(fullPath,"%s/%s", caminhos[i],Parametro[0]);
				execv(fullPath, Parametro);
				printf("\nNUH %s\n", fullPath);
				free(fullPath);
			}		
			//execv(IMPLEMENTAR,IMPLEMENTAR);
			
			//ERRO_COMANDO_NAO_RECONHECIDO
			//fprintf(stderr, "\nComando invalido!\n");

		}	

	
	//}

	//Retorno
	return 1;
}


int isBuiltIn(char **Parametro){
	if(strcmp(Parametro[0], "cd") == 0){
		return 1;
	}

	if(strcmp(Parametro[0], "exit") == 0){
		return 1;
	}
	
	if(strcmp(Parametro[0], "bg") == 0){
		return 1;
	}

	if(strcmp(Parametro[0], "fg") == 0){
		return 1;
	}
	
	if(strcmp(Parametro[0], "jobs") == 0){

		return 1;
	}

	if(strcmp(Parametro[0], "quit") == 0){
		return 1;
	}

	return 0;
}

int Terminal_rodaBuiltIn(char **Parametro){

	//exit
	if(strcmp(Parametro[0], "exit") == 0 || strcmp(Parametro[0], "quit") == 0) {
		//Sai do terminal				
		exit(0);
	}
	//cd
	if(strcmp(Parametro[0], "cd") == 0) {
		if (chdir(Parametro[1]) == -1) perror("ERRO");
		//printf("\n");
	}
	//jobs
	if(strcmp(Parametro[0], "jobs") == 0) {
		Jobs_imprimeJobs(Jobs);
	}

	//bg
	if (strcmp(Parametro[0], "bg") == 0) {
		Jobs_colocaJobEmBackground(Jobs, (pid_t) Parametro[1]);
	}
	
	//fg
	if (strcmp(Parametro[0], "fg") == 0) {
		Jobs_colocaJobEmBackground(Jobs, (pid_t) Parametro[1]);
	}

	return 0;
}

/* 
* Função: Terminal_InterpretaLinhaComando (char*, char**, char*)
* Descrição: Interpreta a Linha de Comando digitada
*/
int Terminal_InterpretaLinhaComando (char *LinhaComando, char **LinhasComando, char **caminhos, int qtdCaminhos) {
	//Variáveis	
	int numParametros, runForeground, idPalavra, contadorParametros;
	char **Parametro, *Comando, *tokenPalavra;
	
	//Aloca a matriz de parâmetros
	Parametro = Alocacao_alocaMatriz((TERMINAL_TAMANHOLINHA/TERMINAL_TAMANHOPALAVRA),TERMINAL_TAMANHOPALAVRA);

	//Aloca o vetor Comando
	Comando = Alocacao_alocaVetor(TERMINAL_TAMANHOPALAVRA);
		
	//Condições iniciais
	idPalavra = 0;
	contadorParametros = 0;
	
	//Quebra Linha de Comando em Palavras
	tokenPalavra = (char*) strtok(LinhaComando, " ");
	while(tokenPalavra != NULL) {
		//Salva palavra
		strcpy(Parametro[idPalavra], tokenPalavra);

		//Percorre o token
		tokenPalavra = (char*) strtok(NULL, " ");

		printf("param.%s\n", Parametro[idPalavra]);
		//Incrementa o número de palavras
		idPalavra++;
	}

	//Salva número de parâmetro
	numParametros = idPalavra;
	//Começa o contador na última posição
	contadorParametros = numParametros-1;
	
	/*
	//Rotina para cada palavra
	while(contadorParametros >= 0) {

		//Armazena palavra
		strcpy(Comando, Parametro[contadorParametros]);
		//REVISAR
		runForeground = 1;

		//Decrementa contador
		contadorParametros--;
	}*/

	if(numParametros >=0 )
		strcpy(Comando, Parametro[0]);

	//printf("\nNUH! %s\n", Comando);

	if(!isBuiltIn(Parametro)){
		//Roda comando
		Terminal_rodaLinhaComando(caminhos, Parametro, numParametros, qtdCaminhos, runForeground);
		//printf("Command not found: \n");
		//return EXIT_FAILURE;
			
	}
	else {
		Terminal_rodaBuiltIn(Parametro);
	}
	//Libera memória alocada
	free(tokenPalavra);

	//Retorno
	return 0;
}

int main(void) {
	//Variáveis
	int loopProgram, idLinhaComando, qtdCaminhos;
	char *LinhaComando, **LinhasComando;
	char *Diretorio, *DiretorioAtual;
	char **caminhos;
	Job *Job;

	//IMPLEMENTAR
	//signal_setup(IMPLEMENTAR)
	
	//Propriedades da Lista
	Jobs.primeiroJob = NULL;
	Jobs.ultimoJob = NULL;
	Jobs.numJobs = 0;

	//Propriedades do Path
	ListaPath.FullPath = Alocacao_alocaMatriz(PATH_NUMDIR, PATH_TAMANHO);
	ListaPath.numPaths = 0;

	//Aloca Linhas de Comando
	LinhasComando = Alocacao_alocaMatriz(TERMINAL_NUMLINHAS, TERMINAL_TAMANHOLINHA);

	//Aloca Cada Linha de Comando
	LinhaComando = Alocacao_alocaVetor(TERMINAL_TAMANHOLINHA);

	//Condições iniciais
	loopProgram = 1;
	idLinhaComando = 0;

	//Aloca vetor 'Diretorio'
	Diretorio = Alocacao_alocaVetor(TERMINAL_TAMANHOLINHA);

	//Aloca Diretório atual
	DiretorioAtual = Alocacao_alocaVetor(PATH_TAMANHO*PATH_NUMDIR);
	
	caminhos = Alocacao_alocaMatriz(TERMINAL_NUMLINHAS, TERMINAL_TAMANHOLINHA);

	char* token;
	int c = 0;
	char* caminhoInteiro;

	//Limpa a tela
	system("clear");
	
		caminhoInteiro = strdup(getenv("PATH"));
		token = strtok(caminhoInteiro,":");
		while(token != NULL)
		{
			caminhos[c]=strdup(token);
			printf("%s\n",caminhos[c]);
			c++;
			token = strtok(NULL,":");
		}
		qtdCaminhos = c;

	//Execução da rotina principal
	while(loopProgram) {
		//Retorna o diretório atual
		
		Diretorio = strdup(getenv("PWD"));

		//Path_recuperaCaminho(&ListaPath);
		//DiretorioAtual = Path_imprimeCaminho(ListaPath);
	
		char* shellLine = (char*) malloc ((strlen(Diretorio)+2) * sizeof(char));
		sprintf(shellLine,"%s", Diretorio);
				

		//Imprime diretório atual em vermelho		
		Color_red(shellLine);	

		//Ativa o modo não-canônico
		Canonical_setNonCanonicalMode();

		//Lê a Linha de Comando
		LinhaComando = Terminal_processaLinha(LinhasComando, idLinhaComando);

		//Retorna ao modo canônico
		Canonical_setCanonicalMode();

		//Insere Linha de Comando no Histórico
		Terminal_insereLinhaNoHistorico(LinhaComando, LinhasComando, idLinhaComando);

		//Interpreta Linha de Comando
		Terminal_InterpretaLinhaComando(LinhaComando, LinhasComando, caminhos, qtdCaminhos);
		
		//Incrementa Linha de Comando
		idLinhaComando++;		
	}
	//Libera memória alocada
	free(LinhaComando);

	//Retorno
	return 1;
}
