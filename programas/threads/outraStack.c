#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

void *thread(void *vargp);

char **p;

int main (void) {
	long i;
	pthread_t tid;

	char *vMsgs[] = {
		"Primeira mensagem",
		"Segunda mensagem"
	};

	p = vMsgs;

	for (i=0; i<2; i++)
		pthread_create(&tid, NULL, thread, (void *) i);
	fprintf(stderr, "Fim da thread principal\n");
	pthread_exit(NULL);

	return 0;
}

void *thread(void *vargp) {
	int id;
	static int sVar = 0;

	id = (long) vargp;
	printf ("Thread %d: %s (sVar = %d)\n", id, p[id], ++sVar);
	sleep (30);

	return NULL;
}
