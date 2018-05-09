#pragma once
#include <string>
#include "CShape.h"
#include "CPoint.h"

class CLineSegment : public CShape
{
public:
	CLineSegment() = delete;
	CLineSegment(const CPoint & startPoint, const CPoint & endPoint, const std::string & outlineColor);

	double GetArea() const override;
	double GetPerimeter() const override;

	CPoint GetStartPoint() const;
	void SetStartPoint(const CPoint & startPoint);

	CPoint GetEndPoint() const;
	void SetEndPoint(const CPoint & endPoint);

	std::string ToString() const override;
private:
	CPoint m_startPoint;
	CPoint m_endPoint;
};