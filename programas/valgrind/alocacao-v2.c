#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char *pChar;
} tipoEstruturado;

int main(int argc, char *argv[]) {
    tipoEstruturado *pEstrutura = malloc(sizeof(tipoEstruturado));
    pEstrutura->pChar = malloc(1000);

    puts("Oi Valgrind!");

    pEstrutura = NULL;

    return 0;
}
