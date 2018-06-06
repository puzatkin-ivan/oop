#pragma once
#include "IShape.h"

class CShape : virtual public IShape
{
public:
	CShape() = default;
	virtual ~CShape() = default;

	std::string GetOutlineColor() const override;
	virtual void SetOutlineColor(const std::string & outlineColor) override;
private:
	std::string m_outlineColor;
};
