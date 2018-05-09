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

double CRectangle::GetWidth() const
{
	return m_width;
}

double CRectangle::GetHeight() const
{
	return m_height;
}