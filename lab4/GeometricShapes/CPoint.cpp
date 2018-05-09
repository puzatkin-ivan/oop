#include "stdafx.h"
#include "CPoint.h"

CPoint::CPoint(double x, double y)
	:x(x)
	,y(y)
{
}

std::istream& operator >> (std::istream &strm, CPoint & point)
{
	strm >> point.x;
	strm >> point.y;
	return strm;
}