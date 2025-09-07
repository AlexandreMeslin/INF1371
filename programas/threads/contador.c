#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#define NTHREADS 2

typedef struct
{
	int numero;
	char *nome;
	int tempo;
	int operacao;
	int *pContagem;
	int vezes;
} tParametroThread;

void *contador(void *pArg);

int main(void)
{
	pthread_t tid[NTHREADS];
	tParametroThread parametro[NTHREADS];
	int i, contagem;

	parametro[0].numero = 1;
	parametro[0].tempo = 1;
	parametro[0].nome = "Incremento: ";
	parametro[0].operacao = 1;	// soma 1
	parametro[0].pContagem = &contagem;
	parametro[0].vezes = 20;
	
	parametro[1].numero = 2;
	parametro[1].tempo = 2;
	parametro[1].nome = "Descremento: ";
	parametro[1].operacao = -1;	// diminui 1
	parametro[1].pContagem = &contagem;
	parametro[1].vezes = 30;

	contagem = 0;
	
	for (i=0; i<NTHREADS; i++)
		pthread_create(&tid[i], NULL, contador, &parametro[i]);

	for (i=0; i<NTHREADS; i++)
		pthread_join(tid[i], NULL);

	return 0;
}

void *contador(void *pArg)
{
	int i;
	for(i=0; i<((tParametroThread *)pArg)->vezes; i++)
	{
		printf ("%s (%d): %d\n", ((tParametroThread *)pArg)->nome, ((tParametroThread *)pArg)->numero, (*((tParametroThread *)pArg)->pContagem) += ((tParametroThread *)pArg)->operacao);
		sleep(((tParametroThread *)pArg)->tempo);
	}
	return NULL;
}
