#include <unistd.h>
#include <stdio.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <errno.h>

#include "aviao.h"

int main (int argc, char *argv[])
{
	int segmento, i, *p;
	struct shmid_ds buffer;
	
	puts ("Criando o aviao");
	// aloca a memória compartilhada
	// IPC_EXCL | S_IRUSR | S_IWUSR);
//	if ((segmento = shmget(CHAVE, NLUGARES * sizeof (int), IPC_CREAT | 01600)) == -1)
	if ((segmento = shmget(CHAVE, NLUGARES * sizeof (int), IPC_CREAT | IPC_EXCL | S_IRUSR | S_IWUSR)) == -1)
	{
		switch (errno)
		{
			case EACCES: puts ("A shared memory identifier exists for key but the calling process does not have permission (as specified by the low-order 9 bits of shmflg)."); break;
			case EEXIST: puts ("A shared memory identifier exists for key and shmflg specifies both IPC_CREATE and IPC_EXCL."); break;
			case EINVAL: puts ("size is either less than the system-defined minimum or greater than the system-defined maximum, or a shared memory identifier exists for key and the size of the shared memory area associated with it is less than size and size is not equal to zero."); break;
			case ENOENT: puts ("A shared memory identifier does not exist for key and shmflg does not specify IPC_CREATE."); break;
			case ENOMEM: puts ("The available data space is not large enough to create a shared memory identifier and associated shared memory area."); break;
			case ENOSPC: puts ("The number of shared memory identifiers would exceed the system-defined limit."); break;
			default: puts ("An operating system error occurred that does not map directly to any of the above errors."); break;
		}
		puts ("Erro ao alocar o segmento");
		exit (-2);
	}
	printf ("Memoria alocada no segmento %d\n", segmento);

	if (shmctl(segmento, IPC_STAT, &buffer) == -1)
		puts ("erro ao consultar o status da memória alocada");
	else
		printf ("%d bytes alocados\n", (int)buffer.shm_segsz);
	
	// associa a memória compartilhada ao processo
	p = (int *) shmat (segmento, 0, 0);
	if (p == NULL)
	{
		puts ("Erro ao associar o segmento ao processo");
		exit (-1);
	}
	puts ("Segmento associado ao processo");
	for (i=0; i<NLUGARES; i++) p[i] = 0;	// todos os lugares estão vagos
	puts ("Lugares inicializados");
	for(;;)
	{
		printf ("\nLugares reservados: ");
		for (i=0; i<NLUGARES; i++)
		{
			printf ("[%4d %4d] ", i, p[i]);
		}
		fflush(stdout);
		sleep (5);
	}
}
