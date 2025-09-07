/*
 * erros:
 *	0 - OK
 *	-1: erro desconhecido
 *	-2: erro ao alocar memória compartilhada
 *	-3: erro ao criar filho
 *	-4: erro ao alocar memória privada
 *	-5: erro ao anexar memória compartilhada
 */

#include <unistd.h>
#include <stdio.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/wait.h>

// deve ser múltiplo de 4 (???)
#define N_NUMEROS 8752
#define N_FILHOS 4
#define FALSE 0
#define TRUE -1

void preenche(double v[]);
void ordena(int segmento, int i);

int main(void)
{
	int segmento;
	int i;
	int idFilho[N_FILHOS];
	double *p; // auxiliar
	double *v[N_FILHOS]; // dados de saida
	int index[N_FILHOS];	// indice dos dados de saida
	double *pMC;	// memoria compartilhada
	int acabou = FALSE;	// se acabou o merge

	if((segmento=shmget(IPC_PRIVATE, N_NUMEROS * sizeof(double), IPC_CREAT | IPC_EXCL | S_IRUSR | S_IWUSR)) != 0)
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
	
	if((pMC = (double *) shmat (segmento, 0, 0)) == NULL)
	{
		puts ("Erro ao associar o segmento ao processo");
		exit (-5);
	}

	preenche(pMC);

	for(i=0; i<N_FILHOS; i++)
	{
		idFilho[i] = fork();
		if(idFilho[i] < 0)
		{
			printf("Erro ao criar filho #%d\n", i);
			exit(-3);
		}
		if(idFilho[i] == 0)
		{
			ordena(segmento, i);
			exit(0);
		}
	}
	
	// espera os filhos morrerem
	for(i=0; i<N_FILHOS; i++) wait(NULL);

	if((p = (double *)malloc(N_NUMEROS * sizeof(double))) == NULL)
	{
		puts("Erro ao aloca vetor de saida");
		exit(-4);
	}

	for(i=0; i<N_FILHOS; i++)
	{
		v[i] = pMC + (N_NUMEROS / N_FILHOS) * i;
		index[i] = 0;
	}
	
	acabou = FALSE;
	while(!acabou)
	{
		int vistos = 0;
		for(i=0; i<N_FILHOS; i++) vistos += index[i];
		if(vistos>=N_NUMEROS) acabou = TRUE;
		else
		{
			for(j=0
		}
	}

	return 0;
}

void preenche(double v[])
{
}

void ordena(int segmento, int i)
{
}

