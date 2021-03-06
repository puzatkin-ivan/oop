#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <array>
#include <iomanip>

const double EPS = 1E-12;
const size_t MAX_SIZE_MATRIX = 3;
using Matrix3x3 = std::array<std::array<double, MAX_SIZE_MATRIX>, MAX_SIZE_MATRIX>;

bool ReadMatrix(const std::string & inputFileName, Matrix3x3 & matrix);
void PrintMatrix(const Matrix3x3 & matrix);
bool CalculateInverseMatrix(const Matrix3x3 & matrix, Matrix3x3 & inverseMatrix);
double GetMatrixDeterminant3x3(const Matrix3x3 & matrix);
double GetMinor2x2(const Matrix3x3 & matrix, size_t strikeoutRow, size_t strikeoutColumn);

int main(int argc, char* argv[])
{
	if (argc != 2)
	{
		std::cout << "Error: invalid arguments count" << std::endl;
		std::cout << "Usage: invert.exe <matrix file>" << std::endl;
		return 1;
	}
	
	const std::string inputFileName = argv[1];
	Matrix3x3 matrix;

	if (!ReadMatrix(inputFileName, matrix))
	{
		return 1;
	}
	
	Matrix3x3 inverseMatrix;
	if (!CalculateInverseMatrix(matrix, inverseMatrix))
	{
		std::cout << "Determinant = 0" << std::endl;
		return 1;
	}

	PrintMatrix(inverseMatrix);

	return 0;
}

bool ReadMatrix(const std::string & inputFileName, Matrix3x3 & matrix)
{
	std::ifstream inputFile(inputFileName);

	if (!inputFile.is_open())
	{
		std::cout << "Error: failed to open " << " for reading" << std::endl;
		return false;
	}

	for (size_t i = 0; i < MAX_SIZE_MATRIX; ++i)
	{
		auto& row = matrix[i];
		for (size_t j = 0; j < MAX_SIZE_MATRIX; ++j)
		{
			if (inputFile.eof())
			{
				return false;
			}
			auto& element = row[j];
			inputFile >> element;
		}
	}
	return true;
}

void PrintMatrix(const Matrix3x3 & matrix)
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

double GetMinor2x2(const Matrix3x3 & matrix, size_t strikeoutRow, size_t strikeoutColumn)
{
	const auto amountRow = matrix.size();
	const size_t AMONUT_ELEMENTS_MINOR = 4;
	std::array<double, AMONUT_ELEMENTS_MINOR> minor;

	size_t index = 0;
	for (size_t row = 0; row < amountRow; ++row)
	{
		if (row != strikeoutRow)
		{
			for (size_t column = 0; column < matrix[row].size(); ++column)
			{
				if (column != strikeoutColumn)
				{
					minor[index] = matrix[row][column];
					++index;
				}
			}
		}
	}	
	auto determinant = (minor[0] * minor[3]) - (minor[1] * minor[2]);

	return determinant;
}

double GetMatrixDeterminant3x3(const Matrix3x3 & matrix)
{
	short sign = 1;

	double determinant = 0;
	for (size_t index = 0; index < matrix.size(); ++index)
	{
		determinant += sign * matrix[0][index] * GetMinor2x2(matrix, 0, index);
		sign *= -1;
	}

	return determinant;
}

bool CalculateInverseMatrix(const Matrix3x3 & matrix, Matrix3x3 & inverseMatrix)
{
	auto matrixDeterminant = GetMatrixDeterminant3x3(matrix);

	if (abs(matrixDeterminant) < EPS)
	{
		return false;
	}

	short sign = 1;
	for (size_t i = 0; i < MAX_SIZE_MATRIX; ++i)
	{
		auto& row = inverseMatrix[i];
		
		for (size_t j = 0; j < MAX_SIZE_MATRIX; ++j)
		{
			double matrixElement = sign * GetMinor2x2(matrix, j, i) / matrixDeterminant;

			if (matrixElement == -0)
			{
				matrixElement = 0;
			}

			row[j] = matrixElement;
			sign *= -1;
		}
	}

	return true;
}
