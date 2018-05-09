#pragma once
#include "CPoint.h"
#include "CSolidShape.h"

class CCircle final : public CSolidShape
{
public:
	CCircle() = delete;
	CCircle(const CPoint& center, double radius, const std::string& outlineColor, const std::string& fillColor);
	~CCircle() = default;

	double GetPerimeter() const;
	double GetArea() const;

	CPoint GetCenter() const;
	double GetRadius() const;

private:
	CPoint m_center;
	double m_radius;
};
