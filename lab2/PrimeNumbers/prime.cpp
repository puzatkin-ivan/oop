#include "stdafx.h"
#include "prime.h"

std::set<int> GeneratePrimeNumbersSet(int upperBound)
{
	if (upperBound < MIN_UPPER_BOUND || upperBound > MAX_UPPER_BOUND)
	{
		return std::set<int>();
	}
	std::vector<bool> sieve(upperBound + 1, true);
	for (size_t i = 2; i * i <= upperBound; ++i)
	{
		if (sieve[i])
		{
			for (size_t j = i * i; j < sieve.size(); j += i)
			{
				sieve[j] = false;
			}
		}
	}
	
	std::set<int> primeNumbers;
	for (size_t index = 2; index < sieve.size(); ++index)
	{
		if (sieve[index])
		{
			primeNumbers.insert(primeNumbers.end(), static_cast<int>(index));
		}
	}
	return primeNumbers;
}
