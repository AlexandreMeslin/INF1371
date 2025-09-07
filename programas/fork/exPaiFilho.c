#include <unistd.h>
#include <stdio.h> 
#include <sys/types.h> 
int main (void) 
{ 
	int id,i; 
	id = fork (); 
	if (id) 
	{
			/* pai */ 
			printf ("Sou pai de %d\n", id); 
			for (i=1;i;i++); 
			puts ("O pai terminou"); 
	} 
	else 
	{ 
			/* filho */ 
			puts ("Sou filho"); 
			for (i=1;i;i++); 
			puts ("O filho terminou"); 
	} 
	return 0;
}

