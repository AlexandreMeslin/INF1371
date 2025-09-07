#include <stdio.h>
#include <unistd.h>

int main(void) {
	int fd[2];
    char textoTx[] = "uma mensagem";
    char textoRx[sizeof textoTx+1];
    int qtdRx;

	pipe(fd);
	if (fork() == 0) {
		/* filho */
//		close(fd[1]); /* fd[1] desnecessario */
		qtdRx = read(fd[0], textoRx, sizeof textoRx); /* lê do pai */
        printf("%d bytes recebidos.\n", qtdRx);
        printf("Mensagem [%s] recebida!\n", textoRx);
        write(fd[1], "outro texto", 12);
        printf("Mensagem retornada\n");
	} else { 
//		close(fd[0]); /* fd[0] desnecessario */
        printf("Transmitindo %ld bytes.\n", sizeof textoTx);
		write(fd[1], textoTx, sizeof textoTx); /* escreve para o filho */
        printf("Mensagem |%s| transmitida.\n", textoTx);
		qtdRx = read(fd[0], textoRx, sizeof textoRx); /* lê do pai */
        printf("%d bytes recebidos.\n", qtdRx);
        printf("Mensagem [%s] recebida.\n", textoRx);
	}
    return 0;
}

