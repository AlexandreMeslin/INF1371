#include <stdio.h>
#include <unistd.h>

int main(void) {
	int fd[2];
    char textoTx[] = "uma mensagem";
    char textoRx[sizeof textoTx];
    int qtdRx;

	pipe(fd);
	if (fork() == 0) {
		/* filho */
        printf("Filho esperando...\n");
		close(fd[1]); /* fd[1] desnecessario */
		qtdRx = read(fd[0], textoRx, sizeof textoRx); /* lê do pai */
        printf("%d bytes recebidos pelo canal %d.\n", qtdRx, fd[0]);
        printf("Mensagem [%s] recebida!\n", textoRx);
	} else { 
		close(fd[0]); /* fd[0] desnecessario */
        printf("Transmitindo %ld bytes pelo canal %d.\n", sizeof textoTx, fd[1]);
		write(fd[1], textoTx, sizeof textoTx); /* escreve para o filho */
        printf("Mensagem |%s| transmitida.\n", textoTx);
	}
    return 0;
}

