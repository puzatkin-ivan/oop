#pragma once
#include "CSolidShape.h"
#include "CPoint.h"

class CRectangle : public CSolidShape
{
public:
	CRectangle(const CPoint & leftTopVertex, double height, double width, const std::string & outlineColor, const std::string & fillColor);

	double GetArea() const override;
	double GetPerimeter() const override;

	CPoint GetLeftTop() const;
	void SetLeftTop(const CPoint& leftTop);

	double GetWidth() const;
	void SetWidth(double width);

	double GetHeight() const; 
	void SetHeight(double height);
protected:
	void AppendAdditionalProperties(std::ostream& stream) const override;
private:
	CPoint m_leftTopVertex;
	double m_height;
	double m_width;
};
