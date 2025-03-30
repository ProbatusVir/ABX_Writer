/* Author: Joshua Smith (ProbatusVir)
 * Date: 3/29/2025
 * This shall contain a suite of bitwise functionality.
*/

#ifndef BITWISE_H
#define BITWISE_H

#ifndef __BYTE_ORDER__
#error System endianness could not be determined.
#endif

#include <stddef.h>
/**
 * \brief A type-generic function to get the bit at a specified index of an array of bits.
 * \param data A pointer to any type of data.
 * \param n The index of the bit to examine.
 * \return Returns the value of the bit. 1 or 0.
 */
int get_bit(const void* data, size_t n);
/**
* \brief Similar to get_bit. This type-generic function gets the nibble at a specified index of an array of nibbles.
* \param data A pointer to any type of data.
* \param n The index of the nibble to examine.
* \return The value of the nibble -- (0-15).
*/
int get_nibble(const void* data, size_t n);
/**
* \brief Turns a nibble into its hex representation.
* \param n An integer from 0-15.
* \return The ASCII representation of the hexidecimal representation of the bit. ('0'-'F')
*/
char get_hex_rep(int n);
/**
* \brief Displays an array of bits.
* \param data A pointer to any type of data.
* \param start The index of the bit to start displaying.
* \param n The number of bits to display.
*/
void display_bits(const void* data, size_t start, size_t n);
/**
 * \brief Display an array of nibbles.\n TODO: Maybe add a start thing to this one just like the display_bits
 * \param data A pointer to any type of data.
 * \param n The number of bits to display.
 */
void display_hex(const void* data, size_t n);
/**
 * \brief Toggle the endianness of data
 * \param data A pointer to any type of data.
 * \param n The size of the data.
 */
void toggle_endian(void* data, size_t n);

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
