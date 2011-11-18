CC = gcc
C_FLAGS = -Wall -g

EXECUTABLE = Pioleta
SOURCES = canonical.c canonical.h colors.c colors.h jobs.c jobs.h signal_capture.c signal_capture.h erros.h shell.c

ALL : 
	$(CC) $(SOURCES) -o $(EXECUTABLE) $(C_FLAGS) 

run : 
	./$(EXECUTABLE)

clean : 
	rm -f *.o *~ 
	rm -f $(EXECUTABLE)