#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <stdlib.h>

void *thread(void *vargp);

char **p;

int main (void) {
	long i;
	pthread_t tid;

	char *vMsgs[2];
	vMsgs[0] = malloc(100);
	vMsgs[1] = malloc(100);
	strcpy(vMsgs[0], "Primeira mensagem");
	strcpy(vMsgs[1], "Segunda mensagem");

	p = vMsgs;

	for (i=0; i<2; i++)
		pthread_create(&tid, NULL, thread, (void *) i);
	pthread_exit(NULL);

	return 0;
}

void *thread(void *vargp) {
	int id;
	static int sVar = 0;

	id = (long) vargp;
	printf ("Thread %d: %s (sVar = %d)\n", id, p[id], ++sVar);

	return NULL;
}
