/* Author: Joshua Smith (ProbatusVir)
 * Date: 3/29/2025
 * This shall contain a suite of bitwise functionality.
*/

#ifndef BITWISE_H
#define BITWISE_H
#include <stddef.h>

int get_bit(const void* data, size_t n);
int get_nibble(const void* data, size_t n);
char get_hex_rep(int n);
void display_bits_system(const void* data, size_t start, size_t n);
void display_bits(const void* data, size_t start, size_t n);

#define ITERATIONS(n) (sizeof(n) / 2)
#define INDICES(n) (sizeof(n) -1)
#define TARGET_BYTE(n, i) (((char*)&n)[i])								// NOLINT(*-str34-c)
#define TOGGLE_ENDIAN(n)				\
for (int i = 0; i < ITERATIONS(n); i++)	\
{										\
SWAP_BYTE(n, i, INDICES(n) - i);		\
}
#define SWAP_BYTE(n, i, j)												\
{typeof(n) SWAP_BYTE_TEMP = TARGET_BYTE(n, i);							\
TARGET_BYTE(n, i) = TARGET_BYTE(n, j);									\
TARGET_BYTE(n, j) = SWAP_BYTE_TEMP;										}



#endif //BITWISE_H
