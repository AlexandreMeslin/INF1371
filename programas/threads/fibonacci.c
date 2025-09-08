/**
 * Programa de cálculo da série de Fibonacci sem threads
 * 
 * O programa calcula a série de Fibonacci para valores crescentes de n,
 * iniciando em 0, e registra os resultados em uma lista encadeada.
 * 
 * O programa não termina, pois está em um loop infinito. Para terminar o programa,
 * é necessário enviar um sinal de interrupção (Ctrl+C).
 * 
 * @author: Alexandre Meslin
 * @date: 2025-09-07
 * @version: 1.0
 * @license: MIT
 * @see: https://en.wikipedia.org/wiki/Fibonacci_number
 * @see: fibonacci-threads.c
 */

#include <stdio.h>
#include <pthread.h>
#include <time.h>
#include <stdlib.h>

#define EVER ;;

struct numeros {
    int n;
    long result;
    double tempo;
    struct numeros *p_next;
};

struct thread_parm_t{
    struct numeros p;
};

long fibonacci(int n);
void registra_resultados(struct numeros *phead);

int main(void) {
    int n = 0;
    long resultado; /** resultado da série n de Fibonacci */
    struct timespec inicio, fim;
    struct numeros *phead;
    struct numeros *p;

    printf("Programa de threads de Fibonacci\n");

    clock_gettime(CLOCK_REALTIME, &inicio);
    for(EVER) {
        phead = NULL;
        for(int i=0; i<n; i++) {
            resultado = fibonacci(i);
            p = (struct numeros *)malloc(sizeof(struct numeros));
            if(p == NULL) {
                fprintf(stderr, "Erro de alocação de memória\n");
                exit(1);
            }
            clock_gettime(CLOCK_REALTIME, &fim);
            double tempo_gasto = fim.tv_sec - inicio.tv_sec + (fim.tv_nsec - inicio.tv_nsec) / 1000000000.0;
            p->n = i;
            p->result = resultado;
            p->tempo = tempo_gasto;
            p->p_next = phead;
            phead = p;
            fprintf(stderr, "Fibonacci(%d) = %ld - t = %fs\n", i, resultado, tempo_gasto);
        }
        registra_resultados(phead);
        n++;
    }
    return 0;
}

/**
 * Cálculo da série de Fibonacci
 * 
 * @param n Número da série a ser calculada
 * @return Resultado da série de Fibonacci
 */
long fibonacci(int n) {
    if (n <= 1)
        return n;
    return fibonacci(n - 1) + fibonacci(n - 2);
}

/**
 * Registra os resultados da série de Fibonacci em um arquivo
 * 
 * @param phead Ponteiro para a cabeça da lista de resultados
 */
void registra_resultados(struct numeros *phead) {
    struct numeros *p = phead;
    FILE *f = fopen("fibonacci_results.txt", "w");
    if(f == NULL) {
        fprintf(stderr, "Erro ao abrir o arquivo para escrita\n");
        return;
    }
    while(p != NULL) {
        fprintf(f, "Fibonacci(%d) = %ld - t = %fs\n", p->n, p->result, p->tempo);
        struct numeros *temp = p;
        p = p->p_next;
        free(temp);
    }
    fclose(f);
}