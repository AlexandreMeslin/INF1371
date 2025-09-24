#include <stdio.h>

/**
 * Exemplo simples para testar o Valgrind
 * Apenas imprime uma mensagem na tela.
 * O Valgrind não deve reportar nenhum problema.
 * Compilar:
 *   gcc -g -Wall -Wextra -pedantic -O0 -fno-omit-frame-pointer -fno-inline -o alomundo alomundo.c
 * Executar com Valgrind:
 *   valgrind --leak-check=full ./alomundo
 * @return int
 */
int main(int argc, char *argv[]) {
    puts("Oi Valgrind!");

    return 0;
}
