#include <stdio.h>
#include <sys/shm.h>
#include <sys/stat.h>

#include "aviao.h"

int main (int argc, char *argv[])
{
	int segmento, i, *vLugares;
	int cpf, qtd, vendidos;

	segmento = shmget (CHAVE, NLUGARES * sizeof (int), IPC_CREAT);// | IPC_EXCL | S_IRUSR | S_IWUSR);
	vLugares = (int *) shmat (segmento, 0, 0);

	printf("Entre com o seu CPF: "); scanf ("%d", &cpf);
	printf("Entre com a quantidade de lugares: "); scanf("%d", &qtd);

	for (i=0, vendidos=0; i<NLUGARES && vendidos<qtd; i++)
	{
		if (vLugares[i] == cpf)
		{
			vLugares[i] = 0;
			vendidos++;
		}
	}

	printf ("Quantidade de lugares vendidos: %d\n", vendidos);

	shmdt (vLugares);

	return 0;
}

