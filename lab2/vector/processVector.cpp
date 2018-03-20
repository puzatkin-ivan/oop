#include "stdafx.h"
#include "processVector.h"

std::vector<double> GetNumbers(std::istream & inputFile)
{
	return std::vector<double>(std::istream_iterator<double>(inputFile), std::istream_iterator<double>());
}

void PrintNumbers(std::ostream & outputFile, const std::vector<double> & outputVector, unsigned precision)
{
	outputFile << std::fixed << std::setprecision(precision);
	copy(outputVector.begin(), outputVector.end(), std::ostream_iterator<double>(outputFile, " "));
}

void ProcessVector(std::vector<double> & numbers)
{
	if (numbers.size() > 1)
	{
		auto minElement = *std::min_element(numbers.begin(), numbers.end());
		if (minElement != 0)
		{
			std::transform(numbers.begin(), numbers.end(), numbers.begin(),
				[minElement](double number) { return number * minElement; });
		}
	}
}
