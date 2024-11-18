#pragma once

short unsigned int ToggleEndian(short unsigned int n);
unsigned int ToggleEndian(unsigned int n);

#define INDICES(n) sizeof(n) -1
#define ITERATIONS(n) sizeof(n) / 2
#define TARGET_BYTE(n, i) ((char*)&n)[i]
#define SWAP_BYTE(n, i, j)\
	TARGET_BYTE(n, i) ^= TARGET_BYTE(n, j);\
	TARGET_BYTE(n, j) ^= TARGET_BYTE(n, i);\
	TARGET_BYTE(n, i) ^= TARGET_BYTE(n, j);\

#define TOGGLE_ENDIAN(n)\
	for (int i = 0; i < ITERATIONS(n); i++)\
	{\
		SWAP_BYTE(n, i, INDICES(n) - i);\
	}

#define REP_HEX(n) (char)((n) + 48 + ((n) > 9) * 7)

#define DISPLAY_HEX(n)\
	for (int byte = 0; byte < sizeof(n); byte++)\
	{\
		std::cout << REP_HEX(TARGET_BYTE(n, byte) / 16);/*Eliminate the right and take its place.*/\
		std::cout << REP_HEX(TARGET_BYTE(n, byte) % 16) << ' ';/*Zeroes the leftmost nibble to capture the rightmost, space for console formatting*/\
	}
//ideally nullptr or an unitialized pointer would be passed in.
//This has never been tested.
#define HEX_ARRAY(n, ptrArr) {\
	ptrArr = new char[sizeof(n)*2];\
	for (int byte = 0; byte < sizeof(n); byte++)\
		ptrArr[byte * 2] = TARGET_BYTE(n, byte) / 16;/*Zeroes the leftmost nibble, replacing the rightmost*/\
		ptrArr[byte * 2 + 1] = TARGET_BYTE(n, byte) % 16;/*Gets everything less than 16 now.*/\
	}\
}

short unsigned int ToggleEndian(short unsigned int n)
{
	TOGGLE_ENDIAN(n);
	return n;
}

unsigned int ToggleEndian(unsigned int n)
{
	TOGGLE_ENDIAN(n);
	return n;
}