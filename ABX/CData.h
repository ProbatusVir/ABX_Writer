#pragma once
#include "Region.h"
class CData : public Region
{
public:
	virtual const unsigned short int HeaderSize() const override
	{

	}
	virtual const unsigned int ChunkSize() const override
	{

	}
	virtual const unsigned short int Type() const override { return ToggleEndian((SUI)0x0401); }
};

