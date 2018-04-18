#include "stdafx.h"
#include "prime.h"

std::set<int> GeneratePrimeNumbersSet(int upperBound)
{
	if (upperBound < MIN_UPPER_BOUND || upperBound > MAX_UPPER_BOUND)
	{
		throw std::exception("Invalid upperBound");
	}
	auto sieve = InitVectorPrimes(upperBound);

	return GeneratePrimeNumbersSetFromVector(sieve);
}

std::vector<bool> InitVectorPrimes(int upperBound)
{
	std::vector<bool> sieve(upperBound + 1, true);
	sieve[0] = false;
	sieve[1] = false;
	for (size_t i = 2; i * i <= sieve.size(); ++i)
	{
		if (sieve[i])
		{
			for (size_t j = i * i; j < sieve.size(); j += i)
			{
				sieve[j] = false;
			}
		}
	}
	return sieve;
}

std::set<int> GeneratePrimeNumbersSetFromVector(const std::vector<bool>& sieve)
{
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
