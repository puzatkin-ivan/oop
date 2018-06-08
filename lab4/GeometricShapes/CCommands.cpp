#include "stdafx.h"
#include "CCommands.h"
#include <boost/algorithm/string.hpp>

namespace
{
static const size_t COUNT_PARAMETERS_FOR_LINE_SEGMENT = 6;

static const size_t COUNT_PARAMETERS_FOR_CIRCLE = 6;

static const size_t COUNT_PARAMETERS_FOR_TRIANGLE = 9;

static const size_t COUNT_PARAMETERS_FOR_RECTANGLE = 7;
} // namespace

std::vector<std::string> CCreateShapeCommand::GetParams(std::istream& input)
{
	std::string command;
	if (!std::getline(input, command))
	{
		throw std::invalid_argument("Input file is empty.");
	}
	boost::to_lower(command);
	std::vector<std::string> params;
	boost::split(params, command, boost::is_space());
	return params;
}

CAddLineSegmentCommand::CAddLineSegmentCommand(std::vector<std::unique_ptr<IShape>>& shapes)
	: m_shapes(shapes)
{
}

void CAddLineSegmentCommand::Execute(std::istream& input)
{
	auto params = GetParams(input);
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

void CAddCircleCommand::Execute(std::istream& input)
{
	auto params = GetParams(input);
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

void CAddRectangleCommand::Execute(std::istream& input)
{
	auto params = GetParams(input);
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

CAddTriangleCommand::CAddTriangleCommand(std::vector<std::unique_ptr<IShape>>& shapes)
	: m_shapes(shapes)
{
}

void CAddTriangleCommand::Execute(std::istream& input)
{
	auto params = GetParams(input);
	if (params.size() != COUNT_PARAMETERS_FOR_TRIANGLE)
	{
		throw std::invalid_argument("Error: Invalid count argument for rectangle");
	}
	CPoint vertex1(std::stod(params[1]), std::stod(params[2]));
	CPoint vertex2(std::stod(params[3]), std::stod(params[4]));
	CPoint vertex3(std::stod(params[5]), std::stod(params[6]));
	const auto outlineColor = params[7];
	const auto fillColor = params[8];

	m_shapes.push_back(std::make_unique<CTriangle>(vertex1, vertex2, vertex3, outlineColor, fillColor));
}

CPrintInfoCommand::CPrintInfoCommand(std::vector<std::unique_ptr<IShape>>& shapes, std::ostream& output)
	:m_shapes(shapes)
	,m_output(output)
{
}

void CPrintInfoCommand::Execute(std::istream& input)
{
	(void)&input;
	if (m_shapes.empty())
	{
		m_output << "Shapes is empty." << std::endl;
		return;
	}

	m_output << "Info About Shapes:" << std::endl;
	for (auto& shape : m_shapes)
	{
		m_output << shape->ToString() << std::endl;
	}
}

CPrintMinPerimeterCommand::CPrintMinPerimeterCommand(std::vector<std::unique_ptr<IShape>>& shapes, std::ostream& output)
	: m_shapes(shapes)
	, m_output(output)
{
}

void CPrintMinPerimeterCommand::Execute(std::istream& input)
{
	(void)&input;
	if (m_shapes.empty())
	{
		m_output << "Shapes is empty." << std::endl;
		return;
	}
	auto minPerimeter = std::min_element(m_shapes.begin(), m_shapes.end(), [](const auto& lhs, const auto& rhs) {
		return lhs->GetPerimeter() < rhs->GetPerimeter();
	});
	m_output << "Minimum perimeter of the shape:" << std::endl << (*minPerimeter)->ToString() << std::endl;
}

CPrintMaxAreaCommand::CPrintMaxAreaCommand(std::vector<std::unique_ptr<IShape>>& shapes, std::ostream& output)
	: m_shapes(shapes)
	, m_output(output)
{
}

void CPrintMaxAreaCommand::Execute(std::istream& input)
{
	(void)&input;
	if (m_shapes.empty())
	{
		m_output << "Shapes is empty." << std::endl;
		return;
	}
	auto maxArea = std::max_element(m_shapes.begin(), m_shapes.end(), [](const auto& lhs, const auto& rhs) {
		return lhs->GetArea() < rhs->GetArea();
	});
	m_output << "Maximum area of the shape:" << std::endl << (*maxArea)->ToString() << std::endl;
}
