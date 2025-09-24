#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

int shared_variable = 0;

void* increment(void* arg) {
    for (int i = 0; i < 10000; i++) {
        shared_variable++;
    }
    return NULL;
}

int main() {
    pthread_t thread1, thread2;

    // Cria duas threads
    pthread_create(&thread1, NULL, increment, NULL);
    pthread_create(&thread2, NULL, increment, NULL);

    // Espera pelas threads terminarem
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    printf("Valor final da variável compartilhada: %d\n", shared_variable);
    return 0;
}
