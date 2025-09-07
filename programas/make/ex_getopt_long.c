#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <getopt.h>

#define TRUE -1
#define FALSE 0

int main(int argc, char *argv[])
{
	int ch;
	int optA = FALSE, optB = FALSE, optC = FALSE;
	int optHelp = FALSE, optVerbose = FALSE, optOpcao1 = FALSE;
	char strB[8752], strOpcao1[2578];

	char *opcoesCurtas = ":ab:ch";
	struct option opcoesLongas[] = 
	{
		{"help",	0, NULL, 'h'},
		{"verbose",	0, NULL, 2},
		{"opcao1",	1, NULL, 3},
		{NULL,		0, NULL, 0}
	};

	while((ch=getopt_long(argc, argv, opcoesCurtas, opcoesLongas, NULL)) != -1)
	{
		switch(ch)
		{
			case 'a': 
				optA = TRUE;
				break;
			case 'b':
				optB = TRUE;
				if(strlen(optarg) < 8752) strcpy(strB, optarg);
				break;
			case 'c':
				optC = TRUE;
				break;
			case 'h':
				optHelp = TRUE;
				break;
			case 2:
				optVerbose = TRUE;
				break;
			case 3:
				optOpcao1 = TRUE;
				strcpy(strOpcao1, optarg);
				break;
			default:
				printf("Opcao errada\n");
				return -1;
		}
	}
	
	if(optHelp)
	{
		puts("Uso: ex_opt_long [-ach] [-b <argumento>] [--help] [--verbose] [--opcao1]");
		return 1;
	}
	if(optA) printf("Opcao a\n");
	if(optB) printf("Opcao b com argumento \"%s\"\n", strB);
	if(optC) printf("Opcao c\n");
	if(optVerbose) puts("Estou no modo verboragico");
	if(optOpcao1) printf("Opcao1 com argumento \"%s\"\n", strOpcao1);

	return 0;
}
