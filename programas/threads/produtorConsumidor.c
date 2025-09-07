#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <semaphore.h>

#define NITERACOES 5

typedef struct {
	int buffer;
	sem_t cheio;
	sem_t vazio;
} tCompartilhamento;

void *produtor(void *pArg);
void *consumidor(void *pArg);
void P(sem_t *pSemaforo);
void V(sem_t *pSemaforo);

tCompartilhamento compartilhado;

int main(void) {
	pthread_t tidProdutor, tidConsumidor;

	sem_init(&compartilhado.vazio, 0, 1);
	sem_init(&compartilhado.cheio, 0, 0);

	pthread_create(&tidProdutor, NULL, produtor, NULL);
	pthread_create(&tidConsumidor, NULL, consumidor, NULL);

	pthread_join(tidProdutor, NULL);
	pthread_join(tidConsumidor, NULL);

	return 0;
}

void *produtor(void *pArg) {
	int i, item;

	for(i=0; i<NITERACOES; i++) {
		item = i;
		printf("Produzindo %d\n", item);
		P(&compartilhado.vazio);
		compartilhado.buffer = item;
		V(&compartilhado.cheio);
	}
	
	return NULL;
}

void *consumidor(void *pArg) {
	int i, item;

	for(i=0; i<NITERACOES; i++) {
		P(&compartilhado.cheio);
		item = compartilhado.buffer;
		V(&compartilhado.vazio);
		printf("Consumido %d\n", item);
	}
	
	return NULL;
}

void P(sem_t *pSemaforo) {
	if(sem_wait(pSemaforo) == -1) {
		fprintf(stderr, "Erro em P");
		exit(-2);
	}
}

void V(sem_t *pSemaforo) {
	if(sem_post(pSemaforo) == -1) {
		fprintf(stderr, "Erro em V");
		exit(-3);
	}
}
