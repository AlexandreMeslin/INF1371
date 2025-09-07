#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

void *outraThread(void *vargp);

int main (void) {
	pthread_t tid;

	fprintf(stderr, "Vou criar a thread\n");
	pthread_create(&tid, NULL, outraThread, NULL);
	fprintf(stderr, "Thread criada, esperando pelo término\n");
	pthread_join(tid, NULL);
	fprintf(stderr, "Fim da thread\n");
	return 0;
}

void *outraThread(void *vargp) {
	puts("Nova thread nascendo...");
	sleep (30);
	puts("Alo mundo!");
	return NULL;
}

