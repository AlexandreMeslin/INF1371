/*
Esse programa cria 2 threads.
a) a 1a thread apenas mostra o mundo girando
b) a 2a thread apenas se bloqueia
Use esse programa para verificar se uma thread bloqueia a outra
*/
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

#define EVER ;;

void *giraMundo(void *vargp);
void *bloqueio(void *vargp);

int main(void) {
    pthread_t tid0, tid1;
    int erro;

    fprintf(stderr, "Vou criar a thread para girar o mundo\n");
    if((erro = pthread_create(&tid0, NULL, giraMundo, NULL)) != 0) {
        fprintf(stderr, "Erro #%d ao criar a thread para girar o mundo.\n", erro);
        exit(erro);
    }

    fprintf(stderr, "Vou criar a thread que bloqueia\n");
    if((erro = pthread_create(&tid1, NULL, bloqueio, NULL)) != 0) {
        fprintf(stderr, "Erro #%d ao criar a thread que bloqueia.\n", erro);
        exit(erro);
    }

    for(EVER) {}

    return 0;
}

void *bloqueio(void *vargp) {
    int valor;
    for(EVER) {
        printf("Entre com um valor: ");
        scanf("%d", &valor);
        printf("O valor lido foi %d\n", valor);
    }
}

void *giraMundo(void *vargp) {
    int posicao =0;
    char elementos[] = {'|', '/', '-', '\\'};

    printf("Girando o mundo\n");
    for(EVER) {
        sleep(1);
        printf("\b%c", elementos[posicao]);
        fflush(stdout);
        posicao = (posicao + 1) % sizeof elementos;
    }
}