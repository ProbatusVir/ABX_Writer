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

void display_bits(const void* data, const size_t start, const size_t n)
{
	const ssize_t upper_bound = start + n;
	#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
	for (size_t i = start; i < upper_bound; i++)
		printf("%d", get_bit(data, i));
	#else
	for (ssize_t i = upper_bound; i >= (ssize_t)0; i--)
		printf("%d", get_bit(data, i));
	#endif
}

void display_hex(const void* data, size_t n)
{
	#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
	const size_t pairs = n / 2;
	for (int i = 0; i <= pairs; i += 2)
	{
		int nibble = get_nibble(data, i + 1);
		printf("%c", get_hex_rep(nibble));
		nibble = get_nibble(data, i);
		printf("%c", get_hex_rep(nibble));
	}
	if (n % 2)
		printf("%c", get_hex_rep(get_nibble(data, n - 1)));

	#else
	//I have no way of testing this right now.
	for (int i = 0; i < n; i++)
	{
		const int nibble = get_nibble(&n, i);
		printf("%c", get_hex_rep(nibble));
	}
	#endif
}

void toggle_endian(void* data, const size_t n)
{
	const size_t pairs = n / (size_t)2;
	const size_t n_indices = n - 1;
	char* byte_array = (char*)data;
	for (size_t i = 0; i < pairs; i++)
	{
		const size_t j = n_indices - i; // I wonder if having two counter would be more efficient somehow.
		const char tmp = byte_array[i];
		byte_array[i] = byte_array[j];
		byte_array[j] = tmp;
	}
}

#undef SYSTEM_BITS
