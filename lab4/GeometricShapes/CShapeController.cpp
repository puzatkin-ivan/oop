#include "stdafx.h"
#include "CShapeController.h"
#include <boost/range/algorithm/find_if.hpp>
#include <boost/algorithm/string.hpp>

CShapeController::CShapeController()
{
	AddItem("line segment", std::make_unique<CAddLineSegmentCommand>(m_shapes));
	AddItem("cicrle", std::make_unique<CAddCircleCommand>(m_shapes));
	AddItem("rectangle", std::make_unique<CAddRectangleCommand>(m_shapes));
	AddItem("triangle", std::make_unique<CAddTriangleCommand>(m_shapes));
	AddItem("info", std::make_unique<CPrintInfoCommand>(m_shapes));
	AddItem("min perimeter", std::make_unique<CPrintMinPerimeterCommand>(m_shapes));
	AddItem("max area", std::make_unique<CPrintMaxAreaCommand>(m_shapes));
}

void CShapeController::Run(std::istream& stream)
{
	std::string command;
	while (std::getline(stream, command))
	{
		boost::to_lower(command);
		std::vector<std::string> params;
		boost::split(params, command, boost::is_space());

		auto action = boost::find_if(m_actionMap, [&](const Item & item) {
			return item.shortcut == command;
		});

		if (action == boost::end(m_actionMap))
		{
			throw std::invalid_argument("Error: Unknown command");
		}
		action->command->Execute(params);

		auto minPerimeter = boost::find_if(m_actionMap, [&](const Item & item) {
			return item.shortcut == "min perimeter";
		});
		minPerimeter->command->Execute(params);

		auto maxArea = boost::find_if(m_actionMap, [&](const Item & item) {
			return item.shortcut == "max area";
		});
		maxArea->command->Execute(params);
	}
}
