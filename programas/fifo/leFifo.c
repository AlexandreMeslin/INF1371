#include <stdio.h>

int main (void)
{
	FILE *pArq;
	int ch;

	printf("Vou abrir a FIFO para leitura\n");
	if ((pArq = fopen("minhaFifo", "r")) == NULL) 	{
		puts ("Erro ao abrir a FIFO para leitura");
		return -1;
	}

	puts ("Começando a ler...");
	while ((ch = fgetc(pArq)) != EOF) {
		putchar (ch);
		putchar ('_');
	}
	printf("Término da leitura\n");

	fclose (pArq);
	return 0;
}
