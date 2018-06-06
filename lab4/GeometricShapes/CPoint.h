#pragma once
#include <fstream>
#include <iostream>

class CPoint
{
public:
	CPoint() = default;
	CPoint(double x, double y);
	~CPoint() = default;

	double x;
	double y;
private:
};
