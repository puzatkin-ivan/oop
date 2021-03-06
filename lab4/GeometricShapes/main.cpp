#include "stdafx.h"
#include "CShapeController.h"

int main()
{
	try
	{
		std::vector<std::unique_ptr<IShape>> shapes;
		CShapeController controller(shapes, std::cout);
		controller.AddItem("linesegment", std::make_unique<CAddLineSegmentCommand>(shapes));
		controller.AddItem("circle", std::make_unique<CAddCircleCommand>(shapes));
		controller.AddItem("rectangle", std::make_unique<CAddRectangleCommand>(shapes));
		controller.AddItem("triangle", std::make_unique<CAddTriangleCommand>(shapes));
		controller.AddItem("info", std::make_unique<CPrintMinPerimeterCommand>(shapes, std::cout));
		controller.Run(std::cin);
	}
	catch (std::exception & e)
	{
		std::cout << e.what() << std::endl;
	}
    return 0;
}