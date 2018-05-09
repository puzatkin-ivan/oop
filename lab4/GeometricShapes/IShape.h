#pragma once
#include <string>
#include <sstream>
#include <fstream>

class IShape
{
public:
	IShape() = default;
	virtual ~IShape() = default;

	virtual double GetArea() const = 0;
	virtual double GetPerimeter() const = 0;

	virtual std::string GetOutlineColor() const = 0;
	virtual void SetOutlineColor(const std::string & outlineColor) = 0;

	virtual std::string ToString() const = 0;
private:
};
