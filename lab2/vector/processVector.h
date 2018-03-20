#pragma once

#include <iostream>
#include <algorithm>
#include <iterator>
#include <vector>
#include <iomanip>

std::vector<double> GetNumbers(std::istream & inputFile);
void PrintNumbers(std::ostream & outputFile, const std::vector<double> & outputVector, unsigned precision);

void ProcessVector(std::vector<double> & numbers);