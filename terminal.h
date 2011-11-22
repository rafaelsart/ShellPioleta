#ifndef TERMINAL_H_INCLUDED
#define TERMINAL_H_INCLUDED
#endif

/*
* Conjunto de definições de Terminal
*/
#define TERMINAL_TAMANHODIRETORIO 128
#define TERMINAL_TAMANHOPATH 512
#define TERMINAL_TAMANHOUSUARIO 32
#define TERMINAL_NUMLINHAS 128
#define TERMINAL_TAMANHOLINHA 512
#define TERMINAL_TAMANHOPALAVRA 32

/* Path */
char **Path;

/* 
* Função: Terminal_insereLinhaNoHistorico (char*, char**, int)
* Descrição: Insere uma Linha de Comando no Histórico de Linhas
*/
int Terminal_insereLinhaNoHistorico (char *LinhaComando, char **LinhasComando, int numLinhasComando);

/*
* Função: Terminal_InterpretaLinhaComando (char*, char**)
* Descrição: Interpreta a Linha de Comando digitada
*/
void Terminal_InterpretaLinhaComando (char *LinhaComando, char **LinhasComando);

/*
* Função: Terminal_processaLinha (char*, char**, int)
* Descrição: Lê e controla a Linha de Comando, de modo não-canônico
*/
char* Terminal_processaLinha (char **LinhasComando, int numLinhasComando);
