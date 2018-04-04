#pragma once
#include <set>
#include <vector>

const int MIN_UPPER_BOUND = 2;
const int MAX_UPPER_BOUND = 100000000;

std::set<int> GeneratePrimeNumbersSet(int upperBound);
std::vector<bool> InitVectorPrimes(int upperBound);
std::set<int> GeneratePrimeNumbersSetFromVector(const std::vector<bool> & sieve);