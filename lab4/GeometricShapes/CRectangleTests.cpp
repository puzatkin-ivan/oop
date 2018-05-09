#include "stdafx.h"
#include "../GeometricShapes/CPoint.h"
#include "../GeometricShapes/CRectangle.h"

namespace
{
static const unsigned HEIGHT = 100;

static const unsigned WIDTH = 100;

static const std::string OUTLINE_COLOR = "#ffffff";

static const std::string FILL_COLOR = "#ffffff";
}

struct CRectangleFixture
{
	CRectangleFixture()
		: point(12, 42)
		, rectangle(point, HEIGHT, WIDTH, OUTLINE_COLOR, FILL_COLOR)
	{
	}

	std::string GetExpectedRectangleInfo()
	{
		const auto rectangleArea = WIDTH * HEIGHT;
		const auto rectanglePerimeter = 2 * (WIDTH + HEIGHT);
		std::ostringstream rectangleInfo;
		rectangleInfo << "Type: Rectangle" << std::endl;
		rectangleInfo << "Area: " << rectangleArea << std::endl;
		rectangleInfo << "Perimeter: " << rectanglePerimeter << std::endl;
		rectangleInfo << "OutlineColor: " << OUTLINE_COLOR << std::endl;
		rectangleInfo << "FillColor: " << FILL_COLOR << std::endl;
		return rectangleInfo.str();
	}

	CRectangle rectangle;
	CPoint point;
};

BOOST_FIXTURE_TEST_SUITE(CRectangle_, CRectangleFixture)
	BOOST_AUTO_TEST_CASE(correct_initialization)
	{
		BOOST_CHECK(rectangle.ToString == GetExpectedRectangleInfo());
	}
BOOST_AUTO_TEST_SUITE_END()
