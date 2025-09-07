/* alarm.c - demonstrate the SIGALRM signal and alarm system call */

#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

void wakeup(int);    /* executed when alarm received. */
void cleanup(int);   /* Executed upon an abort. */

int counter = 0;     /* Global so wakeup() and main() can both see it. */

int main(void)
{
	/* Illustrate catching interactive abort signals. */
	signal(SIGINT, cleanup);     /* Normally Delete key */
	signal(SIGQUIT,cleanup);     /* Normally ^\ */
   /* Quietly count to ourselves but every 5 sec or so output
	the counter. */
	wakeup(0);
	for(;;)
		counter++;
	
	return 0;
}

void wakeup(int signum) 
{
	/* print the current value of counter */
	system("date");
	printf("counter is currently %d.\n ",counter);
	printf("\n");
	/* Set signal to this function. */
	signal(SIGALRM, wakeup);
	/* Set alarm clock for 5 seconds. */
	alarm(5);
}

void cleanup(int signum)
{
	printf("Exiting after abort received.\n\n");
	exit(1);
}
