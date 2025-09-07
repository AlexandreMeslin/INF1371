#include <stdio.h>
#include <unistd.h>

int main(void)
{
	int x, y;
	char ch;

	for(;;)
	{
		for(ch='A'; ch<='Z'; ch++)
			for(x=1; x<10; x++)
			{
				for(y=1; y<10; y++)
				{
					printf("\033[%d;%dH%c", x, y, ch);
					fflush(stdout);
					sleep(1);
				}
			}
	}
}
