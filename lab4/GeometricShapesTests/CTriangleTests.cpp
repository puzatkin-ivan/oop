#include "stdafx.h"
#include "../GeometricShapes/CPoint.h"
#include "../GeometricShapes/CTriangle.h"

namespace
{
static const std::array<CPoint, 3> VERTEX = { CPoint(20, 12), CPoint(12, 12), CPoint(12, 45) };

static const std::string OUTLINE_COLOR = "#abc012";

static const std::string FILL_COLOR = "#abc012";
} // namespace

struct STriangleFixture
{
	STriangleFixture()
		: triangle(VERTEX[0], VERTEX[1], VERTEX[2], OUTLINE_COLOR, FILL_COLOR)
	{
	}

	double GetExpectedArea() const
	{
		auto p = GetExpectedPerimeter() / 2;
		auto a = std::hypot(VERTEX[0].x - VERTEX[1].x, VERTEX[0].y - VERTEX[1].y);
		auto b = std::hypot(VERTEX[1].x - VERTEX[2].x, VERTEX[1].y - VERTEX[2].y);
		auto c = std::hypot(VERTEX[2].x - VERTEX[0].x, VERTEX[2].y - VERTEX[0].y);
		return std::sqrt(p * (p - a) * (p - b) * (p - c));
	}

	double GetExpectedPerimeter() const
	{
		auto a = std::hypot(VERTEX[0].x - VERTEX[1].x, VERTEX[0].y - VERTEX[1].y);
		auto b = std::hypot(VERTEX[1].x - VERTEX[2].x, VERTEX[1].y - VERTEX[2].y);
		auto c = std::hypot(VERTEX[2].x - VERTEX[0].x, VERTEX[2].y - VERTEX[0].y);
		return a + b + c;
	}

	std::string GetExpectedStringRepresntation()
	{
		std::ostringstream stream;
		stream << "Type: " << "Triangle" << std::endl;
		stream << "Area: " << GetExpectedArea() << std::endl;
		stream << "Perimeter: " << GetExpectedPerimeter() << std::endl;
		stream << "Outline Color: " << OUTLINE_COLOR << std::endl;
		stream << "Fill Color: " << FILL_COLOR << std::endl;
		return stream.str();
	}

	bool VerifyPoints(const CPoint& lhs, const CPoint& rhs)
	{
		return (lhs.x == lhs.x) && (lhs.y == rhs.y);
	}

	CTriangle triangle;
};

BOOST_FIXTURE_TEST_SUITE(Triangle, STriangleFixture)
	BOOST_AUTO_TEST_CASE(has_a_vertex_1)
	{
		BOOST_CHECK(VerifyPoints(triangle.GetVertex1(), VERTEX[0]));
	}
	BOOST_AUTO_TEST_CASE(has_a_vertex_2)
	{
		BOOST_CHECK(VerifyPoints(triangle.GetVertex2(), VERTEX[1]));
	}
	BOOST_AUTO_TEST_CASE(has_a_vertex_3)
	{
		BOOST_CHECK(VerifyPoints(triangle.GetVertex3(), VERTEX[2]));
	}
	BOOST_AUTO_TEST_CASE(can_find_perimeter)
	{
		BOOST_CHECK(triangle.GetPerimeter() == GetExpectedPerimeter());
	}
	BOOST_AUTO_TEST_CASE(can_find_area)
	{
		BOOST_CHECK(triangle.GetArea() == GetExpectedArea());
	}
	BOOST_AUTO_TEST_CASE(has_a_outline_color)
	{
		BOOST_CHECK(triangle.GetOutlineColor() == OUTLINE_COLOR);
	}
	BOOST_AUTO_TEST_CASE(has_a_fill_color)
	{
		BOOST_CHECK(triangle.GetFillColor() == FILL_COLOR);
	}
	BOOST_AUTO_TEST_CASE(has_a_string_representation)
	{
		BOOST_CHECK(triangle.ToString() == GetExpectedStringRepresntation());
	}
	BOOST_AUTO_TEST_CASE(can_change_outline_color)
	{
		auto newColor = "#123312";
		triangle.SetOutlineColor(newColor);
		BOOST_CHECK(triangle.GetOutlineColor() == newColor);
	}
	BOOST_AUTO_TEST_CASE(can_change_fill_color)
	{
		auto newColor = "#123312";
		triangle.SetFillColor(newColor);
		BOOST_CHECK(triangle.GetFillColor() == newColor);
	}
BOOST_AUTO_TEST_SUITE_END()
