#include "stdafx.h"
#include "CCircle.h"

CCircle::CCircle(const CPoint & center, double radius, const std::string & outlineColor, const std::string & fillColor)
	:CSolidShape("Circle", outlineColor, fillColor)
	,m_center(center)
	,m_radius(radius)
{
}

double CCircle::GetArea() const
{
	return M_PI * m_radius * m_radius;
}

double CCircle::GetPerimeter() const
{
	return 2 * M_PI * m_radius;
}

CPoint CCircle::GetCenter() const
{
	return m_center;
}

void CCircle::SetCenter(const CPoint& center)
{
	m_center = center;
}

double CCircle::GetRadius() const
{
	return m_radius;
}

void CCircle::SetRadius(double radius)
{
	m_radius = radius;
}

void CCircle::AppendAdditionalProperties(std::ostream& stream) const
{
	stream << "Center: " << m_center.x << " " << m_center.y << std::endl;
	stream << "Radius: " << m_radius << std::endl;
}