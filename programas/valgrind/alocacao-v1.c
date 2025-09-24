#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    char *p = malloc(1000);

    puts("Oi Valgrind!");

    return 0;
}
