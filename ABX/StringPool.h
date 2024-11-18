#pragma once
#include "Region.h"
class StringPool : public Region
{
public:
	virtual const unsigned short int HeaderSize() const override
	{

	}
	virtual const unsigned int ChunkSize() const override
	{

	}
	virtual const unsigned short int Type() const override { return ToggleEndian((SUI)0x0100); }

private:
	//
	char* WriteString(const char* _string)
	{
		// I'm not sure exactly why this is the case, but the string format is
		// 2 identical bytes representing the string length (excluding \0)
		// Followed by the string and null terminator. The second byte seems redundant
		const unsigned char length = strlen(_string);
		const unsigned char str_size = length + 1;

		char* new_string = new char[length + sizeof(length) * 2];
		new_string[0] = new_string[1] = length;

		memcpy_s(new_string + 2, str_size, _string, str_size);
	}


	char** strings = nullptr;

};

