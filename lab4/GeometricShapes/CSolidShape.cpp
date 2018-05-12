#include "stdafx.h"
#include "CSolidShape.h"

CSolidShape::CSolidShape(const std::string& type, const std::string& outllineColor, const std::string& fillColor)
	:m_type(type)
	,m_fillColor(fillColor)
	,m_outlineColor(outllineColor)
{
}

std::string CSolidShape::ToString() const
{
	std::ostringstream stream;
	stream << "Type: " << m_type << std::endl;
	stream << "Area: " << GetArea() << std::endl;
	stream << "Perimeter: " << GetPerimeter() << std::endl;
	stream << "Outline Color: " << GetOutlineColor() << std::endl;
	stream << "Fill Color: " << GetFillColor() << std::endl;
	AppendAdditionalProperties(stream);
	return stream.str();
}

std::string CSolidShape::GetOutlineColor() const
{
	return m_outlineColor;
}

void CSolidShape::SetOutlineColor(const std::string& outlineColor)
{
	m_outlineColor = outlineColor;
}

std::string CSolidShape::GetFillColor() const
{
	return m_fillColor;
}

void CSolidShape::SetFillColor(const std::string& fillColor)
{
	m_fillColor = fillColor;
}
