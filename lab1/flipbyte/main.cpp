#include "stdafx.h"
#include <iostream>
#include <string>
#include <cctype>

uint8_t FlipByte(uint8_t bytes);

int main(int argc, char* argv[])
{
	if (argc != 2)
	{
		std::cout << "Error: invalid arguments count" << std::endl;
		std::cout << "Usage: flipbyte.exe <input digit>" << std::endl;
		return 1;
	}

	const char* inputString = argv[1];
	 
	char *lastCharPtr;
	int inputDigit = std::strtol(inputString, &lastCharPtr, 10);

	if ((inputDigit < 0 || inputDigit > 255) || *lastCharPtr == *inputString)
	{
		std::cout << "Error: invalid digit" << std::endl;
		std::cout << "Usage: 0 .. 255" << std::endl;
		return 1;
	}

	auto bytes = static_cast<uint8_t>(inputDigit);
	int reverseBytes = FlipByte(bytes);
	std::cout << reverseBytes << std::endl;

    return 0;
}

uint8_t FlipByte(uint8_t bytes)
{
	bytes = (bytes << 4) | (bytes >> 4);
	bytes = ((bytes & 0b00110011) << 2) | ((bytes >> 2) & 0b00110011);
	bytes = ((bytes & 0b01010101) << 1) | ((bytes >> 1) & 0b01010101);
	return bytes;
}
