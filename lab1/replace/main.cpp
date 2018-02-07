#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>

void ReplaceString(std::ifstream & inFile, std::ofstream & outFile, const std::string & searchStr, const std::string & replaceStr);
std::string PasteString(const std::string & currentStr, const std::string & replaceStr, size_t initPositton, size_t sizeSearchStr);

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
	
	std::ifstream inputFile(inputFileName);
	std::ofstream outputFile(outputFileName);
	
	if (!inputFile.is_open())
	{
		std::cout << "Error: failed to open" << inputFileName << "for reading" << std::endl;
		return 1;
	}

	if (!outputFile.is_open())
	{

		std::cout << "Error: failed to open" << inputFileName << "for writing" << std::endl;
		return 1;
	}
	
	const std::string seacrhStr = argv[3];
	const std::string replaceStr = argv[4];

	if (seacrhStr.empty())
	{
		std::cout << "Error: <searchString> is empty" << std::endl;
		return 1;
	}

	ReplaceString(inputFile, outputFile, seacrhStr, replaceStr);

    return 0;
}


void ReplaceString(std::ifstream & inFile, std::ofstream & outFile, const std::string & searchStr, const std::string & replaceStr)
{
	std::string line;
	while (std::getline(inFile, line))
	{
		auto searchResult = line.find(searchStr);
		while (searchResult != std::string::npos)
		{
			line = PasteString(line, replaceStr, searchResult, searchStr.size());
			searchResult = line.find(searchStr, searchResult + replaceStr.size());
		}
		outFile << line << std::endl;
	}
}

std::string PasteString(const std::string & currentStr, const std::string & replaceStr, size_t initPositton, size_t sizeSearchStr)
{
	std::string newLine;
	for (size_t i = 0; i < initPositton; ++i)
	{
		newLine.push_back(currentStr[i]);
	}

	newLine.append(replaceStr);

	const auto initinalPos = initPositton + sizeSearchStr;
	for (size_t i = initinalPos; i < currentStr.size(); ++i)
	{
		newLine.push_back(currentStr[i]);
	}

	return newLine;
}
