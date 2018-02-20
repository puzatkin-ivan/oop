#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>


bool ReadMatrix(std::ifstream & inputFile, std::vector<std::vector<double>> & matrix);
void PrintMatrix(const std::vector<std::vector<double>> & matrix);
double GetMatrixDeterminant2x2(std::vector<std::vector<double>> matrix, size_t strikeoutRow, size_t strikeoutColumn);
double GetMatrixDeterminant3x3(const std::vector<std::vector<double>> & matrix);
std::vector<std::vector<double>> GetInverseMatrix(const std::vector<std::vector<double>> & matrix);

namespace
{

	static const unsigned MAX_SIZE_MATRIX = 3;

}

int main(int argc, char* argv[])
{
	if (argc != 2)
	{
		std::cout << "Error: invalid arguments count" << std::endl;
		std::cout << "Usage: ivert.exe <matrix file>" << std::endl;
		return 1;
	}

	std::ifstream inputFile(argv[1]);

	if (!inputFile.is_open())
	{
		std::cout << "Error: failed to open" << argv[1] << "for reading" << std::endl;
		return 1;
	}
	std::vector<std::vector<double>> matrix;
	if (!ReadMatrix(inputFile, matrix))
	{
		std::cout << "Error: martix reading" << std::endl;
		return 1;
	}
	std::vector<std::vector<double>> inverseMatrix = GetInverseMatrix(matrix);

	if (inverseMatrix.empty())
	{
		std::cout << "Determinant = 0" << std::endl;
		return 1;
	}

	PrintMatrix(inverseMatrix);

	return 0;
}

bool ReadMatrix(std::ifstream & inputFile, std::vector<std::vector<double>> & matrix)
{
	for (size_t i = 0; i < MAX_SIZE_MATRIX; ++i)
	{
		std::vector<double> row;
		for (size_t j = 0; j < MAX_SIZE_MATRIX; ++j)
		{
			if (!inputFile.eof())
			{
				double element;
				inputFile >> element;
				row.push_back(element);
			}
			else
			{
				return false;
			}
		}
		matrix.push_back(row);
	}
	return true;
}

void PrintMatrix(const std::vector<std::vector<double>> & matrix)
{
	for (size_t i = 0; i < matrix.size(); ++i)
	{
		for (size_t j = 0; j < matrix[i].size(); ++j)
		{
			std::cout << std::setprecision(3) << matrix[i][j] << " ";
		}
		std::cout << std::endl;
	}
}

double GetMatrixDeterminant2x2(std::vector<std::vector<double>> matrix, size_t strikeoutRow, size_t strikeoutColumn)
{
	const auto amountRow = matrix.size();
	std::vector<double> minor;

	for (size_t row = 0; row < amountRow; ++row)
	{
		if (row != strikeoutRow)
		{
			for (size_t column = 0; column < matrix[row].size(); ++column)
			{
				if (column != strikeoutColumn)
				{
					minor.push_back(matrix[row][column]);
				}
			}
		}
	}

	auto detarmenant = (minor[0] * minor[3]) - (minor[1] * minor[2]);

	return detarmenant;
}

double GetMatrixDeterminant3x3(const std::vector<std::vector<double>> & matrix)
{
	double determinant = 0;
	size_t column = 0;

	for (size_t index = 0; index < matrix.size(); ++index)
	{
		auto coefficent = std::pow(-1, index);
		determinant += coefficent * matrix[0][index] * GetMatrixDeterminant2x2(matrix, 0, index);
	}
	return determinant;
}

std::vector<std::vector<double>> GetInverseMatrix(const std::vector<std::vector<double>> & matrix)
{
	auto matrixDeterminant = GetMatrixDeterminant3x3(matrix);
	std::vector<std::vector<double>> inverseMatrix;

	if (matrixDeterminant != 0)
	{
		auto determinant = 1 / matrixDeterminant;
		for (size_t i = 0; i < MAX_SIZE_MATRIX; ++i)
		{
			std::vector<double> row;

			for (size_t j = 0; j < MAX_SIZE_MATRIX; ++j)
			{
				auto coefficent = std::pow(-1, i + j);
				double matrixElement = coefficent * determinant * GetMatrixDeterminant2x2(matrix, j, i);
				row.push_back(matrixElement);
			}

			inverseMatrix.push_back(row);
		}
		return inverseMatrix;
	}
	return inverseMatrix;
}
