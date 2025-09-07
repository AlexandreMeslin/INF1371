#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include <sys/sem.h>

int main(int argc, char *argv[])
{
	int opcao;
	char *strOpcao = ":k:s:m:d";
	char operador = ' ';
	int res,sem_id,op1;


	while((opcao=getopt(argc, argv, strOpcao)) != -1)
	{
		operador=opcao;
		op1= atoi(optarg);
	}
	switch(operador)
	{
		case 'k':
			printf("op1= %d\n",op1);
			sem_id=semget(op1, 1, IPC_CREAT | 0600);
			break;
		default:
			printf("Opcao Invalida");
			return -1;
	}
	printf("Res: %d\n",sem_id);
	for(;;);
}
