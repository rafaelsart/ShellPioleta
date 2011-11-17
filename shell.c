#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#include <termios.h>
#include <errno.h>
#include <sys/wait.h>

/* ANSI-Cores */
#define C_RED		"\033[91m"
#define C_GREEN        	"\033[92m"
#define C_ORANGE     	"\033[93m"
#define C_BLUE         	"\033[94m"
#define C_PINK         	"\033[95m"
#define C_CYAN        	"\033[96m"
#define C_WHITE       	"\033[97m"
#define C_BLACK        	"\033[90m"
#define RESTORE       	"\033[00m"
 
/* Funcoes de cores */
void red (char string[]) {
	printf("%s%s $%s ", C_RED, string, RESTORE);
}
 
void green (char string[]) {
	printf("%s%s $%s ", C_GREEN, string, RESTORE);
}
 
void orange (char string[]) {
	printf("%s%s $%s ", C_ORANGE , string, RESTORE);
}
 
void blue(char string[]) {
	printf("%s%s $%s ", C_BLUE, string, RESTORE);
}
 
void pink(char string[]) { 
	printf("%s%s $%s ", C_PINK, string, RESTORE);
}
 
void cyan(char string[]) {
	printf("%s%s $%s ", C_CYAN, string, RESTORE);
}
 
void white (char string[]) { 
	printf("%s%s $%s ", C_WHITE, string, RESTORE);
}
 
void black (char string[]) {
	printf("%s%s $%s  ", C_BLACK, string, RESTORE);
}

/* Inicializa Vetor */
char *initializeVector() {
	char *v;

	v = (char *) malloc(sizeof(char)*1024);
	if(v == NULL){
		printf("memory");
	}

	return v;
}

/* Inicializa Matriz */
char **initializeMatrix(){
	char **trix;
	int i;
	
	trix = (char **) malloc (sizeof(char) * 101);
	for(i=0; i < 101; i++){
		trix[i] = (char *) malloc(sizeof(char) * 101);
	}
	return trix;
}


/*Flush the keys buffer*/
void flushKeys(char *key)
{
	key[0] = key[1] = key[2] = 0;
}

void eraseWord(char *bufferAux)
{
	int i;	
	for(i = 0; i < strlen(bufferAux); i++)
	{
		printf("\b \b");
	}
}

/* Le e controla a linha de comando - modo nao canonico  */
char* readLine(char *buffer, char **trix, int commandLine)
{
	char c;
	int i, j, k;
	int keyIndex = 0;
	char key[3];
	char bufferAux[100];
	int linesOver;

	linesOver = 0;
	
	for(i=0; i < 100; i++){
		buffer[i] = '\0';
		bufferAux[i] = '\0';
	}

	i = j = k = 0;
	flushKeys(key);
	 
	while((c = getchar()))
	{	
		key[keyIndex] = c;
		keyIndex++;
		
		if(keyIndex > 2)
		{
			keyIndex = 0;
		}
			
		//Seta para cima	
		if(key[0] == 27 && key[1] == 91 && key[2] == 65 && linesOver == 0)
		{
			//printf("CIMA");
			flushKeys(key);
			for(j=0; j < strlen(buffer); j++){
				bufferAux[j] = buffer[j];
			}
			bufferAux[j] = '\0';
			eraseWord(bufferAux);

			linesOver++;
			if(commandLine - linesOver > 0) {
				for(j=0; trix[commandLine-linesOver][j] != '\0'; j++){
					buffer[j] = trix[commandLine-linesOver][j];
				}
				buffer[j] = '\0';			
			}
			i = strlen(buffer);

			printf("%s", buffer);
		}
		else if(key[0] == 27 && key[1] == 91 && key[2] == 65 && linesOver > 0 && commandLine-linesOver > 1) {
			//CIMA
			flushKeys(key);
			
			eraseWord(buffer);
	
			linesOver++;
			for(j=0; trix[commandLine-linesOver][j] != '\0'; j++){
				buffer[j] = trix[commandLine-linesOver][j];
			}
			buffer[j] = '\0';
			i = strlen(buffer);

			printf("%s", buffer);
		}
		else if(key[0] == 27 && key[1] == 91 && key[2] == 66 && linesOver == 1)
		{
			//Seta para baixo
			flushKeys(key);

			eraseWord(buffer);

			linesOver--;
			for(j=0; bufferAux[j] != '\0'; j++){
				buffer[j] = bufferAux[j];
			}
			buffer[j] = '\0';

			i = strlen(buffer);

			printf("%s", buffer);
		}
		else if(key[0] == 27 && key[1] == 91 && key[2] == 66 && linesOver > 1){
			//Seta para baixo
			flushKeys(key);

			eraseWord(buffer);

			linesOver--;
			for(j = 0; trix[commandLine - linesOver][j] != '\0'; j++){
				buffer[j] = trix[commandLine - linesOver][j];
			}
			buffer[j] = '\0';
			
			i = strlen(buffer);

			printf("%s", buffer);
				
		}
		else if(key[0] == 12 || key[1] == 12 || key[2] == 12)
		{		
			//CTRL+L
			flushKeys(key);
			system("clear");
			//printf("%s", fullPrompt());
		}
		else if(key[0] == 3 || key[1] == 3 || key[2] == 3)
		{
			//CTRL+C
			flushKeys(key);
			strcpy(buffer,"CTRLC");
			break;
		}
		else if(key[0] == 4 || key[1] == 4 || key[2] == 4)
		{	
			//CTRL+D
			flushKeys(key);
			strcpy(buffer,"CTRLD");
			break;
		}		
		else if(key[0] == 26 || key[1] == 26 || key[2] == 26)
		{	
			//CTRL+Z
			flushKeys(key);
			strcpy(buffer,"CTRLZ");
			break;
		}
		else if(key[0] != 27 && key[0] != 12 && key[0] != 4 && key[0] != 26 && key[0] != 3) 
		{
			flushKeys(key);
			//Print keyboard keys on the screen
			if(c >= 32 && c <= 126) 
			{
				printf("%c", c);
				buffer[i++] = c;
				buffer[i] = '\0';
			}
			
			//Enter 
			else if(c == 13)
			{
				//Enter sem digitar nada	
				if(buffer[0] == '\0')
				{
					break;
				}
				//Enter depois de digitar algo
				else 
				{
					printf("%c\n", c);
					break;
				}

				
			}
			//'Print' the backspace key
			else if(c == 127 && i > 0)
			{
				printf("\b \b");	
				i--;
				buffer[i]='\0';
			}
		}	
	
	}
	return buffer;
}

struct termios oldtio;

void setNonCanonicalMode(void) 
{
	struct termios newtio;

	tcgetattr(0,&oldtio);
	bzero(&newtio,sizeof(newtio));
	
	newtio.c_cflag = CRTSCTS | CS8 | CLOCAL | CREAD | ICANON;
	newtio.c_iflag = IGNPAR;
    newtio.c_oflag = OPOST;

	//Muda a entrada para o modo não Canônico
    newtio.c_lflag = 0;
         
    newtio.c_cc[VTIME]    = 0;
    newtio.c_cc[VMIN]     = 1;
        
    tcflush(0, TCIFLUSH);
    tcsetattr(0,TCSANOW,&newtio);
	return;
}

void setCanonicalMode(void) 
{
	//Retorna as configurações antigas (modo canonico)
	tcflush(0, TCIOFLUSH);
    tcsetattr(0,TCSANOW,&oldtio);
}


/* coloca o que foi digitado em uma linha da matriz */
int parseLine(char *v, char **trix, int commandLine) {
	int column;

	for(column=0; v[column] != '\0'; column++){
		trix[commandLine][column] = v[column];	
	}
		trix[commandLine][column] = '\0';

	return 0;
}

int runCommand(char *path, char *v, int parNum, char **aux, char **trix, int runBg) {
	char temp[1000], temp2[1000];
	int i, j, k, status, pipe_to_file, Nprocess;
	int fds[2];
	pid_t pid, pid2;
	char *args[100];
	FILE *ori_stdin = stdin;
	FILE *ori_stdout = stdout;
	FILE *ori_stderr = stderr;

	/* Criando novo processo */
	pid = fork();
	if(pid < 0 ) {
		printf("Erro na criacao do processo.\n");
	}
	else
	if(pid == 0) { // Processo Filho
		setpgid(0,0);
		i = 0;
		while(i < parNum) {
			k = 0;
			fflush(0);
			pipe_to_file=0;
			while(i < parNum){
			if (strcmp(aux[i], "|")==0) { // | indica o término de um comando
				i++;
				break;
			} else if (strcmp(aux[i], ">")==0) { // saida para um arquivo
				i++;
				freopen (aux[i], "w", stdout);
				pipe_to_file=1;
			} else if (strcmp(aux[i], "<")==0) { // entrada de um arquivo
				i++;
				freopen (aux[i], "r", stdin);
			} else if (strcmp(aux[i], ">>")==0) { // saida para um arquivo com append
				i++;
				freopen (aux[i], "a", stdout);
				pipe_to_file=1;
			} else if (strcmp(aux[i], "2>")==0) { // saida de erros para um arquivo
				i++;
				freopen (aux[i], "w", stderr);
			}
			else {
				args[k]= aux[i];
				k++;
			}
			i++;
		}
			args[k]= NULL;
			
			/*if(pipe(fds)){
				fprintf(ori_stdout,"Pipe error\n");
			}*/
			
			pid2=fork();
			if (pid2<0) {
				fprintf(ori_stdout,"Não foi possível executar o fork(), abortando execução do comando");
			}
			else if (pid2==0) { //Processo filho
				dup2(fds[0], 0);
				close(fds[1]);
				if (i>= parNum) {
					exit(0);
				}
			}
			else {
				if (i>= parNum) {
					if (pipe_to_file==0) {
						freopen ("/dev/tty", "a", stdout);
					}
				}
				else {
					dup2(fds[1], 1);
					close(fds[0]);
				}
				if (execv(args[0], args) == -1) {
					i=0;
					while (path[i]!='\0') {
						if (path[i]==':') {
							temp2[0]='\0';
							strcat(temp2, temp);
							strcat(temp2, "/");
							strcat(temp2, aux[0]);
							if (execv(temp2, args) != -1) { 
								break;
							}
							temp[0]='\0';
							i++;
						}
						strncat(temp, (path+i), 1);
						i++;
					}
					if (path[i]=='\0') {
						perror("ERRO");
					}
				}
				exit(0);
			}
		
                        
		}
	}
}

/* interpreta a linha de comando digitada */
int interpreter(char *v, char **trix, char *path) {
	int i, j, k, parNum, runBg;
	char **aux, c, last, comm[51];
	char currentPath[101];
	/* 'aux' eh uma matrix que guarda temporariamente cada comando em uma linha */
	/* 'c' guarda caracteres temporariamente */
	/* 'last' guarda a posicao do ultimo espaco */
	/* 'comm' guarda o comando que será tratado no momento */

	aux = (char**) malloc (sizeof(char) * 101);
	for(i=0; i < 101; i++) {
		aux[i] = (char *) malloc(sizeof(char) * 101);
	}

	last = 0;
	k = 0;
	
	for(i=0; v[i] != '\0'; i++){
		c = v[i];
			
		if(c == ' '){
			for(j = last; j < i; j++) {
				aux[k][j-last] = v[j]; 
			}
			aux[k][j-last] = '\0';
			last = i+1;
			k++;
		}
	}

	for(i = last; v[i] != '\0'; i++) {
		aux[k][i-last] = v[i];
	}
	aux[k][i-last] = '\0';
	k++;

	k--;

	parNum = k;
	while(k >= 0){
		for(j=0; aux[k][j] != '\0'; j++){
			comm[j] = aux[k][j];
		}
		comm[j] = '\0';
		k--;
	
		//printf("%s",comm);	
		/* se tiver soh 1 parametro */
		if(parNum == 0){
			/* pwd */
			if(strcmp(comm, "pwd") == 0) {
				getcwd(currentPath, 1000);
				printf("%s\n", currentPath);
			}
			if(strcmp(comm, "exit") == 0 || strcmp(comm, "quit") == 0) {
				exit(0);
			}
			if(strcmp(comm, "cd") == 0) {
				printf("Escolha o diretorio\n");
			}
			if(strcmp(comm, "jobs") == 0) {
				printf("Imprimir os jobs\n");
			}
		}
		else {
			runBg = 0;
			runCommand(path, v, parNum, aux, trix, runBg);
		}
	}

	return 0;
}

int main(void) {
	int i, j, loopProgram, commandLine;
	char c, *v, **trix, *path, *currentPath;
	int count;	

	trix = initializeMatrix();
	v = initializeVector();

	loopProgram = 1;
	commandLine = 1;

	path = (char *) malloc(sizeof(char) * 101);
	currentPath =  (char *) malloc(sizeof(char) * 101);

	path = getenv("PATH");
	/* printf("%s", path); */
	
	system("clear");

	while(loopProgram) {
		getcwd(currentPath, 1000); /* Caminho para diretorio atual */
		red(currentPath);
		
		/* lendo a linha de comando */
		for(i=0; i < 101; i++){
			v[i] = '\0';
		}		

		setNonCanonicalMode();
		/*for(i=0; c != '\n'; i++){
			c = getchar();

			v[i] = c;
		}	
		v[i] = '\0';
		c = 'x';  para evitar lixo */  
		v = readLine(v, trix, commandLine);
		setCanonicalMode();
		
		//printf("%s\n", v);
		//printf("%s", v); /* - teste - imprime a linha de comando */
		count = strlen(v);
		//printf("%d\n", count);

		parseLine(v, trix, commandLine);
		
		//for(i=0; trix[commandLine][i] != '\0'; i++){
		//	printf("%c", trix[commandLine][i]);
		//}
		//printf("\n");

		interpreter(v, trix, path);
		
		commandLine++;			
	}

	free(v);		

	return 0;
}
