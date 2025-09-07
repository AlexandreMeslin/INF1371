#include <stdio.h>
#include <unistd.h>

int main (void) {
	puts ("vou parar...");
	pause();
	puts ("Continuei!");
	return 0;
}
