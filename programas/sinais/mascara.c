#include <stdio.h>
#include <signal.h>
#include <unistd.h>

#define TEMPO 10
#define EVER ;;
#define TRUE -1
#define FALSE 0

void handler(int sinal);

int fimTempo;
struct hostent {
	char	*h_name;    /* name of the host */
	char **h_aliases;   /* list of aliases (nicknames) */
	int h_addrtype;     /* address type */
	int h_length;       /* length in bytes of the address */
	char **h_addr_list; /* list of address (network order) */
};

int main (void) {
	sigset_t sinal;
	sigemptyset(&sinal);	// aluno incluir teste!
	sigaddset(&sinal, SIGINT); 	// aluno incluir teste!
	sigprocmask(SIG_BLOCK, &sinal, NULL);	// aluno incluir teste!
	signal(SIGALRM, handler);	// aluno incluir teste!
	signal(SIGINT, handler);	// aluno incluir teste!

	fimTempo = FALSE;
	printf ("%d segundos sem Ctrl-C\n", TEMPO);
	alarm(TEMPO);
	for(EVER) 	{
		if (fimTempo) 		{
			puts("Fim do tempo sem Ctrl-C");
			sigprocmask(SIG_UNBLOCK, &sinal, NULL);	// aluno incluir teste!
			break;
		}
	}
	for(EVER);
	
	return 0;
}

void handler(int sinalNo) {
	switch (sinalNo) 	{
		case SIGALRM:
			fimTempo = TRUE;
			break;
		case SIGINT:
			puts("Ctrl-C recebido");
			break;
	}
}
