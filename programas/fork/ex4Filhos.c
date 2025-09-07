#include <unistd.h>
#include <stdio.h> 
#include <sys/types.h> 
#define TEMPO0 10000000000 
#define TEMPO1 9000000000 
#define TEMPO2 8000000000 
#define TEMPO3 7000000000 
#define TEMPO4 6000000000 
int main(void) 
{ 
	unsigned long int i,j; 
	for(i=0;i<4;i++) 
	if (!fork()) break; 
	switch (i) 
	{ 
		case 0: 
			puts("sou filho 0"); 
			for (j=0;j<TEMPO0;j++); 
			puts("filho 0 terminou"); 
			break; 
		case 1: 
			puts("sou filho 1"); 
			for(j=0;j<TEMPO1;j++); 
			puts("filho 1 terminou"); 
			break; 
		case 2: 
			puts("sou filho 2"); 
			for(j=0;i<TEMPO2;i++); 
			puts("filho 2 terminou"); 
			break; 
		case 3: 
			puts("sou filho 3"); 
			for(j=0;j<TEMPO3;j++); 
			puts("filho 3 terminou"); 
			break; 
		case 4: 
			puts ("sou pai"); 
			for (j=0;j<TEMPO4;j++); 
			puts("pai terminou"); 
	} 
	return 0;
}

