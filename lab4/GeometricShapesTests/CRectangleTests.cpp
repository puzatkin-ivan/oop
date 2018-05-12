#include "stdafx.h"
#include "../GeometricShapes/CPoint.h"
#include "../GeometricShapes/CRectangle.h"

namespace
{
static const CPoint LEFT_TOP_VERTEX(12, 12);

static const double WIDTH = 10;

static const double HEIGHT = 10;

static const std::string OUTLINE_COLOR = "#abc012";

static const std::string FILL_COLOR = "#abc012";
} // namespace

struct SRectangleFixture
{
	SRectangleFixture()
		: rectangle(LEFT_TOP_VERTEX, HEIGHT, WIDTH, OUTLINE_COLOR, FILL_COLOR)
	{
	}

	double GetExpectedArea() const
	{
		return WIDTH * HEIGHT;
	}

	double GetExpectedPerimeter() const
	{
		return 2 * (WIDTH + HEIGHT);
	}

	std::string GetExpectedStringRepresntation()
	{
		std::ostringstream stream;
		stream << "Type: " << "Rectangle" << std::endl;
		stream << "Area: " << GetExpectedArea() << std::endl;
		stream << "Perimeter: " << GetExpectedPerimeter() << std::endl;
		stream << "Outline Color: " << OUTLINE_COLOR << std::endl;
		stream << "Fill Color: " << FILL_COLOR << std::endl;
		stream << "Left Top Vertex: " << rectangle.GetLeftTop().x << " " << rectangle.GetLeftTop().y << std::endl;
		stream << "Width: " << rectangle.GetWidth() << std::endl;
		stream << "Height: " << rectangle.GetHeight() << std::endl;
		return stream.str();
	}

	bool VerifyPoints(const CPoint& lhs, const CPoint& rhs)
	{
		return (lhs.x == lhs.x) && (lhs.y == rhs.y);
	}

	CRectangle rectangle;
};

BOOST_FIXTURE_TEST_SUITE(Rectangle, SRectangleFixture)
	BOOST_AUTO_TEST_CASE(has_a_left_top_vertex)
	{
		BOOST_CHECK(VerifyPoints(rectangle.GetLeftTop(), LEFT_TOP_VERTEX));
	}
	BOOST_AUTO_TEST_CASE(has_a_perimeter)
	{
		BOOST_CHECK(rectangle.GetPerimeter() == GetExpectedPerimeter());
	}
	BOOST_AUTO_TEST_CASE(has_an_area)
	{
		BOOST_CHECK(rectangle.GetArea() == GetExpectedArea());
	}
	BOOST_AUTO_TEST_CASE(has_a_width)
	{
		BOOST_CHECK(rectangle.GetWidth() == WIDTH);
	}
	BOOST_AUTO_TEST_CASE(has_a_height)
	{
		BOOST_CHECK(rectangle.GetHeight() == HEIGHT);
	}
	BOOST_AUTO_TEST_CASE(has_a_outline_color)
	{
		BOOST_CHECK(rectangle.GetOutlineColor() == OUTLINE_COLOR);
	}
	BOOST_AUTO_TEST_CASE(has_a_fill_color)
	{
		BOOST_CHECK(rectangle.GetFillColor() == FILL_COLOR);
	}
	BOOST_AUTO_TEST_CASE(has_a_string_representation)
	{
		BOOST_CHECK(rectangle.ToString() == GetExpectedStringRepresntation());
	}
	BOOST_AUTO_TEST_CASE(can_be_change_left_top_vertex)
	{
		rectangle.SetLeftTop(CPoint(123, 312));
		BOOST_CHECK(VerifyPoints(rectangle.GetLeftTop(), CPoint(123, 312)));
	}
	BOOST_AUTO_TEST_CASE(can_be_change_width)
	{
		rectangle.SetWidth(54);
		BOOST_CHECK(rectangle.GetWidth() == 54);
	}
	BOOST_AUTO_TEST_CASE(can_be_change_height)
	{
		rectangle.SetHeight(54);
		BOOST_CHECK(rectangle.GetHeight() == 54);
	}
	BOOST_AUTO_TEST_CASE(can_change_outline_color)
	{
		auto newColor = "#123312";
		rectangle.SetOutlineColor(newColor);
		BOOST_CHECK(rectangle.GetOutlineColor() == newColor);
	}
	BOOST_AUTO_TEST_CASE(can_change_fill_color)
	{
		auto newColor = "#123312";
		rectangle.SetFillColor(newColor);
		BOOST_CHECK(rectangle.GetFillColor() == newColor);
	}
BOOST_AUTO_TEST_SUITE_END()
