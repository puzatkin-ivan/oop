#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <array>
#include <iomanip>

const size_t MAX_SIZE_MATRIX = 3;
using Matrix3x3 = std::array<std::array<double, MAX_SIZE_MATRIX>, MAX_SIZE_MATRIX>;

bool ReadMatrix(const std::string & inputFileName, Matrix3x3 & matrix);
void PrintMatrix(const Matrix3x3 & matrix);
bool CalculateInverseMatrix(const Matrix3x3 & matrix, Matrix3x3 & inverseMatrix);
double GetMatrixDeterminant3x3(const Matrix3x3 & matrix);
double GetMatrixDeterminant2x2(const Matrix3x3 & matrix, size_t strikeoutRow, size_t strikeoutColumn);


int main(int argc, char* argv[])
{
	if (argc != 2)
	{
		std::cout << "Error: invalid arguments count" << std::endl;
		std::cout << "Usage: invert.exe <matrix file>" << std::endl;
		return 1;
	}
	int statusExecute = 0;
	
	const std::string inputFileName = argv[1];
	Matrix3x3 matrix;

	if (!ReadMatrix(inputFileName, matrix))
	{
		return 1;
	}
	
	Matrix3x3 inverseMatrix;
	if (!CalculateInverseMatrix(matrix, inverseMatrix))
	{
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
		std::array<double, MAX_SIZE_MATRIX> row;
		for (size_t j = 0; j < MAX_SIZE_MATRIX; ++j)
		{
			if (inputFile.eof())
			{
				return false;
			}
			double element;
			inputFile >> element;
			row[j] = element;
		}
		matrix[i] = row;
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

double GetMatrixDeterminant2x2(const Matrix3x3 & matrix, size_t strikeoutRow, size_t strikeoutColumn)
{
	const auto amountRow = matrix.size();
	std::array<double, 4> minor;

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
	auto detarmenant = (minor[0] * minor[3]) - (minor[1] * minor[2]);

	return detarmenant;
}

double GetMatrixDeterminant3x3(const Matrix3x3 & matrix)
{
	double determinant = 0;
	size_t column = 0;

	for (size_t index = 0; index < matrix.size(); ++index)
	{
		auto sign = std::pow(-1, index);
		determinant += sign * matrix[0][index] * GetMatrixDeterminant2x2(matrix, 0, index);
	}

	return determinant;
}

bool CalculateInverseMatrix(const Matrix3x3 & matrix, Matrix3x3 & inverseMatrix)
{
	auto matrixDeterminant = GetMatrixDeterminant3x3(matrix);

	if (matrixDeterminant == 0)
	{
		std::cout << "Determinant = 0" << std::endl;
		return false;
	}

	for (size_t i = 0; i < MAX_SIZE_MATRIX; ++i)
	{
		std::array<double, MAX_SIZE_MATRIX> row;
		for (size_t j = 0; j < MAX_SIZE_MATRIX; ++j)
		{
			auto sign = std::pow(-1, i + j);
			double matrixElement = sign * (1 / matrixDeterminant) * GetMatrixDeterminant2x2(matrix, j, i);

			if (matrixElement == -0)
			{
				matrixElement = 0;
			}

			row[j] = matrixElement;
		}

		inverseMatrix[i] = row;
	}

	return true;
}
