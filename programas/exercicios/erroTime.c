#include <stdio.h>
#include <time.h>

#define ATRASO 20000000000L

int main(void)
{
	time_t tInicio, tFim;
	long i;

	printf("Contando até %ld\n", ATRASO);

	tInicio = time(NULL);
	for(i=0; i<ATRASO; i++);	/* delay */
	tFim = time(NULL);

	printf("Tempo inicial:\t%ld s\nTempo final:\t%ld s\n", tInicio, tFim);
	printf("Tempo inicial: %s\nTempo final: %s\n", ctime(&tInicio), ctime(&tFim));
	return 0;
}
