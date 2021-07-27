#include <stdint.h>

typedef int8_t  	int8;
typedef int16_t 	int16;
typedef int32_t 	int32;
typedef int64_t 	int64;
typedef uint8_t  	uint8;
typedef uint16_t 	uint16;
typedef uint32_t 	uint32;
typedef uint64_t 	uint64;

void* 	read_file (const char* file_path);
int 	write_binary_file (const char *file_path, void *data, uint16_t size);
int 	open_file (const char* file_path);
void 	close_file (int file_descriptor);

#ifdef PLATFORM_MACOS 
	#include "platform_macos.h"
#endif
