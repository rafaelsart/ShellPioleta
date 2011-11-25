CC = gcc
C_FLAGS = -Wall -g

EXECUTABLE = Pioleta
SOURCES = alocacao.c alocacao.h canonical.c canonical.h colors.c colors.h comando.c comando.h jobs.c jobs.h signal_capture.c signal_capture.h terminal.c terminal.h tela.c tela.h shell.c

ALL : 
	$(CC) $(SOURCES) -o $(EXECUTABLE) $(C_FLAGS) 

run : 
	./$(EXECUTABLE)

clean : 
	rm -f *.o *~ 
	rm -f $(EXECUTABLE)
