#include "stdafx.h"
#include "CShapeController.h"

int main()
{
	try
	{
		CShapeController controller(std::cout);
		controller.Run(std::cin);
	}
	catch (std::exception & e)
	{
		std::cout << e.what() << std::endl;
	}
    return 0;
}