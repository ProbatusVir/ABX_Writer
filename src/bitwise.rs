use bytemuck::{bytes_of, bytes_of_mut, NoUninit};

pub fn get_hex_rep(n : u8) -> u8
{
	debug_assert!(n >= 0 && n <= 15);
	n as u8 + b'0' + (n > 9) as u8 * (b'A' - b'9' - 1)
}

pub fn get_bit<T : NoUninit>(data : &T, n : usize) -> bool
{

	let bytes = bytes_of(data);
	let index : usize = n / u8::BITS as usize;
	let bit : usize = n % u8::BITS as usize;
	let section = bytes[index] as usize;
	let probe : usize = 1 << bit;
	(section & probe) != 0
}

pub fn get_nibble<T : NoUninit>(data : &T, n : usize) -> u8
{
	const NIBBLE_PERMUTATIONS : u8 = 0x10;
	const NIBBLES_IN_BYTE : usize = 2;
	const BITS_IN_NIBBLE : usize = u8::BITS as usize / NIBBLES_IN_BYTE;
	let byte_buffer = bytes_of(data);
	let index = n / NIBBLES_IN_BYTE;
	let local_index = n % NIBBLES_IN_BYTE;
	let spaces_to_move = local_index * BITS_IN_NIBBLE;
	let section = (byte_buffer[index]) >> spaces_to_move;
	let result = section & (NIBBLE_PERMUTATIONS - 1);
	// Division essentially captures the more significant end of the byte, modulo captures the lesser
	// It's done this way to avoid branching.
	result / NIBBLE_PERMUTATIONS | result % NIBBLE_PERMUTATIONS
}

// I will possibly rework this to have less variables.
pub fn display_bits<T : NoUninit>(data : &T, start : usize, n : usize)
{
	let upper_bound : usize = start + n;
	#[cfg(target_endian = "little")]{
		for i in 0 .. upper_bound
		{
			let bit = if get_bit(data, i) {'1'} else {'0'};
			print!("{bit}");
		}
	}
	/* This was never tested on a big-endian system! */
	#[cfg(target_endian = "big")] {
		let mut i = upper_bound;
		for i in (0 .. upper_bound).rev()
		{
			let bit = if get_bit(data, i) {'1'} else {'0'};
			print!("{bit}");
		}
	}
}

pub fn display_hex<T : NoUninit>(data : &T, n : usize)
{
	let pairs = n / 2;
	#[cfg(target_endian = "little")] {
		// This loop is unrolled because weird little-endian ordering.
		for i in 0..pairs {
			let actual_iterator = i * 2; // I don't know what to call this variable.
			let mut nibble = get_hex_rep(get_nibble(data, actual_iterator + 1)) as char;
			print!("{nibble}");
			nibble = get_hex_rep(get_nibble(data, actual_iterator)) as char;
			print!("{nibble}");
		}
		if (n % 2 == 1)
		{
			let last_character = get_hex_rep(get_nibble(data, n)) as char;
			print!("{last_character}")
		}
	}
	// Still untested.
	#[cfg(target_endian = "big")] {
		for i in 0 .. n
		{
			let nibble = get_hex_rep(get_nibble(data, i)) as char;
			print!("{nibble}");
		}
	}
}

// This shouldn't need to exist.
pub fn toggle_endian<T : NoUninit + bytemuck::Pod>(data : &mut T)
{
	let pairs = size_of::<T>() / 2;
	let n_indices = size_of::<T>() - 1;
	let mut byte_buffer: &mut [u8] = bytes_of_mut(data);
	for i in 0 .. pairs
	{
		let j = n_indices - i;
		byte_buffer.swap(i, j);
	}
}