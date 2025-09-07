#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    int fd;      /* descritor a ser duplicado  */
    int retorno; /* valor de retorno de dup  */
    int ch;

    if ((fd = open(argv[1], O_RDONLY, 0666)) == -1)     {
        perror("Error open()");
        return -1;
    }

    close(0);                    /* fecha entrada stdin */
    if ((retorno = dup(fd)) < 0) { /* duplica para stdin (menor descritor fechado) */
        perror("Error dup()");
        return -2;
    }

    while ((ch = getchar()) != EOF)
        putchar(ch);
    return 0;
}
