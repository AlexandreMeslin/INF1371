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

	if ((segmento = shmget(8753, strlen(argv[1]), S_IRUSR | S_IWUSR | 0x666)) < 0)
	{
		puts("Erro ao alocar memória");
		exit(-1);
	}

	printf("Segmento %d alocado\n", segmento);

	if((p = (char *)shmat(segmento, 0, 0)) == NULL)
	{
		puts("Erro ao anexar memória");
		exit(-2);
	}
	
	printf ("%ld - %s\n", (long)p, p);
	
	return 0;
}
