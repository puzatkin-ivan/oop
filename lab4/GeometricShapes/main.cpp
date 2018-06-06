#include "stdafx.h"
#include "CShapeController.h"

void DoReadShape();

int main()
{
	try
	{
		DoReadShape();
	}
	catch (std::exception & e)
	{
		std::cout << e.what() << std::endl;
	}
    return 0;
}

void DoReadShape()
{
	CShapeController controller;
	controller.Run(std::cin);
	std::string command;
	while (std::getline(std::cin, command))
	{
	}
}
