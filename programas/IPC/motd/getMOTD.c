#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/shm.h>
#include <string.h>

int main (int argc, char *argv[])
{
	char *p;
	int segmento;

	// segmento obtido de motd.c
	segmento = atoi(argv[1]);
	if((p = (char *)shmat(segmento, 0, 0)) == NULL)
	{
		puts("Erro ao anexar memória");
		exit(-2);
	}
	
	printf ("%ld - %s\n", (long)p, p);
	
	return 0;
}
