#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>

int main(int argc, char *argv[])
{
	int opcao;
	char *strOpcao = ":a:s:m:d:";
	char operador = ' ';
	int op1, op2, res;
	struct option opcoesLongas[] =
	{
		{"soma",	1, NULL, 'a'},
		{"adiciona",	1, NULL, 'a'},
		{"subtrai",	1, NULL, 's'},
		{"multiplica",	1, NULL, 'm'},
		{"divide",	1, NULL, 'd'},
		{NULL,		0, NULL, 0}
	};

	while((opcao=getopt_long(argc, argv, strOpcao, opcoesLongas, NULL)) != -1)
	{
		operador = opcao;
		op1 = atoi(optarg);
	}

	switch(operador)
	{
		case 'a':
			res = op1 + atoi(argv[3]);
			break;
		case 's':
			res = op1 - atoi(argv[3]);
			break;
		case 'm':
			res = op1 * atoi(argv[3]);
			break;
		case 'd':
			res = op1 / atoi(argv[3]);
			break;
		default:
			puts ("Operacao invalida");
	}
	printf("%d\n", res);
}
