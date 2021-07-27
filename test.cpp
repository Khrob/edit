#include "edit.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>

void silly_string_test()
{
	const char string[128] = "Hola, mundo! And how are you this afternoon?";
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

int test_write_file ()
{
	int res = -1;
	int file_descriptor = open_file((char *)"test/writetest.file");
	if (file_descriptor != -1) { 
		const char *text = "there's only one Bengo Macarona.";
		res = write(file_descriptor, text, strlen(text));
		close_file(file_descriptor);
		if (res == -1) { printf("Error writing text\n"); }
		else { res = 0; }
	}
	return res == -1 ? 0 : 1;
}

int test_read_file ()
{
	void *data = read_file ((char *)"resources/test.file");
	if (data == NULL) { 
		printf("FAIL: Couldn't read test.file.");
		return 0;
	} else { 
		// printf("%s\n", (char *)data);
		return 1;
	}
}


void red_text (const char *str) 
{
	printf ("\033[0;31m");
	printf ("%s", str);
	printf ("\033[0m"); 
}

int main () 
{
	int passcount = 0;
	int failcount = 0;

	// silly_string_test();

	if (test_write_file()) { passcount++; } else { red_text("Failed test_write_file\n"); failcount++; }
	if (test_read_file())  { passcount++; } else { red_text("Failed test_read_file\n"); failcount++; }

	printf ("Passed %d tests\n", passcount);

	if (failcount > 0) {
		char s[32];
		sprintf(s, "Failed %d tests.\n", failcount);
		red_text(s);
	}

	return 0;
}

