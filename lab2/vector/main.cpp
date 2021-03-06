#include "stdafx.h"
#include <algorithm>
#include <fstream>
#include "processVector.h"

const unsigned AMOUNT_OF_DIGITS_AFTER_POINT = 3;

int main(int argc, char* argv[])
{
	auto number = GetNumbers(std::cin);
	ProcessVector(number);
	std::sort(number.begin(), number.end());
	PrintNumbers(std::cout, number, AMOUNT_OF_DIGITS_AFTER_POINT);
	return 0;
}
