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
	struct shmid_ds shmbuffer;

	if ((segmento = shmget(8753, strlen(argv[1]), IPC_CREAT | S_IRUSR | S_IWUSR | 0x666)) < 0)
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
	
	shmctl(segmento, IPC_STAT, &shmbuffer);
	printf("Tamanho da área alocada: %d bytes\n", (int)shmbuffer.shm_segsz);


	puts(argv[1]);
	strcpy(p, argv[1]);
	
	return 0;
}
