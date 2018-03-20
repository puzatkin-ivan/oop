#include "stdafx.h"
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

	auto number = GetNumbers(std::cin);
	ProcessVector(number);
	PrintNumbers(std::cout, number, AMOUNT_NUMBERS_POST_POINT);
	return 0;
}
