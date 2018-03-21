#include "stdafx.h"
#include "HtmlDecode.h"

int main(int argc, char* argv[])
{
	if (argc != 2)
	{
		std::cout << "Error: invalid arguments count" << std::endl;
		std::cout << "Usage: vector.exe <input file>" << std::endl;
		return 1;
	}
	std::ifstream inputFile(argv[1]);
	if (!inputFile.is_open())
	{
		std::cout << "Failed to open " << argv[1] << " for reading." << std::endl;
		return 1;
	}

	std::string inputString;
	while (std::getline(inputFile, inputString))
	{
		std::cout << HtmlDecode(inputString) << std::endl;
	}

    return 0;
}

