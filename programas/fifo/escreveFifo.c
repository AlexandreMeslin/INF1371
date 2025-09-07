#include <stdio.h>

int main (void) {
	FILE *pArq;

	printf("Vou abrir a FIFO\n");
	if ((pArq = fopen("minhaFifo", "w")) == NULL) {
		puts ("Erro ao abrir a FIFO para escrita");
		return -1;
	}

	puts ("Começando a escrever...");
	fputs ("Melancia sem caroço", pArq);
	printf("Término da escrita\n");
	
	fclose (pArq);
	return 0;
}
