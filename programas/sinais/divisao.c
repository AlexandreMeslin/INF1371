#include <stdio.h>
#include <signal.h>
#include <stdlib.h>

#define EVER ;;

void handler(int sinal);

int a, b;

int main (void)
{
	signal(SIGFPE, handler);

	printf ("Entre com 2 numeros reais: ");
	scanf ("%d%d", &a, &b);
	printf ("%d / %d = %d\n", a, b, a/b);

	return 0;
}

void handler(int sinal)
{
	printf ("Divisão por zero (%d/%d)\n", a, b);
	b = 1;
}
