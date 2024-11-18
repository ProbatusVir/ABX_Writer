// ConsoleApplication2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

#include "bitops.h"
#include "Constants.h"

#include "Region.h"
#include "CData.h"
#include "EndElement.h"
#include "EndNamespace.h"
#include "FileHeader.h"
#include "ResourceMap.h"
#include "StartNamespace.h"
#include "StringPool.h"


//
// HEADER: 
//	file_type: Short uint -> always "03 00"
//	header_size: short uint -> should always be 8, written "08 00"
//	file_size: uint
// 

int main()
{
	short unsigned int file_type = ToggleEndian((SUI)0x0300);
	DISPLAY_HEX(file_type);
	
}
