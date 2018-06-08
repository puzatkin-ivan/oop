#include "stdafx.h"
#include "CShapeController.h"
#include <boost/range/algorithm/find_if.hpp>
#include <boost/algorithm/string.hpp>

CShapeController::CShapeController(std::ostream& output)
	:m_output(output)
{
	AddItem("linesegment", std::make_unique<CAddLineSegmentCommand>(m_shapes));
	AddItem("circle", std::make_unique<CAddCircleCommand>(m_shapes));
	AddItem("rectangle", std::make_unique<CAddRectangleCommand>(m_shapes));
	AddItem("triangle", std::make_unique<CAddTriangleCommand>(m_shapes));
	AddItem("info", std::make_unique<CPrintMinPerimeterCommand>(m_shapes, m_output));
}

void CShapeController::Run(std::istream& stream)
{
	std::string command;
	while (std::getline(stream, command))
	{		
		std::string name;
		std::stringstream iss(command);
		iss >> name;
		
		auto action = boost::find_if(m_actionMap, [&](const Item & item) {
			return item.shortcut == name;
		});

		if (action == boost::end(m_actionMap))
		{
			throw std::invalid_argument("Error: Unknown command");
		}
		std::stringstream input(command);
		action->command->Execute(input);

		if (!m_shapes.empty())
		{
			auto printMinPerimeter = std::make_unique<CPrintMinPerimeterCommand>(m_shapes, m_output);
			printMinPerimeter->Execute(input);

			auto printMaxArea = std::make_unique<CPrintMaxAreaCommand>(m_shapes, m_output);
			printMaxArea->Execute(input);
		}
	}
}
