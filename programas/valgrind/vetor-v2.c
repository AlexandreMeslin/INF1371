#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    char pOrigem[] = "Um texto";
    char *pDestino;

    pDestino = malloc(strlen(pOrigem));
    strcpy(pDestino, pOrigem);

    puts(pDestino);
    free(pDestino);

    return 0;
}
