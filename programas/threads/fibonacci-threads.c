/**
 * Programa de cálculo da série de Fibonacci utilizando threads
 * 
 * Cada thread calcula a série de Fibonacci para um valor n, e armazena os resultados
 * em uma lista encadeada. As listas de resultados são armazenadas em uma fila de tasks.
 * 
 * O programa principal cria uma nova task a cada iteração, onde cada task calcula a
 * série de Fibonacci para valores de 0 a n-1, onde n é incrementado a cada iteração.
 * 
 * A cada iteração, o programa registra o tempo gasto para calcular cada valor da série
 * de Fibonacci.
 * 
 * O programa não termina, pois está em um loop infinito. Para terminar o programa,
 * é necessário enviar um sinal de interrupção (Ctrl+C).
 * 
 * @author: Alexandre Meslin
 * @date: 2025-09-07
 * @version: 1.0
 * @license: MIT
 * @see: https://en.wikipedia.org/wiki/Fibonacci_number
 * @see: fibonacci.c
 */

#include <stdio.h>
#include <pthread.h>
#include <time.h>
#include <stdlib.h>

#define EVER ;;

/*
 * Estruturas
 */
/** Estrutura para armazenar os resultados da série de Fibonacci */
struct numeros {
    int n;                  // número da série de Fibonacci
    long result;            // resultado da série de Fibonacci
    double tempo;           // tempo gasto para calcular a série de Fibonacci
    struct numeros *p_next; // ponteiro para o próximo resultado
};

/** Estrutura para armazenar uma task na fila de tasks */
struct task {
    struct numeros *phead;  // ponteiro para a cabeça da lista de resultados
    struct task *p_next;    // ponteiro para a próxima task
};

/** Estrutura para passar parâmetros para a thread consumidor */
struct thread_parm_t{
    struct task **pFila;            // ponteiro para a fila de tasks
    pthread_mutex_t *mutex;         // mutex para proteger o acesso à fila
    pthread_cond_t *cond;           // variável de condição para sinalizar a presença de novas tasks
    pthread_mutex_t *file_mutex;    // mutex para proteger o acesso ao arquivo
};

/*
 * Protótipos
 */
long fibonacci(int n);
void registra_resultados(struct numeros *phead, pthread_mutex_t *file_mutex);
void adiciona_task(struct task **ppFila, struct numeros *phead, pthread_mutex_t *mutex, pthread_cond_t *cond);
void produtor(struct task **ppFila, int n, pthread_mutex_t *mutex, pthread_cond_t *cond, pthread_mutex_t *file_mutex);
void *consumer(void *arg);

/*
 * Variáveis globais 
 */
struct timespec inicio; // tempo de início do programa

/**
 * Função principal
 * 
 * Cria uma thread consumidor e entra em um loop infinito, onde a cada iteração
 * cria uma nova task para calcular a série de Fibonacci para valores de 0 a n-1,
 * onde n é incrementado a cada iteração.
 * 
 * @return 0 se o programa terminar corretamente
 */
int main(void) {
    int n = 0;                  /** número de elementos da série de Fibonacci a serem calculados */
    struct task *pFila = NULL;  /** fila de tasks */
    
    pthread_t thread;           /** thread consumidor */
    struct thread_parm_t parm;  /** parâmetros para a thread consumidor */
    pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;       /** mutex para proteger o acesso à fila */
    pthread_cond_t cond = PTHREAD_COND_INITIALIZER;          /** variável de condição para sinalizar a presença de novas tasks */
    pthread_mutex_t file_mutex = PTHREAD_MUTEX_INITIALIZER;  /** mutex para proteger o acesso ao arquivo */

    // Inicializa os parâmetros para a thread consumidor
    parm.pFila = &pFila;
    parm.mutex = &mutex;
    parm.cond = &cond;
    parm.file_mutex = &file_mutex;

    // Cria a thread consumidor
    int rc = pthread_create(&thread, NULL, consumer, &parm);
    if(rc) {
        fprintf(stderr, "Erro ao criar thread consumidor, rc=%d\n", rc);
        exit(1);
    }

    printf("Programa de threads de Fibonacci\n");

    clock_gettime(CLOCK_TAI, &inicio);
    for(EVER) {
        // Início de uma task
        produtor(&pFila, n, &mutex, &cond, &file_mutex);
        // Fim de uma task
        n++;
    }

    // Nunca chega aqui

    // Limpa os recursos
    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&cond);
    pthread_mutex_destroy(&file_mutex);

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
void registra_resultados(struct numeros *phead, pthread_mutex_t *file_mutex) {
    struct numeros *p = phead;
    pthread_mutex_lock(file_mutex);
    FILE *f = fopen("fibonacci_results.txt", "w");
    if(f == NULL) {
        fprintf(stderr, "Erro ao abrir o arquivo para escrita\n");
        pthread_mutex_unlock(file_mutex);
        return;
    }
    while(p != NULL) {
        fprintf(f, "[%d] Fibonacci(%d) = %ld - t = %fs\n", __LINE__, p->n, p->result, p->tempo);
        struct numeros *temp = p;
        p = p->p_next;
        free(temp);
    }
    fclose(f);
    fprintf(stderr, "[%d]\n", __LINE__);
    pthread_mutex_unlock(file_mutex);
    fprintf(stderr, "[%d]\n", __LINE__);
}

/**
 * Adiciona uma task na fila de tasks
 * 
 * A fila é uma lista encadeada de tasks, onde cada task contém a lista de resultados
 * da série de Fibonacci calculados naquela task.
 * 
 * A task é adicionada no final da fila.
 * 
 * @param ppFila Ponteiro para a cabeça da fila de tasks
 * @param phead Ponteiro para a cabeça da lista de resultados da task
 * 
 */
void adiciona_task(struct task **ppFila, struct numeros *phead, pthread_mutex_t *mutex, pthread_cond_t *cond) {
    struct task *pNew = (struct task *)malloc(sizeof(struct task));
    if(pNew == NULL) {
        fprintf(stderr, "Erro de alocação de memória para task\n");
        exit(1);
    }
    pNew->phead = phead;
    pNew->p_next = NULL;

    pthread_mutex_lock(mutex);  // Protege o acesso à fila
    if(*ppFila == NULL) {
        *ppFila = pNew;
    } else {
        struct task *p = *ppFila;
        while(p->p_next != NULL) {
            p = p->p_next;
        }
        p->p_next = pNew;
    }
    pthread_cond_signal(cond);   // Sinaliza que há uma nova task na fila
    pthread_mutex_unlock(mutex); // Libera o acesso à fila
}

/**
 * Função que representa o produtor de tasks
 * 
 * Cada task calcula a série de Fibonacci para valores de 0 a n-1, onde n é o
 * parâmetro passado para a função.
 * 
 * @param n Número de elementos da série de Fibonacci a serem calculados
 */
void produtor(struct task **pFila, int n, pthread_mutex_t *mutex, pthread_cond_t *cond, pthread_mutex_t *file_mutex) {
    long resultado; /** resultado da série n de Fibonacci */
    struct timespec fim;
    struct numeros *phead = NULL;
    struct numeros *p;

    for(int i=0; i<n; i++) {
        resultado = fibonacci(i);
        clock_gettime(CLOCK_TAI, &fim);
        double tempo_gasto = fim.tv_sec - inicio.tv_sec + (fim.tv_nsec - inicio.tv_nsec) / 1000000000.0;
        p = (struct numeros *)malloc(sizeof(struct numeros));
        if(p == NULL) {
            fprintf(stderr, "Erro de alocação de memória\n");
            exit(1);
        }
        p->n = i;
        p->result = resultado;
        p->tempo = tempo_gasto;
        p->p_next = phead;
        phead = p;
        fprintf(stderr, "[%d] Fibonacci(%d) = %ld - t = %fs\n", __LINE__, i, resultado, tempo_gasto);
    }
    adiciona_task(pFila, phead, mutex, cond);
}

/**
 * Função que representa o consumidor de tasks
 * 
 * O consumidor retira uma task da fila e registra os resultados em um arquivo.
 * 
 * @param arg Ponteiro para a estrutura de parâmetros da thread
 * @return NULL
 */
void *consumer(void *arg) {
    struct thread_parm_t *param;
    struct task *pTask;

    param = (struct thread_parm_t *)arg;

    for(EVER) {
        fprintf(stderr, "[%d] Thread consumidor esperando por uma task\n", __LINE__);
        pthread_mutex_lock(param->mutex); // Protege o acesso à fila
        fprintf(stderr, "[%d] Thread consumidor acordou\n", __LINE__);

        // Espera até que haja uma task na fila
        // Importante: usar while para evitar wakeup spurious
        while(*(param->pFila) == NULL) {
            pthread_cond_wait(param->cond, param->mutex); // Espera por uma nova task
        }

        // Retira a task da fila
        pTask = *(param->pFila);
        *(param->pFila) = pTask->p_next;
        pthread_mutex_unlock(param->mutex); // Libera o acesso à fila

        // Processa a task (fora da região crítica)
        registra_resultados(pTask->phead, param->file_mutex);
        free(pTask);
    }
    fprintf(stderr, "[%d] Thread consumidor terminando\n", __LINE__);
    return NULL;
}