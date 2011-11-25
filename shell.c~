//Inclusão de bibliotecas do sistema
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#include <termios.h>
#include <errno.h>
#include <sys/wait.h>

//Inclusão de bibliotecas próprias
#include "colors.h"
#include "tela.h"
#include "erros.h"
#include "alocacao.h"
#include "jobs.h"
#include "signal_capture.h"
#include "canonical.h"
#include "terminal.h"
#include "comando.h"

int main(void) {
	//Variáveis
	int loopProgram, numLinhasComando;
	char *LinhaComando, **LinhasComando;
	//char *Diretorio, *Usuario;
	
	//Instala sinais
	Signal_Instalacao();
	
	//Propriedades da Lista
	Jobs.primeiroJob = NULL;
	Jobs.ultimoJob = NULL;
	Jobs.numJobs = 0;

	//Aloca Linhas de Comando
	LinhasComando = Alocacao_alocaMatriz(TERMINAL_NUMLINHAS, TERMINAL_TAMANHOLINHA);
	
	//Condições iniciais
	loopProgram = 1;
	numLinhasComando = 0;

	//Limpa a tela
	Tela_limpaTela();

	//Execução da rotina principal
	while(loopProgram) {
		//Instala sinais
		//Signal_Instalacao();

		//Aloca Linha de Comando
		LinhaComando = Alocacao_alocaVetor(TERMINAL_TAMANHOLINHA);
		
		//Imprime a Shell
		//Tela_apagaCaracteres(TERMINAL_TAMANHOLINHA);
                Tela_imprimeShell();
		
		//Ativa o modo não-canônico
		Canonical_setNonCanonicalMode();
		
		//Lê a Linha de Comando
		LinhaComando = Terminal_processaLinha(LinhasComando, numLinhasComando);

		//Retorna ao modo canônico
		Canonical_setCanonicalMode();

		//Processa Linha de Comando
		if(LinhaComando != NULL){
			//Insere Linha de Comando no Histórico
			Terminal_insereLinhaNoHistorico(LinhaComando, LinhasComando, numLinhasComando);

			//Interpreta Linha de Comando
			Terminal_InterpretaLinhaComando(LinhaComando, LinhasComando);
			
			Tela_apagaCaracteres(TERMINAL_TAMANHOLINHA);

			//Incrementa Número de Linhas de Comando
			numLinhasComando++;

			//Libera memória alocada
			free(LinhaComando);		
		}
	}
	//Retorno
	return 1;
}
