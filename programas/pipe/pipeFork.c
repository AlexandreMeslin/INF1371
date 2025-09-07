#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
	int fd[2], pid1, pid2;  
	char *my_program1[] = {"/bin/ls", "-l", NULL};		// directory listing
	char *my_program2[] = {"/usr/bin/wc", NULL};		// line, word and character count

	//system("ps -eF | grep meslin | cut -b60-95 | more");
	
	pipe(fd);
	if ((pid1=fork())==0) {	// filho 1
		close(1);			// close the stdout
		dup(fd[1]);			// duplicate fd[1] to position 1 - stdout
		close(fd[0]); 		// nao precisa mais dos descritores criados
		close(fd[1]); 
		execv(my_program1[0],my_program1);	// the output of the program redirected to fd[1]
	}
	if ((pid2=fork())==0) {	//filho 2
		close(0);			// close the stdin
		dup(fd[0]);			// duplicate the fd[0] to position 0
		close(fd[0]);		// tambem nao precisa mais dos antigos descritores
		close(fd[1]);
		execv(my_program2[0],my_program2);	// entrada redirecionada de fd[0]
	}

	close(fd[0]);
	close(fd[1]);
	waitpid(pid1, NULL, 0);	// espera um filho terminar
	waitpid(pid2, NULL, 0);	// espera ooutro filho terminar
	return 0;
}
