/**
 * Programa que cria 1000 processos filhos usando fork()
 * e mede o tempo total gasto para criar esses processos.
 * Compilar com: gcc -o cria_processos cria_processos.c -std=c17
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

/**
 * Função principal.
 * Cria 1000 processos filhos usando fork() e mede o tempo total gasto.
 * 
 * @return int Código de saída do programa
 */
int main(void) {
    struct timespec inicio; // tempo de início do programa
    struct timespec fim;    // tempo de fim do programa

    clock_gettime(CLOCK_MONOTONIC, &inicio);
    for(int i=0; i<1000; i++) {
        pid_t pid = fork();
        if (pid < 0) {
            // Erro ao criar o processo
            perror("fork");
            exit(1);
        } else if (pid == 0) {
            // Processo filho
            //printf("Processo filho: PID = %d, PPID = %d\n", getpid(), getppid());
            exit(0);
        } else {
            // Processo pai
            //printf("Processo pai: PID = %d, PPID = %d, Filho PID = %d\n", getpid(), getppid(), pid);
            //wait(NULL); // Espera o processo filho terminar
        }
    }

    clock_gettime(CLOCK_MONOTONIC, &fim);
    double tempo = (fim.tv_sec - inicio.tv_sec) + (fim.tv_nsec - inicio.tv_nsec) / 1e9;
    printf("Tempo total: %f segundos\n", tempo);

    return 0;
}