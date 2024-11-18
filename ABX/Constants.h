#pragma once
//The event is the upper half of any byte
enum class Event : unsigned char
{
	START_DOCUMENT = 0,
	END_DOCUMENT,
	START_TAG,	//Follows a string which is the tag name (must be STRING_INTERNED)
	END_TAG,
	TEXT,
	CDSECT,
	ENTITY_REF,
	IGNORABLE_WHITESPACE,
	PROCESSING_INSTRUCTION,
	COMMENT,
	DOCDECL,
	ATTRIBUTE = 15
};

// The data type is the lower half of any byte
// big endian
enum class Data : unsigned char
{
	NIL = 1, //No data follows
	STRING,	//16 bit Int, followed by that many bytes of UTF-8
	STRING_INTERNED,
	BYTE_HEX,
	BYTES_BASE64, //16 bit int followed by that many bytes of data
	INT,	 //32 bit int
	INT_HEX, //32 bit int
	LONG,	  //64 bit int
	LONG_HEX, //64 bit int
	FLOAT,	//32 bit single precision
	DOUBLE, //64 bit double precision
};

typedef short unsigned int SUI;
typedef unsigned int UI;



