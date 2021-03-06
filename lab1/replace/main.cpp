#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>

int CopyFileWithReplace(const std::string & inFile, const std::string & outFile, const std::string & searchStr, const std::string & replaceStr);
void CopyStringWithReplace(std::istream & inFile, std::ostream & outFile, const std::string & searchStr, const std::string & replaceStr);
std::string Replace(const std::string & inputStr, const std::string & searchStr, const std::string & replaceStr);

int main(int argc, char* argv[])
{
	if (argc != 5)
	{
		std::cout << "Error: invalid arguments count" << std::endl;
		std::cout << "Usage: replace.exe <input file> <output file> <search string> <replace string>" << std::endl;
		return 1;
	}

	const std::string inputFileName = argv[1];
	const std::string outputFileName = argv[2];
	const std::string searchStr = argv[3];
	const std::string replaceStr = argv[4];

	return CopyFileWithReplace(inputFileName, outputFileName, searchStr, replaceStr);
}

int CopyFileWithReplace(const std::string & inputFileName, const std::string & outputFileName, const std::string & searchStr, const std::string & replaceStr)
{
	std::ifstream inputFile(inputFileName);
	std::ofstream outputFile(outputFileName);

	if (!inputFile.is_open())
	{
		std::cout << "Error: failed to open " << inputFileName << " for reading" << std::endl;
		return 1;
	}

	if (!outputFile.is_open())
	{
		std::cout << "Error: failed to open " << outputFileName << " for writing" << std::endl;
		return 1;
	}

	CopyStringWithReplace(inputFile, outputFile, searchStr, replaceStr);
	return 0;
}

void CopyStringWithReplace(std::istream & inFile, std::ostream & outFile, const std::string & searchStr, const std::string & replaceStr)
{
	std::string line;
	while (std::getline(inFile, line))
	{
		outFile << Replace(line, searchStr, replaceStr) << std::endl;
	}
}

std::string Replace(const std::string & inputStr, const std::string & searchStr, const std::string & replacementStr)
{
	if (searchStr.empty())
	{
		return inputStr;
	}
	std::string resultStr;
	size_t initSearchPos = 0;
	
	while (initSearchPos != std::string::npos)
	{
		auto foundPos = inputStr.find(searchStr, initSearchPos);
		resultStr.append(inputStr, initSearchPos, foundPos - initSearchPos);

		if (foundPos != std::string::npos)
		{
			resultStr.append(replacementStr);
			foundPos += searchStr.size();
		}
		initSearchPos = foundPos;
	}
	
	return resultStr;
}
