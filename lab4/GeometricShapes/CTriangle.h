#pragma once

#include "CPoint.h"
#include "CSolidShape.h"
#include <array>

class CTriangle : public CSolidShape
{
public:
	CTriangle() = delete;
	CTriangle(const CPoint& vertex1, const CPoint& vertex2, const CPoint& vertex3, 
		const std::string& outlineColor, const std::string& fillColor);
	~CTriangle() = default;

	double GetArea() const override;
	double GetPerimeter() const override;

	CPoint const& GetVertex1() const;
	CPoint const& GetVertex2() const;
	CPoint const& GetVertex3() const;

private:
	std::array<CPoint, 3> m_vertices;
};
