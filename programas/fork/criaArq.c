#include <stdio.h>
#include <stdlib.h>

#define TAMBUFFER (512/sizeof(float))

int main (void)
{
	FILE *pArq;
	float v[TAMBUFFER];
	int i, j;

	if ((pArq = fopen("dados.bin", "w")) == NULL)
	{
		puts ("erro ao abrir o arquivo");
		return -1;
	}

	for (i=0; i < 2*1024*1024/512; i++)
	{
		for (j=0; j<TAMBUFFER; j++) v[j] = rand();
		fwrite(v, sizeof(float), TAMBUFFER, pArq);
	}

	fclose (pArq);
	
	return 0;
}
