#include "stdafx.h"
#include "CLineSegment.h"

CLineSegment::CLineSegment(const CPoint & startPoint, const CPoint & endPoint, const std::string & outlineColor)
	:m_startPoint(startPoint)
	,m_endPoint(endPoint)
{
}

double CLineSegment::GetArea() const
{
	return 0.0;
}

double CLineSegment::GetPerimeter() const
{
	return std::hypot(m_endPoint.x - m_startPoint.x,
		m_endPoint.y - m_startPoint.y);
}

CPoint CLineSegment::GetStartPoint() const
{
	return m_startPoint;
}

void CLineSegment::SetStartPoint(const CPoint & startPoint)
{
	m_startPoint = startPoint;
}

CPoint CLineSegment::GetEndPoint() const
{
	return m_endPoint;
}

void CLineSegment::SetEndPoint(const CPoint & endPoint)
{
	m_endPoint = endPoint;
}

std::string CLineSegment::ToString() const
{
	std::stringstream result;
	
	result << "Type: LineSegment" << std::endl
		<< "Area: " << GetArea() << std::endl
		<< "Perimeter: " << GetPerimeter() << std::endl
		<< "StartPoint: " << m_startPoint.x << " " << m_startPoint.y << std::endl
		<< "EndPoint: " << m_endPoint.x << " " << m_endPoint.y << std::endl;
	return result.str();
}
