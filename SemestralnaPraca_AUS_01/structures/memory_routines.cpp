#include "memory_routines.h"

namespace structures {
	byte & MemoryRoutines::byteSet(byte & B)
	{
		B |= MAX_BYTE;
		return B;
	}
	byte & MemoryRoutines::byteReset(byte & B)
	{
		B ^= B;
		return B;
	}
	byte & MemoryRoutines::byteXOR(byte & B)
	{
		B ^= MAX_BYTE;
		return B;
	}
	byte & MemoryRoutines::byteSHL(byte & B)
	{
		B = B << 1;
		return B;
	}
	byte & MemoryRoutines::byteSHR(byte & B)
	{
		B = B >> 1;
		return B;
	}
	bool MemoryRoutines::byteNthBitGet(byte & B, int n)
	{
		return (B >> n) & 1;
	}

	byte & MemoryRoutines::byteNthBitTo0(byte & B, int n)
	{
		B &= (~(1 << n));
		return B;
	}

	byte & MemoryRoutines::byteNthBitTo1(byte & B, int n)
	{
		B |= (1 << n);
		return B;
	}

	byte & MemoryRoutines::byteNthBitToggle(byte & B, int n)
	{
		B ^= (1 << n);
		return B;
	}

	MemoryRoutines::MemoryRoutines()
	{
	}

}
