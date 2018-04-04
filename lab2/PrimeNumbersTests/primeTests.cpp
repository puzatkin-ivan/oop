#include "stdafx.h"
#include <chrono>
#include "../PrimeNumbers/prime.h"

bool SetsAreEqual(const std::set<int> & lhs, const std::set<int> & rhs)
{
	return lhs == rhs;
}

BOOST_AUTO_TEST_SUITE(Prime_Numbers)
	BOOST_AUTO_TEST_CASE(makes_empty_prime_numbers_set_from_out_of_range_numbers)
	{
		auto sieve = GeneratePrimeNumbersSet(1);
		BOOST_CHECK(sieve.empty());

		sieve = GeneratePrimeNumbersSet(100000001);
		BOOST_CHECK(sieve.empty());
	}
	BOOST_AUTO_TEST_CASE(makes_prime_numbers_up_to_10)
	{
		std::set<int> expectedSieve = { 2,3,5,7 };
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
		auto deltaTime = std::chrono::duration_cast<std::chrono::milliseconds>(start - end).count();
		BOOST_CHECK_EQUAL(ESTIMATED_SIZE, sieve.size());
		BOOST_CHECK(deltaTime >= MAX_EXECUTION_TIME);
	}
BOOST_AUTO_TEST_SUITE_END()
