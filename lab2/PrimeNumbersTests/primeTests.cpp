#include "stdafx.h"
#include "../PrimeNumbers/prime.h"
#include <chrono>
#include <iostream>

bool SetsAreEqual(const std::set<int>& lhs, const std::set<int>& rhs)
{
	return lhs == rhs;
}

BOOST_AUTO_TEST_SUITE(Prime_Numbers)
	BOOST_AUTO_TEST_CASE(make_vector_initialization_for_upper_bound_2)
	{
		std::vector<bool> expected = { 0, 0, 1 };
		auto result = InitVectorPrimes(2);
		BOOST_CHECK(expected == result);
	}
	BOOST_AUTO_TEST_CASE(make_set_prime_numbers_for_upper_bound_2)
	{
		std::set<int> expectedSet = { 2 };
		auto primeNumbersVector = InitVectorPrimes(2);
		auto result = GeneratePrimeNumbersSetFromVector(primeNumbersVector);
		BOOST_CHECK(SetsAreEqual(expectedSet, result));
	}
	BOOST_AUTO_TEST_CASE(makes_empty_prime_numbers_set_from_out_of_range_numbers)
	{
		BOOST_CHECK_THROW(GeneratePrimeNumbersSet(MIN_UPPER_BOUND - 1), std::exception);
	}
	BOOST_AUTO_TEST_CASE(make_empty_prime_numbers_set_from_upper_numbers)
	{
		BOOST_CHECK_THROW(GeneratePrimeNumbersSet(MAX_UPPER_BOUND + 1), std::exception);
	}
	BOOST_AUTO_TEST_CASE(makes_prime_numbers_up_to_10)
	{
		std::set<int> expectedSieve = { 2, 3, 5, 7 };
		auto sieve = GeneratePrimeNumbersSet(10);

		BOOST_CHECK(SetsAreEqual(expectedSieve, sieve));
	}
	BOOST_AUTO_TEST_CASE(makes_prime_numbers_up_to_max_upper_bound)
	{
		const size_t ESTIMATED_SIZE = 5761455;
		const int MAX_EXECUTION_TIME = 12000;
		std::chrono::time_point<std::chrono::system_clock> start = std::chrono::system_clock::now();
		auto sieve = GeneratePrimeNumbersSet(MAX_UPPER_BOUND);
		std::chrono::time_point<std::chrono::system_clock> end = std::chrono::system_clock::now();
		auto deltaTime = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
		std::cout << deltaTime << std::endl;
		BOOST_CHECK_EQUAL(ESTIMATED_SIZE, sieve.size());
		BOOST_CHECK(deltaTime <= MAX_EXECUTION_TIME);
	}
BOOST_AUTO_TEST_SUITE_END()
