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

int test_write_file ()
{
	int res = -1;
	int file_descriptor = open_file("test/writetest.file");
	printf("writetest.file id is %d\n", file_descriptor);

	if (file_descriptor == -1) { 
		close_file(file_descriptor); 
	}
	else {
		char *text = "there's only one Bengo Macarona.";
		res = write(file_descriptor, text, strlen(text));
		if (res == -1) { printf("Error writing text\n"); }
		else { printf ("res: %d\n", res); }
	}

	close_file(file_descriptor);
	return res;
}

int test_read_file ()
{
	void *data = read_file ("resources/test.file");
	if (data == NULL) { 
		printf("FAIL: Couldn't read test.file.");
		return -1;
	} else { 
		printf("%s\n", (char *)data);
		return 0;
	}
}



int main () 
{
	int passcount = 0;
	int failcount = 0;

	// silly_string_test();

	test_write_file();
	test_read_file();

	return 0;
}

