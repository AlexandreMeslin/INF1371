#include <stdio.h>
#include <stdlib.h>

/**
 * Exemplo simples de alocação de memória
 * Aloca 1000 bytes e não libera a memória.
 * Isso deve ser detectado pelo Valgrind.
 * 
 * Compilar:
 *   gcc -g -Wall -Wextra -pedantic -O0 -fno-omit-frame-pointer -fno-inline -o alocacao-v1 alocacao-v1.c
 * 
 * Executar com Valgrind:
 *   valgrind --leak-check=full ./alocacao-v1
 * @return int
 */
int main(void) {
    char *p = malloc(1000);

    printf("Oi Valgrind! (%p)\n", p);

    return 0;
}