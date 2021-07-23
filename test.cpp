#include "edit.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>

void silly_string_test()
{
	char string[128] = "Hola, mundo! And how are you this afternoon?";
	int len = strlen(string);
	int sleeptime = 1000000 / 55;

	for (int i=0; i<=len; i++) {
		printf("\r");
		for (int j=0; j<i; j++) printf("%c", string[j]);
		fflush(NULL);
		usleep(sleeptime);
	}

	printf("\n%d\n", len);
}

int main () 
{
	silly_string_test();
	return 0;
}

