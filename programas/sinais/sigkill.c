#include <stdio.h>
#include <signal.h>

void funcao(int d);

int a = -1;

int main(void)
{

	if (signal(SIGKILL, funcao) == SIG_ERR)
		printf("b\n");
	else 
		printf("c\n");

	while (a)
	{
	}

	printf ("d\n");
	return 0;
}

void funcao(int e)
{
	a = 0;
	printf("f\n");
}

