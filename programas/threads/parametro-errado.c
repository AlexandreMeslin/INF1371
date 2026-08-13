/**
 * Esta versão modifica os parâmetros antes que cada thread 
 * obtenha os valores corretos
 */
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define N_THREADS	4

// Tipo dos parâmetros da thread
typedef struct {
	int   value;
	char  string[128];
} thread_parm_t;

void *threadfunc(void *parm);

int main(int argc, char *argv[]) {
	pthread_t             thread[N_THREADS];// Identificador da thread
	int                   rc;			// Código de retorno das funções
	pthread_attr_t        pta;			// Atributos da thread
	thread_parm_t         *parm=NULL;	// Parâmetros para a thread

	// Create a thread attributes object
	printf("Create a thread attributes object\n");
	rc = pthread_attr_init(&pta);
	if(rc) {
		fprintf(stderr, "pthread_attr_init() failed, rc=%d\n", rc);
		exit(1);
	}

	// Create a thread with default attributes and multiple parameters
	printf("Create thread using the default attributes e vários parâmetros\n");
	/* Set up multiple parameters to pass to the thread */
	parm = malloc(sizeof(thread_parm_t));
	if(parm == NULL) {
		fprintf(stderr, "malloc() failed\n");
		exit(1);
	}
	// vamos criar n threads
	for(int i=0; i<N_THREADS; i++) {
		parm->value = 77 + i;
		strcpy(parm->string, "Inside secondary thread");
		rc = pthread_create(&thread[i], &pta, threadfunc, (void *)parm);
		if(rc) {
			fprintf(stderr, "pthread_create() failed, rc=%d\n", rc);
			exit(1);
		}
	}

	// Destroy the thread attributes object, since it is no longer needed
	printf("Destroy thread attributes object\n");
	rc = pthread_attr_destroy(&pta);
	if(rc) {
		fprintf(stderr, "pthread_attr_destroy() failed, rc=%d\n", rc);
		exit(1);
	}

	// Wait for the thread to complete
	printf("Wait for thread to complete\n");
	for(int i=0; i<N_THREADS; i++) {
		rc = pthread_join(thread[i], NULL);
		if(rc) {
			fprintf(stderr, "pthread_join() failed, rc=%d\n", rc);
			exit(1);
		}
	}

	printf("Main completed\n");
	return 0;
}

/**
 * Função executada pela nova thread
 * 
 * @param parm Parâmetros passados para a thread
 * @return NULL
 */
void *threadfunc(void *parm) {
	thread_parm_t *p = (thread_parm_t *)parm;
	printf("%s, parm = %d\n", p->string, p->value);
	sleep(30);
	free(p);
	return NULL;
}
