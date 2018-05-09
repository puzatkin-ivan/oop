#pragma once
#include "CSolidShape.h"
#include "CPoint.h"

class CRectangle : public CSolidShape
{
public:
	CRectangle(const CPoint & leftTopVertex, double height, double width, const std::string & outlineColor, const std::string & fillColor);
	~CRectangle() = default;

	double GetArea() const override;
	double GetPerimeter() const override;

	CPoint GetLeftTop() const;
	double GetWidth() const;
	double GetHeight() const;
private:
	CPoint m_leftTopVertex;
	double m_height;
	double m_width;
};
