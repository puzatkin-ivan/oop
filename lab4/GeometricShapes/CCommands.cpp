#include "stdafx.h"
#include "CCommands.h"

namespace
{
static const size_t COUNT_PARAMETERS_FOR_LINE_SEGMENT = 6;

static const size_t COUNT_PARAMETERS_FOR_CIRCLE = 6;

static const size_t COUNT_PARAMETERS_FOR_TRIANGLE = 9;

static const size_t COUNT_PARAMETERS_FOR_RECTANGLE = 7;
}

CAddLineSegmentCommand::CAddLineSegmentCommand(std::vector<std::unique_ptr<IShape>>& shapes)
	: m_shapes(shapes)
{
}

void CAddLineSegmentCommand::Execute(const std::vector<std::string>& params)
{
	if (params.size() != COUNT_PARAMETERS_FOR_LINE_SEGMENT)
	{
		throw std::invalid_argument("Error: Invalid count argument for linesegment");
	}
	CPoint startPoint(std::stod(params[1]), std::stod(params[2]));
	CPoint endPoint(std::stod(params[3]), std::stod(params[4]));
	const auto outlineColor = params[4];

	m_shapes.push_back(std::make_unique<CLineSegment>(startPoint, endPoint, outlineColor));
}

CAddCircleCommand::CAddCircleCommand(std::vector<std::unique_ptr<IShape>>& shapes)
	: m_shapes(shapes)
{
}

void CAddCircleCommand::Execute(const std::vector<std::string>& params)
{
	if (params.size() != COUNT_PARAMETERS_FOR_CIRCLE)
	{
		throw std::invalid_argument("Error: Invalid count argument for circle");
	}
	const CPoint center(std::stod(params[1]), std::stod(params[2]));
	const auto radius = std::stod(params[3]);
	const auto outlineColor = params[4];
	const auto fillColor = params[5];

	m_shapes.push_back(std::make_unique<CCircle>(center, radius, outlineColor, fillColor));
}

CAddRectangleCommand::CAddRectangleCommand(std::vector<std::unique_ptr<IShape>>& shapes)
	: m_shapes(shapes)
{
}

void CAddRectangleCommand::Execute(const std::vector<std::string>& params)
{
	if (params.size() != COUNT_PARAMETERS_FOR_TRIANGLE)
	{
		throw std::invalid_argument("Error: Invalid count argument for triangle");
	}
	CPoint vertex1(std::stod(params[1]), std::stod(params[2]));
	CPoint vertex2(std::stod(params[3]), std::stod(params[4]));
	CPoint vertex3(std::stod(params[5]), std::stod(params[6]));
	const auto outlineColor = params[7];
	const auto fillColor = params[8];

	m_shapes.push_back(std::make_unique<CTriangle>(vertex1, vertex2, vertex3, outlineColor, fillColor));
}

CAddTriangleCommand::CAddTriangleCommand(std::vector<std::unique_ptr<IShape>>& shapes)
	: m_shapes(shapes)
{
}

void CAddTriangleCommand::Execute(const std::vector<std::string>& params)
{
	if (params.size() != COUNT_PARAMETERS_FOR_RECTANGLE)
	{
		throw std::invalid_argument("Error: Invalid count argument for rectangle");
	}
	CPoint leftTopVertex(std::stod(params[1]), std::stod(params[2]));
	const auto height = std::stod(params[3]);
	const auto width = std::stod(params[4]);
	const auto outlineColor = params[5];
	const auto fillColor = params[6];

	m_shapes.push_back(std::make_unique<CRectangle>(leftTopVertex, height, width, outlineColor, fillColor));
}

CPrintInfoCommand::CPrintInfoCommand(std::vector<std::unique_ptr<IShape>>& shapes)
	: m_shapes(shapes)
{
}

void CPrintInfoCommand::Execute(const std::vector<std::string>& params)
{
	(void)&params;
	if (m_shapes.empty())
	{
		std::cout << "Shapes is empty." << std::endl;
	}

	std::cout << "Info About Shapes:" << std::endl;
	for (auto& shape : m_shapes)
	{
		std::cout << shape->ToString() << std::endl;
	}
}

CPrintMinPerimeterCommand::CPrintMinPerimeterCommand(std::vector<std::unique_ptr<IShape>>& shapes)
	: m_shapes(shapes)
{
}

void CPrintMinPerimeterCommand::Execute(const std::vector<std::string>& params)
{
	(void)&params;
	if (!m_shapes.empty())
	{
		auto minPerimeter = std::min_element(m_shapes.begin(), m_shapes.end(), [](const auto& lhs, const auto& rhs) {
			return lhs->GetPerimeter() < rhs->GetPerimeter();
		});
		std::cout << "Min Perimeter: " << (*minPerimeter)->ToString() << std::endl;
	}
}

CPrintMaxAreaCommand::CPrintMaxAreaCommand(std::vector<std::unique_ptr<IShape>>& shapes)
	: m_shapes(shapes)
{
}

void CPrintMaxAreaCommand::Execute(const std::vector<std::string>& params)
{
	(void)&params;
	if (!m_shapes.empty())
	{
		auto maxArea = std::max_element(m_shapes.begin(), m_shapes.end(), [](const auto& lhs, const auto& rhs) {
			return lhs->GetArea() < rhs->GetArea();
		});
		std::cout << "Max Area: " << (*maxArea)->ToString() << std::endl;
	}
}
