#include "stdafx.h"
#include "crypt.h"

int Crypt(const std::string & inFileName, const std::string & outFileName, const std::function<char(char)> & fn)
{
	std::ifstream inFile(inFileName, std::ios::binary);

	if (!inFile.is_open())
	{
		std::cout << "Error: failed to open " << inFileName << " for reading" << std::endl;
		return 1;
	}

	std::ofstream outFile(outFileName, std::ios::binary);

	if (!outFile.is_open())
	{
		std::cout << "Error: failed to open " << outFileName << " for writing" << std::endl;
		return 1;
	}

	char ch;
	while (inFile.get(ch))
	{
		outFile << fn(ch);
	}
	return 0;
}

std::function<char(char)> GetCryptFunction(const uint8_t & key)
{
	return [key](char byte) {
		byte ^= key;
		auto resultByte = BitPermutation(byte);
		return resultByte;
	};
}

std::function<char(char)> GetDecryptFunction(const uint8_t & key)
{
	return [key](char ch) {
		auto byte = ch;
		auto resultByte = BitPermutationBack(byte);
		resultByte ^= key;
		return resultByte;
	};
}

uint8_t BitPermutation(char byte)
{
	auto result = 0;

	result |= (byte & 0b10000000) >> 2;
	result |= (byte & 0b01100000) >> 5;
	result |= (byte & 0b00011000) << 3;
	result |= (byte & 0b00000111) << 2;

	return result;
}

uint8_t BitPermutationBack(const uint8_t & byte)
{
	auto result = 0;

	result |= (byte & 0b11000000) >> 3;
	result |= (byte & 0b00100000) << 2;
	result |= (byte & 0b00011100) >> 2;
	result |= (byte & 0b00000011) << 5;

	return result;
}
