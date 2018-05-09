#include "stdafx.h"
#include "../GeometricShapes/CCircle.h"

namespace
{
static const CPoint CENTER(14, 34);

static const double RADIUS = 63;

static const double AREA_CIRCLE = M_PI * RADIUS * RADIUS;

static const double PERIMETER_CIRCLE = 2 * M_PI * RADIUS;

static const std::string OUTLINE_COLOR = "#abc012";

static const std::string FILL_COLOR = "#abc012";
}

struct SCircleFixture
{
	SCircleFixture()
		: circle(CENTER, RADIUS, OUTLINE_COLOR, FILL_COLOR)
	{
	}

	std::string GetExpectedStringRepresntation()
	{
		std::ostringstream stream;
		stream << "Type: " << "Circle" << std::endl;
		stream << "Area: " << AREA_CIRCLE << std::endl;
		stream << "Perimeter: " << PERIMETER_CIRCLE << std::endl;
		stream << "Outline Color: " << OUTLINE_COLOR << std::endl;
		stream << "Fill Color: " << FILL_COLOR << std::endl;
		return stream.str();
	}

	CCircle circle;
};

BOOST_FIXTURE_TEST_SUITE(Circle, SCircleFixture)
	BOOST_AUTO_TEST_CASE(has_a_center)
	{
		BOOST_CHECK(circle.GetCenter().x == CENTER.x);
		BOOST_CHECK(circle.GetCenter().y == CENTER.y);
	}
	BOOST_AUTO_TEST_CASE(has_a_radius)
	{
		BOOST_CHECK(circle.GetRadius() == RADIUS);
	}
	BOOST_AUTO_TEST_CASE(can_find_perimeter)
	{
		BOOST_CHECK(circle.GetPerimeter() == PERIMETER_CIRCLE);
	}
	BOOST_AUTO_TEST_CASE(can_find_area)
	{
		BOOST_CHECK(circle.GetArea() == AREA_CIRCLE);
	}
	BOOST_AUTO_TEST_CASE(has_a_outline_color)
	{
		BOOST_CHECK(circle.GetOutlineColor() == OUTLINE_COLOR);
	}
	BOOST_AUTO_TEST_CASE(has_a_fill_color)
	{
		BOOST_CHECK(circle.GetFillColor() == FILL_COLOR);
	}	
	BOOST_AUTO_TEST_CASE(has_a_string_representation)
	{
		BOOST_CHECK(circle.ToString() == GetExpectedStringRepresntation());
	}
	BOOST_AUTO_TEST_CASE(can_change_outline_color)
	{
		auto newColor = "#123312";
		circle.SetOutlineColor(newColor);
		BOOST_CHECK(circle.GetOutlineColor() == newColor);
	}
	BOOST_AUTO_TEST_CASE(can_change_fill_color)
	{
		auto newColor = "#123312";
		circle.SetFillColor(newColor);
		BOOST_CHECK(circle.GetFillColor() == newColor);
	}
BOOST_AUTO_TEST_SUITE_END()
