#include <stdio.h>
#include <unistd.h>
#define EVER ;;

int main(void)
{
	printf("Este é o processo de número %d\n", getpid());
	printf("O processo %d é o pai deste processo\n", getppid());

	for(EVER);

	return 0;
}
