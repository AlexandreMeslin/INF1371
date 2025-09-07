#include <stdio.h>
#include <unistd.h>

int main(void) {
	int x = 1;

	pid_t pid = fork();
	if(pid == 0)
		printf("Filho (%d): x = %d\n", getpid(), ++x);
	else {
		printf("O PID do meu filho é %d\n", pid);
		printf("Pai (%d): x = %d\n", getpid(), --x);
	}
	printf("Termino do processo %d com x = %d\n", getpid(), x);
	return 0;
}
