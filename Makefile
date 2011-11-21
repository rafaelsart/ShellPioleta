CC = gcc
C_FLAGS = -Wall -g

EXECUTABLE = Pioleta
SOURCES = canonical.c canonical.h colors.c colors.h path.c path.h alocacao.c alocacao.h jobs.c jobs.h signal_capture.c signal_capture.h tela.c tela.h erros.h shell.c

ALL : 
	$(CC) $(SOURCES) -o $(EXECUTABLE) $(C_FLAGS) 

run : 
	./$(EXECUTABLE)

clean : 
	rm -f *.o *~ 
	rm -f $(EXECUTABLE)
