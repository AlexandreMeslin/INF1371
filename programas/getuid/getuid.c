#include <stdio.h>
#include <unistd.h>

int main(int argc, char * argv[])
{
	FILE *arq;

	printf("(UID = %d) (EUID = %d) (GID = %d) (EGID = %d)\n",
		getuid(), geteuid(), getgid(), getegid());
	puts("Criando o arquivo \"banana.arq\".");
	arq = fopen("banana.arq", "w");

	return 0;
}
