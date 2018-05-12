#include "stdafx.h"
#include "CRectangle.h"

CRectangle::CRectangle(const CPoint & leftTopVertex, double height, double width, const std::string & outlineColor, const std::string & fillColor)
	:CSolidShape("Rectangle", outlineColor, fillColor)
	,m_leftTopVertex(leftTopVertex)
	,m_width(width)
	,m_height(height)
{
}

double CRectangle::GetArea() const
{
	return m_width * m_height;
}

double CRectangle::GetPerimeter() const
{
	return 2 * (m_width + m_height);
}

CPoint CRectangle::GetLeftTop() const
{
	return m_leftTopVertex;
}

void CRectangle::SetLeftTop(const CPoint& leftTop)
{
	m_leftTopVertex = leftTop;
}

double CRectangle::GetWidth() const
{
	return m_width;
}

void CRectangle::SetWidth(double width)
{
	m_width = width;
}

double CRectangle::GetHeight() const
{
	return m_height;
}

void CRectangle::SetHeight(double height)
{
	m_height = height;
}

void CRectangle::AppendAdditionalProperties(std::ostream& stream) const
{
	stream << "Left Top Vertex: " << m_leftTopVertex.x << " " << m_leftTopVertex.y << std::endl;
	stream << "Width: " << m_width << std::endl;
	stream << "Height: " << m_height << std::endl;
}