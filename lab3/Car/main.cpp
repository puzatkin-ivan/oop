#include "stdafx.h"
#include "CCar.h"
#include "CCarController.h"

int main()
{
	CCar car;
	CCarController carControl(car, std::cin, std::cout);
	while (!std::cin.eof())
	{
		if (!carControl.HandleCommand())
		{
			std::cout << "Unknown command" << std::endl;
		}
	}
    return 0;
}

