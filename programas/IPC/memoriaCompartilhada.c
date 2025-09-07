#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main (int argc, char *argv[]) {
	int *p, id, status, pid;
	int (*f)();

	f = main;
	*((int *)f) = 0;
	
	if ((p = (int *)malloc (sizeof(int))) == NULL)
	{
		puts ("Erro de alocaćão de memória");
		exit (-1);
	}

	*p = 8752;

	if ((id = fork()) < 0)
	{
		puts ("Erro na criação do novo processo");
		exit (-2);
	}
	else if (id == 0)
	{
		*p += 5;
		printf ("Processo filho = %d\t(%ld)\n", *p, (long)p);
	}
	else
	{
		pid = wait (&status);
		*p += 10;
		printf ("Processo pai = %d\t(%ld)\n", *p, (long)p);
	}
	return 0;
}
