#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>

void ProcessStrings(std::ifstream & inFile, std::ofstream & outFile, const std::string & searchStr, const std::string & replaceStr);
std::string Replace(std::string & inputStr, const std::string & searchStr, const std::string & replaceStr);

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
	
	const std::string searchStr = argv[3];
	const std::string replaceStr = argv[4];

	if (searchStr.empty())
	{
		std::cout << "Error: <searchString> is empty" << std::endl;
		return 1;
	}

	ProcessStrings(inputFile, outputFile, searchStr, replaceStr);

    return 0;
}


void ProcessStrings(std::ifstream & inFile, std::ofstream & outFile, const std::string & searchStr, const std::string & replaceStr)
{
	std::string line;
	while (std::getline(inFile, line))
	{
		outFile << Replace(line, searchStr, replaceStr) << std::endl;
	}
}


std::string Replace(std::string & inputStr, const std::string & searchStr, const std::string & replaceStr)
{
	auto searchResult = inputStr.find(searchStr);
	const auto lengthSearchStr = searchStr.size();
	std::string lineWithReplaceStr;
	size_t currPos = 0;
	
	while (searchResult != std::string::npos)
	{
		lineWithReplaceStr.append(inputStr, currPos, searchResult);
		lineWithReplaceStr.append(replaceStr);
		currPos = searchResult + searchStr.size();
		searchResult = inputStr.find(searchStr, currPos);
	}

	lineWithReplaceStr.append(inputStr, currPos);

	return lineWithReplaceStr;
}