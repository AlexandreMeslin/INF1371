#include <stdio.h>

int main(void)
{
	printf ("Tamanho de short inteiro: %d\n", sizeof (short int));
	printf ("Tamanho de inteiro: %d\n", sizeof (int));
	printf ("Tamanho de long inteiro: %d\n", sizeof (long int));

	printf ("Tamanho de float: %d\n", sizeof (float));
	printf ("Tamanho de double: %d\n", sizeof (double));

	printf ("Tamanho de long double: %d\n", sizeof (long double));

	return 0;
}
