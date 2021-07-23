/*

	edit.h

	Single-header library for using .edit project files

*/

#include "platform_macos.h"


typedef struct 
{
	char	 	magic[2];			// Should always be 0xED17
	int 		version;			// File Format version 
} 
Edit_File_Header;


typedef struct 
{
	char* 		title;
	float 		ratio_width; 		// For the ratio, not in pixels.
	float 		ratio_height;		// This is a float so you can to 1:2.39
} 
Edit_File_Project;


typedef struct 
{	
	char*		title;
	float		ratio_width;
	float		ratio_height;
} Edit_Project;


Edit_File_Project* load_project (char *file_path)
{
	return NULL;
}

int write_project ()
{
	return -1;
}
