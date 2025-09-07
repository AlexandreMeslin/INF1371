#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>

#define OPENMODE (O_RDONLY | O_NONBLOCK)
#define FIFO "minhaFifo"
#define EVER ;;

int main(void) {
    int fpFIFO;
    char ch;
    int status;
    fd_set readfds;

    if (access(FIFO, F_OK) == -1) {
        if (mkfifo(FIFO, S_IRUSR | S_IWUSR) != 0) {
            fprintf(stderr, "Erro ao criar FIFO %s\n", FIFO);
            return -1;
        }
        printf("FIFO %s criada\n", FIFO);
    }

    puts("Abrindo FIFO");
    if ((fpFIFO = open(FIFO, OPENMODE)) < 0) {
        fprintf(stderr, "Erro ao abrir a FIFO %s\n", FIFO);
        return -2;
    }

    puts("Começando a ler...");
    for (EVER) {
        FD_ZERO(&readfds);
        FD_SET(fpFIFO, &readfds);
        if (select(fpFIFO + 1, &readfds, NULL, NULL, NULL) < 0) {
            fprintf(stderr, "Erro ao tentar dar select\n");
            exit(1);
        }
        if (FD_ISSET(fpFIFO, &readfds)) {
            while ((status = read(fpFIFO, &ch, sizeof ch)) > 0) {
                putchar(ch);
                fflush(stdout);
            }
        }
    }

    puts("Fim da leitura");

    close(fpFIFO);
    return 0;
}
