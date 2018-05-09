#include "stdafx.h"
#include "CTriangle.h"

CTriangle::CTriangle(const CPoint& vertex1, const CPoint& vertex2, const CPoint& vertex3, const std::string& outlineColor, const std::string& fillColor)
	:CSolidShape("Triangle", outlineColor, fillColor)
	,m_vertices({ vertex1, vertex2, vertex3 })
{
}

double CTriangle::GetArea() const
{
	auto p = GetPerimeter() / 2;
	auto a = std::hypot(m_vertices[0].x - m_vertices[1].x, m_vertices[0].y - m_vertices[1].y);
	auto b = std::hypot(m_vertices[1].x - m_vertices[2].x, m_vertices[1].y - m_vertices[2].y);
	auto c = std::hypot(m_vertices[0].x - m_vertices[2].x, m_vertices[0].y - m_vertices[2].y);
	return std::sqrt(p * (p - a) * (p - b) * (p - c));
}

double CTriangle::GetPerimeter() const
{
	auto a = std::hypot(m_vertices[0].x - m_vertices[1].x, m_vertices[0].y - m_vertices[1].y);
	auto b = std::hypot(m_vertices[1].x - m_vertices[2].x, m_vertices[1].y - m_vertices[2].y);
	auto c = std::hypot(m_vertices[0].x - m_vertices[2].x, m_vertices[0].y - m_vertices[2].y);
	return a + b + c;
}

CPoint const& CTriangle::GetVertex1() const
{
	return m_vertices[0];
}

CPoint const& CTriangle::GetVertex2() const
{
	return m_vertices[1];
}

CPoint const& CTriangle::GetVertex3() const
{
	return m_vertices[2];
}