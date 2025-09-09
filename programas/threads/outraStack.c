#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

// Protótipos
void *thread(void *vargp);

char **p;	/** Ponteiro global para as mensagens */

int main (void) {
	long i;
	pthread_t tid;	/** Identificador da thread */

	char *vMsgs[] = {
		"Primeira mensagem",
		"Segunda mensagem"
	};

	p = vMsgs;	// Ponteiro aponta para o vetor de mensagens

	// Cria duas novas threads
	fprintf(stderr, "Vou criar as threads\n");
	for (i=0; i<2; i++) {
		int rc = pthread_create(&tid, NULL, thread, (void *) i);
		if (rc) {
			fprintf(stderr, "pthread_create() failed, rc=%d\n", rc);
			exit(1);
		}
	}
	fprintf(stderr, "Fim da thread principal\n");
	pthread_exit(NULL);

	return 0;
}

/**
 * Função executada pela nova thread
 * 
 * @param vargp Argumento passado para a thread (índice da mensagem)
 * @return NULL
 */
void *thread(void *vargp) {
	int id;
	static int sVar = 0;	// Variável estática (uma por função e não por thread)

	id = (long) vargp;
	printf ("Thread %d: %s (sVar = %d)\n", id, p[id], ++sVar);
	sleep (30);

	return NULL;
}
