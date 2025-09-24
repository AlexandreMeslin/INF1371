#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char *pChar;
} tipoEstruturado;

/**
 * Exemplo de vazamento de memória com estrutura
 * Aloca uma estrutura que contém um ponteiro e aloca memória para esse ponteiro.
 * Depois, perde a referência para a estrutura sem liberar nenhuma das alocações.
 * Isso deve ser detectado pelo Valgrind.
 * Compilar:
 *   gcc -g -Wall -Wextra -pedantic -O0 -fno-omit-frame-pointer -fno-inline -o alocacao-v2 alocacao-v2.c
 * Executar com Valgrind:
 *   valgrind --leak-check=full ./alocacao-v2
 * @return int
 */
int main(void) {
    tipoEstruturado *pEstrutura = malloc(sizeof(tipoEstruturado));
    pEstrutura->pChar = malloc(1000);

    puts("Oi Valgrind!");

    pEstrutura = NULL;

    return 0;
}
