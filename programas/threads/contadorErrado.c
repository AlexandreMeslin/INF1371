#include <stdio.h>
#include <pthread.h>

#define NTHREADS 4
#define NITERACOES 100000000

void *contador(void *pArg);

unsigned contagem = 0;

int main (void) {
	pthread_t vTid[NTHREADS];
	int i;

	for (i=0; i<NTHREADS; i++)
		pthread_create(&vTid[i], NULL, contador, NULL);

	for (i=0; i<NTHREADS; i++)
		pthread_join(vTid[i], NULL);

	if(contagem != NITERACOES * NTHREADS)
		printf("***Erro de contagem (%u != %u)\n", contagem, NITERACOES * NTHREADS);
	else
		printf("Infelizmente a contagem deu certo (%u)\n", contagem);

	return 0;
}

void *contador(void *pArg) {
	int i;

	for (i=0; i<NITERACOES; i++)
		contagem++;

	return NULL;
}
