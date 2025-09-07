#include <stdio.h>
#include <signal.h>
#include <unistd.h>

int main(void)
{
	if (signal(SIGHUP, SIG_IGN) == SIG_ERR)
		printf("b\n");
	else 
		printf("c\n");

	if(execl("./loopEterno", "loopEterno", (char *)0) == -1)
		puts("Erro ao chamar loopEterno");	

	printf ("d\n");
	return 0;
}

