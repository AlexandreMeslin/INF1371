#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#define NTHREADS 5
#define EVER ;;

void *outraThread(void *vargp);

int main (void) {
	pthread_t tid;

	fprintf(stderr, "Vou criar as threads\n");
    for(int i=0; i<NTHREADS; i++) {
    	pthread_create(&tid, NULL, outraThread, NULL);
    }
	fprintf(stderr, "Thread criadas\n");
    for(EVER) sleep (30);
	return 0;
}

void *outraThread(void *vargp) {
	puts("Nova thread nascendo...\n");
    for(EVER) sleep (30);
	return NULL;
}

