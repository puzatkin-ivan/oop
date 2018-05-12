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
	void SetCenter(const CPoint& center);
	double GetRadius() const;
	void SetRadius(double radius);
protected:
	void AppendAdditionalProperties(std::ostream& stream) const override;
private:
	CPoint m_center;
	double m_radius;
};
