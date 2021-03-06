#include "stdafx.h"

#include <iterator>
#include <iostream>
#include <fstream>
#include "prime.h"

int main(int argc, char * argv[])
{
	if (argc != 2)
	{
		std::cout << "Invalid arguments count" << std::endl;
		std::cout << "Usage: primeNumbers.exe <upperBound>" << std::endl;
		return 0;
	}

	int upperBound = atoi(argv[1]);
	if ((upperBound < MIN_UPPER_BOUND) || (upperBound > MAX_UPPER_BOUND))
	{
		std::cout << "Invalid argument" << std::endl;
		std::cout << "Upper bound in [1, 100000000]" << std::endl;
		return 0;
	}

	std::set<int> prime = GeneratePrimeNumbersSet(upperBound);
	std::cout << prime.size() << std::endl;

    return 0;
}

