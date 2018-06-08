#pragma once
#include "IShape.h"

class CShape : public IShape
{
public:
	std::string GetOutlineColor() const override;
	void SetOutlineColor(const std::string & outlineColor) override;
private:
	std::string m_outlineColor;
};
