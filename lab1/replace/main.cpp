#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>

void ReplaceString(std::ifstream & inFile, std::ofstream & outFile, const std::string & searchStr, const std::string & replaceStr);
std::string FindAndReplace(std::string & inputStr, const std::string & searchStr, const std::string & replaceStr);

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

	ReplaceString(inputFile, outputFile, searchStr, replaceStr);

    return 0;
}


void ReplaceString(std::ifstream & inFile, std::ofstream & outFile, const std::string & searchStr, const std::string & replaceStr)
{
	std::string line;
	while (std::getline(inFile, line))
	{
		outFile << FindAndReplace(line, searchStr, replaceStr) << std::endl;
	}
}


std::string FindAndReplace(std::string & inputStr, const std::string & searchStr, const std::string & replaceStr)
{
	auto searchResult = inputStr.find(searchStr);
	while (searchResult != std::string::npos)
	{
		inputStr.replace(searchResult, searchStr.size(), replaceStr);
		searchResult = inputStr.find(searchStr, searchResult + replaceStr.size());
	}
	return inputStr;
}