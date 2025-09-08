#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>

#define NTHREADS 4
#define NITERACOES 100000000

void *contador(void *pArg);
void *contador(void *pArg);
void inicializaSemaforo(sem_t *pSemaforo, int pshared, unsigned valor);
void P(sem_t *pSemaforo);
void V(sem_t *pSemaforo);

unsigned contagem = 0;
sem_t semaforo;

int main (void) {
	pthread_t vTid[NTHREADS];
	int i;

	inicializaSemaforo(&semaforo, 0, 1);

	for (i=0; i<NTHREADS; i++)
		pthread_create(&vTid[i], NULL, contador, NULL);

	for (i=0; i<NTHREADS; i++)
		pthread_join(vTid[i], NULL);

	if(contagem != NITERACOES * NTHREADS)
		printf("***Erro de contagem (%u)\n", contagem);
	else
		printf("Felizmente a contagem deu certo (%u)\n", contagem);

	return 0;
}

void *contador(void *pArg) {
	int i;

	for(i=0; i<NITERACOES; i++) {
		P(&semaforo);
		contagem++;
		V(&semaforo);
	}

	return NULL;
}

void inicializaSemaforo(sem_t *pSemaforo, int pshared, unsigned valor) {
	if(sem_init(pSemaforo, pshared, valor) == -1) {
		fprintf(stderr, "Erro na inicialização do semáforo");
		exit(1);
	}
}

void P(sem_t *pSemaforo) {
	if(sem_wait(pSemaforo) == -1) {
		fprintf(stderr, "Erro em P");
		exit(2);
	}
}

void V(sem_t *pSemaforo) {
	if(sem_post(pSemaforo) == -1) {
		fprintf(stderr, "Erro em V");
		exit(3);
	}
}
