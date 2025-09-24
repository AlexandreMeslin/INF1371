#include <stdio.h>

/**
 * Exemplo de uso de variável não inicializada
 * Declara uma variável local sem inicializá-la e tenta usá-la.
 * Isso deve ser detectado pelo Valgrind.
 * Compilar:
 *   gcc -g -Wall -Wextra -pedantic -O0 -fno-omit-frame-pointer -fno-inline -o naoInicializado naoInicializado.c
 * Executar com Valgrind:
 *   valgrind --track-origins=yes ./naoInicializado
 * @return int
 */
int main(int argc, char *argv[]) {
    int a;

    if(a) puts("Verdadeiro");
    else puts("Falso");

    return 0;
}
