#include <stdio.h>
#include <unistd.h>
#include <string.h>

#define TRUE -1
#define FALSE 0

int main(int argc, char *argv[])
{
	int ch;
	int optA = FALSE, optB = FALSE, optC = FALSE;
	char strB[8752];

	while((ch=getopt(argc, argv, ":ab:c")) != -1)
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
			default:
				printf("Opcao errada\n");
				return -1;
		}
	}

	if(optA) printf("Opcao a\n");
	if(optB) printf("Opcao b com argumento \"%s\"\n", strB);
	if(optC) printf("Opcao c\n");

	return 0;
}
