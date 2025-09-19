/**
 * @file thread_pool.c
 * @brief Implementação de um pool de threads simples.
 * Este programa cria um pool de threads que executam tarefas de uma fila.
 * Cada thread pega uma tarefa da fila e a executa.
 * Compilar com: gcc -o thread_pool thread_pool.c -lpthread -std=c17
 * @autor Alexandre Meslin
 * @data 2025-09-16
 * @versão 1.0
 * @licença MIT
 */

/*
 * Cabeçalhos
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

/*
 * Definições e estruturas
 */

/**
 * Estrutura para uma tarefa no pool de threads
 * Representa uma única tarefa a ser executada por uma thread.
 * Contém um ponteiro para a função a ser executada e um argumento para essa função.
 */
typedef struct {
    void (*function)(void *);  // Ponteiro para função
    void *arg;                 // Argumento para a função
} task_t;

/**
 * Estrutura para o pool de threads
 * Contém informações sobre as threads, a fila de tarefas e mecanismos de sincronização.
 */
typedef struct {
    pthread_mutex_t lock;     // Mutex para sincronização
    pthread_cond_t cond;      // Condition variable
    pthread_cond_t finished;  // Para wait_all
    task_t *queue;            // Fila de tarefas
    int queue_size;           // Tamanho máximo da fila
    int queue_count;          // Tarefas na fila
    int queue_front;          // Frente da fila
    int queue_rear;           // Final da fila
    pthread_t *threads;       // Array de threads
    int thread_count;         // Número de threads
    int shutdown;             // Flag de término
    int active_tasks;         // Tarefas em execução
} thread_pool_t;

/*
 * Protótipos
 */

thread_pool_t* thread_pool_create(int thread_count, int queue_size);
void* thread_worker(void *arg);
int thread_pool_add_task(thread_pool_t *pool, void (*function)(void *), void *arg);
void thread_pool_destroy(thread_pool_t *pool);
void thread_pool_wait_all(thread_pool_t *pool);
void print_number(void *arg);

/**
 * Função principal.
 * Demonstra o uso do pool de threads criando tarefas simples.
 * @return int Código de saída do programa
 * @author Alexandre Meslin
 * @date 2025-09-16
 * @version 1.0
 * @license MIT
 */
int main() {
    // Cria pool com 4 threads e fila de 100 tarefas
    thread_pool_t *pool = thread_pool_create(4, 100);
    
    // Adiciona tarefas
    for (int i = 0; i < 20; i++) {
        int *num = malloc(sizeof(int));
        *num = i;
        thread_pool_add_task(pool, print_number, num);
    }
    
    // Aguarda todas as tarefas concluírem
    thread_pool_wait_all(pool);
    
    // Destroi o pool
    thread_pool_destroy(pool);
    
    return 0;
}

/**
 * Função que cria um pool de threads.
 * Inicializa o pool, cria as threads e aloca a fila de tarefas.
 * @param thread_count Número de threads no pool
 * @param queue_size Tamanho máximo da fila de tarefas
 * @return thread_pool_t* Ponteiro para o pool de threads criado
 * @note A função aloca memória que deve ser liberada posteriormente.
 * @author Alexandre Meslin
 * @date 2025-09-16
 * @version 1.0
 * @license MIT
 */
thread_pool_t* thread_pool_create(int thread_count, int queue_size) {
    thread_pool_t *pool = malloc(sizeof(thread_pool_t));
    if (!pool) {
        perror("malloc");
        return NULL;
    }
    
    // Inicialização de mutex e condition variables
    pthread_mutex_init(&pool->lock, NULL);
    pthread_cond_init(&pool->cond, NULL);
    pthread_cond_init(&pool->finished, NULL);
    
    // Alocação de threads e fila
    pool->threads = malloc(sizeof(pthread_t) * thread_count);
    pool->queue = malloc(sizeof(task_t) * queue_size);
    
    pool->thread_count = thread_count;
    pool->queue_size = queue_size;
    pool->queue_count = pool->queue_front = pool->queue_rear = 0;
    pool->shutdown = pool->active_tasks = 0;
    
    // Cria as threads
    for (int i = 0; i < thread_count; i++) {
        pthread_create(&pool->threads[i], NULL, thread_worker, pool);
    }
    
    return pool;
}

/**
 * Função que realiza o trabalho de cada thread no pool.
 * Cada thread espera por tarefas na fila e as executa.
 * @param arg Ponteiro para o pool de threads
 * @return void* Retorna NULL
 * @author Alexandre Meslin
 * @date 2025-09-16
 * @version 1.0
 * @license MIT
 */
void* thread_worker(void *arg) {
    thread_pool_t *pool = (thread_pool_t*)arg;
    
    while (1) {
        pthread_mutex_lock(&pool->lock);
        
        // Espera por tarefas ou shutdown
        while (pool->queue_count == 0 && !pool->shutdown) {
            pthread_cond_wait(&pool->cond, &pool->lock);
        }
        
        if (pool->shutdown) {
            pthread_mutex_unlock(&pool->lock);
            pthread_exit(NULL);
        }
        
        // Pega tarefa da fila
        task_t task = pool->queue[pool->queue_front];
        pool->queue_front = (pool->queue_front + 1) % pool->queue_size;
        pool->queue_count--;
        pool->active_tasks++;
        
        pthread_mutex_unlock(&pool->lock);
        
        // Executa a tarefa
        task.function(task.arg);
        
        pthread_mutex_lock(&pool->lock);
        pool->active_tasks--;
        if (pool->active_tasks == 0 && pool->queue_count == 0) {
            pthread_cond_signal(&pool->finished);
        }
        pthread_mutex_unlock(&pool->lock);
    }
    
    return NULL;
}

/**
 * Função que adiciona uma tarefa ao pool de threads.
 * Coloca a tarefa na fila e sinaliza uma thread para executá-la.
 * @param pool Ponteiro para o pool de threads
 * @param function Ponteiro para a função da tarefa
 * @param arg Argumento para a função da tarefa
 * @return int 0 se a tarefa foi adicionada com sucesso, -1 se a fila está cheia
 * @author Alexandre Meslin
 * @date 2025-09-16
 * @version 1.0
 * @license MIT
 */
int thread_pool_add_task(thread_pool_t *pool, void (*function)(void *), void *arg) {
    pthread_mutex_lock(&pool->lock);
    
    if (pool->queue_count == pool->queue_size) {
        pthread_mutex_unlock(&pool->lock);
        return -1; // Fila cheia
    }
    
    // Adiciona tarefa na fila
    pool->queue[pool->queue_rear].function = function;
    pool->queue[pool->queue_rear].arg = arg;
    pool->queue_rear = (pool->queue_rear + 1) % pool->queue_size;
    pool->queue_count++;
    
    pthread_cond_signal(&pool->cond);
    pthread_mutex_unlock(&pool->lock);
    
    return 0;
}

/**
 * Função que espera todas as tarefas serem concluídas.
 * Bloqueia até que todas as tarefas na fila e em execução sejam finalizadas.
 * @param pool Ponteiro para o pool de threads
 * @author Alexandre Meslin
 * @date 2025-09-16
 * @version 1.0
 * @license MIT
 */
void thread_pool_destroy(thread_pool_t *pool) {
    pthread_mutex_lock(&pool->lock);
    pool->shutdown = 1;
    pthread_cond_broadcast(&pool->cond);
    pthread_mutex_unlock(&pool->lock);
    
    // Aguarda todas as threads terminarem
    for (int i = 0; i < pool->thread_count; i++) {
        pthread_join(pool->threads[i], NULL);
    }
    
    // Libera recursos
    free(pool->threads);
    free(pool->queue);
    pthread_mutex_destroy(&pool->lock);
    pthread_cond_destroy(&pool->cond);
    pthread_cond_destroy(&pool->finished);
    free(pool);
}

/**
 * Função que imprime um número.
 * @param arg Ponteiro para o número a ser impresso
 */
void print_number(void *arg) {
    int num = *(int*)arg;
    printf("Processando número: %d (Thread: %lu)\n", num, pthread_self());
    free(arg);
}

/**
 * Função que espera todas as tarefas serem concluídas.
 * Bloqueia até que todas as tarefas na fila e em execução sejam finalizadas.
 * @param pool Ponteiro para o pool de threads
 * @author Alexandre Meslin
 * @date 2025-09-16
 * @version 1.0
 * @license MIT
 */
void thread_pool_wait_all(thread_pool_t *pool) {
    pthread_mutex_lock(&pool->lock);

    // Espera até que todas as tarefas sejam concluídas
    while (pool->queue_count > 0 || pool->active_tasks > 0)
        pthread_cond_wait(&pool->finished, &pool->lock);

    pthread_mutex_unlock(&pool->lock);
}