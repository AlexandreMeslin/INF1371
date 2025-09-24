#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Exemplo de alocação e cópia de string
 * Aloca memória para uma string, copia um texto para essa memória e depois libera a memória.
 * Não deve haver vazamento de memória.
 * Compilar:
 *   gcc -g -Wall -Wextra -pedantic -O0 -fno-omit-frame-pointer -fno-inline -o vetor-v1 vetor-v1.c
 * Executar com Valgrind:
 *   valgrind --leak-check=full ./vetor-v1
 * @return int
 */
int main(void) {
    char pOrigem[] = "Um texto";
    char *pDestino;

    pDestino = malloc(sizeof pOrigem);
    strcpy(pDestino, pOrigem);

    puts(pDestino);
    free(pDestino);

    return 0;
}
