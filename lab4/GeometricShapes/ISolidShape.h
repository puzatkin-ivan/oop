#pragma once

#include "IShape.h"

class ISolidShape : virtual public IShape
{
public:
	ISolidShape() = default;
	virtual ~ISolidShape() = default;

	virtual std::string GetFillColor() const = 0;
	virtual void SetFillColor(const std::string & fillColor) = 0;
private:
};