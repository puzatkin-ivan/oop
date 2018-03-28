#include "stdafx.h"
#include "CCar.h"
#include "CCarControl.h"

int main()
{
	CCar car;
	CCarControl carControl(car, std::cin, std::cout);
	while (!std::cin.eof())
	{
		if (!carControl.HandleCommand())
		{
			std::cout << "Unknown command" << std::endl;
		}
	}
    return 0;
}

