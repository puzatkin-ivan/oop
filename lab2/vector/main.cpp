#include "stdafx.h"
#include <algorithm>
#include <fstream>
#include "processVector.h"

const unsigned AMOUNT_NUMBERS_POST_POINT = 3;

int main(int argc, char* argv[])
{
	if (argc == 2)
	{
		std::cout << "Error: invalid arguments count" << std::endl;
		std::cout << "Usage: vector.exe <input file>" << std::endl;
		return 1;
	}

	std::ifstream inputFile(argv[1]);
	if (!inputFile.is_open())
	{
		std::cout << "Failed to open " << argv[1] << " for reading." << std::endl;
		return 1;
	}
	auto number = GetNumbers(inputFile);
	ProcessVector(number);
	std::sort(number.begin(), number.end());
	PrintNumbers(std::cout, number, AMOUNT_NUMBERS_POST_POINT);
	return 0;
}
