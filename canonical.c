//Inclusão de bibliotecas do sistema
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>

//Inclusão de bibliotecas próprias
#include "canonical.h"

void Canonical_setNonCanonicalMode (void) {
	struct termios newtio;
	tcgetattr(0,&oldtio);
	bzero(&newtio,sizeof(newtio));
	newtio.c_cflag = CRTSCTS | CS8 | CLOCAL | CREAD | ICANON;
	newtio.c_iflag = IGNPAR;
    	newtio.c_oflag = OPOST;
   	newtio.c_lflag = 0;
	newtio.c_cc[VTIME]    = 0;
    	newtio.c_cc[VMIN]     = 1;
        tcflush(0, TCIFLUSH);
    	tcsetattr(0,TCSANOW,&newtio);
	return;
}

void Canonical_setCanonicalMode(void) {
	tcflush(0, TCIOFLUSH);
    	tcsetattr(0,TCSANOW,&oldtio);
}
