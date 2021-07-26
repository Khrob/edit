#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h> 
#include <errno.h>


// Returns the complete contents of the given file, or NULL on any error.
void* read_file (char* file_path)
{
	// NOTE (khrob): We're not using memory allocators yet, so 
	// this returns memory that you'll need to free yourself.

	void * file_data;
	struct stat s;
	int file_descriptor;
	int r = 0;

	file_descriptor = open(file_path, O_RDONLY); 

	if (file_descriptor == -1) { printf ("ERROR Loading file: %s\n", file_path); }

	r = fstat(file_descriptor, &s);

	if (r == -1) { printf("ERROR Getting file size: %d\n", errno); }
	else { 
		printf("File is %lld bytes big\n", s.st_size); 

		file_data = malloc(s.st_size);

		r = read(file_descriptor, file_data, s.st_size);

		if (r == -1) { 
			printf("ERROR Reading file data: %d\n", errno); 
			free(file_data);
		}
	}

	close(file_descriptor);

	return (r == -1) ? NULL : file_data;
}


// Returns the file id, or -1 if there's an error.
int open_file (char* file_path) 
{
	int file_descriptor = 0;

	file_descriptor = open(file_path, O_CREAT|O_RDWR|O_TRUNC, S_IRWXU|S_IRGRP|S_IROTH);

	if (file_descriptor == -1) {
		printf("ERROR: Couldn't open or create file %s: %d\n", file_path, errno);
	} else {
		printf ("Opened file %d\n", file_descriptor);	
	}

	return file_descriptor;
}

void close_file (int file_descriptor)
{
	close (file_descriptor);
}

