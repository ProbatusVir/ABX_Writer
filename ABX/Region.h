#pragma once
#include "Constants.h"	// These imports don't belong here, but it saves
#include "bitops.h"		// having to type it out each time something derives
class Region
{
public:
	virtual const unsigned short int HeaderSize() const abstract;
	virtual const unsigned int ChunkSize() const abstract;
	virtual const unsigned short int Type() const abstract;
	virtual const size_t Serialize(char* _buffer) const abstract;
};

