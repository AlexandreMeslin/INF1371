#include <stdio.h>
#include <sys/shm.h>
#include <sys/stat.h>

#include "aviao.h"

int main (int argc, char *argv[])
{
	int segmento, i, *vLugares;
	int cpf, qtd, comprados;

	segmento = shmget (CHAVE, NLUGARES * sizeof (int), IPC_CREAT); // | IPC_EXCL | S_IRUSR | S_IWUSR);
	vLugares = (int *) shmat (segmento, 0, 0);

	printf("Entre com o seu CPF: "); scanf ("%d", &cpf);
	printf("Entre com a quantidade de lugares: "); scanf("%d", &qtd);

	for (i=0, comprados=0; i<NLUGARES && comprados < qtd; i++)
	{
		if (vLugares[i] == 0)
		{
			vLugares[i] = cpf;
			comprados++;
		}
	}

	printf ("Quantidade de lugares comprados: %d\n", comprados);

	shmdt (vLugares);

	return 0;
}

