#pragma once
#include "Region.h"
class FileHeader : public Region
{
public:
	virtual const unsigned int ChunkSize() const override {}
	virtual const short unsigned int HeaderSize() const override {}
	virtual const unsigned short int Type() const override { return ToggleEndian((SUI)0x0300); }
};

