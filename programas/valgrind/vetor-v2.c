#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Exemplo de alocação e cópia de string
 * Aloca memória para uma string, copia um texto para essa memória e depois libera a memória.
 * Não deve haver vazamento de memória.
 * Porém, a alocação está incorreta, faltando espaço para o terminador nulo.
 * Isso pode ser detectado pelo Valgrind como acesso fora dos limites.
 * Compilar:
 *   gcc -g -Wall -Wextra -pedantic -O0 -fno-omit-frame-pointer -fno-inline -o vetor-v2 vetor-v2.c
 * Executar com Valgrind:
 *   valgrind --leak-check=full ./vetor-v2
 * @return int
 */
int main(int argc, char *argv[]) {
    if(argc>0) printf("Programa: %s\n", argv[0]);
    char pOrigem[] = "Um texto";
    char *pDestino;
    int tamanho = strlen(pOrigem);

    pDestino = malloc(tamanho); // Incorreto: falta espaço para o '\0'
    printf("Alocou %d bytes\n", tamanho);
    printf("Tamanho da string de origem: %zu\n", sizeof pOrigem);
    strcpy(pDestino, pOrigem);

    puts(pDestino);
    free(pDestino);

    return 0;
}
