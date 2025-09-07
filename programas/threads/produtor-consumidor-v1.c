/**
 * Gerado pelo Chat-CPT v4
 */
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define BUFFER_SIZE 10

// Buffer compartilhado
int buffer[BUFFER_SIZE];
int count = 0;

// Mutex e variáveis de condição
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond_empty = PTHREAD_COND_INITIALIZER;

void* producer(void* arg) {
    int i = 0;
    while (1) {
        // Simula a produção de um item
        int item = i++;

        // Tranca o mutex antes de acessar o buffer
        pthread_mutex_lock(&mutex);

//        // Espera até que haja espaço no buffer
//        while (count == BUFFER_SIZE) {
//            pthread_cond_wait(&cond_full, &mutex);
//        }

        // Adiciona o item ao buffer
        buffer[count] = item;
        count++;
        printf("Produzido: %d\n", item);

        // Sinaliza que o buffer não está mais vazio
        pthread_cond_signal(&cond_empty);

        // Destranca o mutex
        pthread_mutex_unlock(&mutex);

        // Simula um tempo de produção
        sleep(1);
    }
    return NULL;
}

void* consumer(void* arg) {
    while (1) {
        // Tranca o mutex antes de acessar o buffer
        pthread_mutex_lock(&mutex);

        // Espera até que haja itens no buffer
        while (count == 0) {
            pthread_cond_wait(&cond_empty, &mutex);
        }

        // Remove o item do buffer
        int item = buffer[--count];
        printf("Consumido: %d\n", item);

//        // Sinaliza que o buffer não está mais cheio
//        pthread_cond_signal(&cond_full);

        // Destranca o mutex
        pthread_mutex_unlock(&mutex);

        // Simula um tempo de consumo
        sleep(1);
    }
    return NULL;
}

int main() {
    pthread_t producer_thread, consumer_thread;

    // Cria as threads do produtor e do consumidor
    pthread_create(&producer_thread, NULL, producer, NULL);
    pthread_create(&consumer_thread, NULL, consumer, NULL);

    // Espera as threads terminarem (nunca vão terminar neste exemplo)
    pthread_join(producer_thread, NULL);
    pthread_join(consumer_thread, NULL);

    return 0;
}
