#pragma once

#include "ISolidShape.h"
#include "CShape.h"

class CSolidShape : public ISolidShape
{
public:
	CSolidShape(const std::string & type, const std::string & outllineColor, const std::string & fillColor);
	virtual ~CSolidShape() = default;

	std::string GetOutlineColor() const override;
	void SetOutlineColor(const std::string & outlineColor) override;

	std::string GetFillColor() const override;
	void SetFillColor(const std::string & fillColor) override;

	std::string ToString() const override;
private:
	std::string m_type;
	std::string m_fillColor;
	std::string m_outlineColor;
};