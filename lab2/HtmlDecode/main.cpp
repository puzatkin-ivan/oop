#include "stdafx.h"
#include "HtmlDecode.h"

int main(int argc, char* argv[])
{
	std::string inputString;
	while (std::getline(std::cin, inputString))
	{
		std::cout << HtmlDecode(inputString) << std::endl;
	}

    return 0;
}

