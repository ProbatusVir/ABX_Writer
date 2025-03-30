/*	Author: Joshua Smith (ProbatusVir)
 *	Date: 3/29/2025
 *	This file shall contain the main function which shall take a standard XML file as an argument,
 *		and write a file - possibly to a specified file or directory - which contains the
 *		information in ABX format.
*/
#include <stdlib.h>
#include <stdio.h>

#include "bitwise.h"

int main(void)
{
	// TODO: write actual testing functionality for things...
	constexpr size_t n = 0x1234567890ABCDEF;
	TOGGLE_ENDIAN(n);
	for (int i = sizeof(n) * 2 - 1; i >= 0; i--)
	{
		const int nibble = get_nibble(&n, i);
		printf("%c", get_hex_rep(nibble));
	}

	return EXIT_SUCCESS;
}
