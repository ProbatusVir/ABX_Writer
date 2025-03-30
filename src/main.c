/*	Author: Joshua Smith (ProbatusVir)
 *	Date: 3/29/2025
 *	This file shall contain the main function which shall take a standard XML file as an argument,
 *		and write a file - possibly to a specified file or directory - which contains the
 *		information in ABX format.
*/
#include <stdlib.h>
#include <stdio.h>

#include "bitwise.h"

int main(const int argc, const char** argv)
{
	char file_read_buffer[1024];
	puts(argv[1]);
	FILE* file = fopen(argv[1], "r");
	if (!file)
	{
		printf("An error occurred in opening the file!");
		return errno;
	}
	fread(file_read_buffer, sizeof(file_read_buffer[0]), sizeof(file_read_buffer), file);
	printf("%s", file_read_buffer);

	return EXIT_SUCCESS;
}
