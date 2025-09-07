#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>

#define OPENMODE (O_RDONLY | O_NONBLOCK)
//#define OPENMODE (O_RDONLY)
#define FIFO "minhaFifo"

int main (void) {
	int fpFIFO;
	char ch;
	int status;

	if (access(FIFO, F_OK) == -1) {
		if (mkfifo (FIFO, S_IRUSR | S_IWUSR) != 0) {
			fprintf (stderr, "Erro ao criar FIFO %s\n", FIFO);
			return -1;
		}
		printf ("FIFO %s criada\n", FIFO);
	}

	puts ("Abrindo FIFO");
	if ((fpFIFO = open (FIFO, OPENMODE)) < 0) {
		fprintf (stderr, "Erro ao abrir a FIFO %s\n", FIFO);
		return -2;
	}
	
	puts("Começando a ler...");
	while((status=read(fpFIFO, &ch, sizeof ch)) >= 0) {
		putchar(ch);
		fflush(stdout);
	}
	printf("Fim da leitura com status %d\n", status);
		
	close (fpFIFO);
	return 0;
}
