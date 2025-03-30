#include "bitwise.h"

#include <assert.h>
#include <limits.h>
#include <stdio.h>
#define SYSTEM_BITS (sizeof(size_t) * CHAR_BIT)
#define SYSTEM_NIBS (sizeof(size_t) * 2)

char get_hex_rep(const int n)
{
	assert(n >= 0 && n <= 15);
	return n + '0' + (n > 9) * ('A' - '9' - 1);
}

int get_bit(const void* data, const size_t n)
{
	const size_t index = n / SYSTEM_BITS;
	const size_t bit = n % SYSTEM_BITS;
	const size_t section = ((const size_t*)data)[index];
	const size_t probe = (size_t)1 << bit;
	return (section & probe) && (size_t)1;
}

// A note on n: it is the index of the nibble, in terms of nibbles.
int get_nibble(const void* data, const size_t n)
{
	constexpr size_t NIBBLE_PERMUTATIONS = 0x10;
	constexpr size_t BITS_IN_NIBBLE = SYSTEM_BITS / SYSTEM_NIBS;
	const size_t index = n / SYSTEM_NIBS;
	const size_t local_index = n % SYSTEM_NIBS;
	const size_t spaces_to_move = local_index * BITS_IN_NIBBLE;
	size_t section = ((const size_t*)data)[index];
	section >>= spaces_to_move;
	const size_t result = section & (NIBBLE_PERMUTATIONS - 1);
	return result / NIBBLE_PERMUTATIONS | result % NIBBLE_PERMUTATIONS;
}

void display_bits_system(const void* data, const size_t start, const size_t n)
{
	const size_t upper_bound = start + n;
	for (size_t i = start; i < upper_bound; i++)
		printf("%d", get_bit(data, i));
}

void display_bits(const void* data, const size_t start, const size_t n)
{
	const ssize_t upper_bound = start + n;
	for (ssize_t i = upper_bound; i >= (ssize_t)0; i--)
		printf("%d", get_bit(data, i));
}

#undef SYSTEM_BITS