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

	friend std::istream& operator >> (std::istream & in, CPoint & point);
private:
};

std::istream& operator >> (std::istream &strm, CPoint & point);