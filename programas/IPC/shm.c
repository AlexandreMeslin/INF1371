#include <stdio.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main (int argc, char *argv[])
{
	int segmento, *p;
	int id, pid, status;
	struct shmid_ds shmbuffer;

	// aloca a memória compartilhada
	segmento = shmget (IPC_PRIVATE, sizeof (int), IPC_CREAT | IPC_EXCL | S_IRUSR | S_IWUSR);

	// associa a memória compartilhada ao processo
	p = (int *) shmat (segmento, 0, 0);

	// tamanho da área alocada
	shmctl(segmento, IPC_STAT, &shmbuffer);
	printf("Tamanho da área alocada: %d bytes\n", (int)shmbuffer.shm_segsz);

	*p = 8752;

	if ((id = fork()) < 0)
	{
		puts ("Erro na criação do novo processo");
		exit (-2);
	}
	else if (id == 0)
	{
		*p += 5;
		printf ("Processo filho = %d\n", *p);
	}
	else
	{
		pid = wait (&status);
		*p += 10;
		printf ("Processo pai = %d\n", *p);
	}
	
	// libera a memória compartilhada do processo
	shmdt (p);

	// libera a memória compartilhada
	shmctl (segmento, IPC_RMID, 0);
	
	return 0;
}
