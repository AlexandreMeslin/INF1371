/**
 * @file cria_threads.c
 * @brief Cria 1000 threads e mede o tempo total gasto.
 * 
 * Este programa cria 1000 threads usando a biblioteca pthreads e mede o tempo total gasto para criar todas as threads.
 * 
 * @author Alexandre Meslin
 * @date 2025-09-16
 * @version 1.0
 * @license MIT
 */

/*
 * Cabeçalhos
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <pthread.h>

/*
 * Protótipos
 */

void *theThread(void *arg);

/**
 * Função principal.
 * Cria 1000 threads e mede o tempo total gasto.
 * 
 * @return int Código de saída do programa
 */
int main(void) {
    pthread_t thread;       // thread consumidor
    struct timespec inicio; // tempo de início do programa
    struct timespec fim;    // tempo de fim do programa

    clock_gettime(CLOCK_MONOTONIC, &inicio);
    for(int i=0; i<1000; i++) {
        int rc = pthread_create(&thread, NULL, theThread, NULL);
        if (rc) {
            fprintf(stderr, "Erro ao criar thread, rc=%d\n", rc);
            exit(1);
        }
    }
    clock_gettime(CLOCK_MONOTONIC, &fim);
    double tempo = (fim.tv_sec - inicio.tv_sec) + (fim.tv_nsec - inicio.tv_nsec) / 1e9;
    printf("Tempo total: %f segundos\n", tempo);
    return 0;
}

/**
 * Função executada pela thread.
 * 
 * @param arg Argumento passado para a thread (não utilizado)
 * @return void* Retorna NULL
 */
void *theThread(void *arg) {
    // Código da thread
    pthread_exit(NULL);
}
