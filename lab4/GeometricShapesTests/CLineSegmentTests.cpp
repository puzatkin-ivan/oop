#include "stdafx.h"
#include "../GeometricShapes/CLineSegment.h"
#include "../GeometricShapes/CPoint.h"

namespace
{
static const CPoint START_POINT(12, 57);

static const CPoint END_POINT(15, 17);

static const std::string OUTLINE_COLOR = "#abc012";
}

struct CLineSegmentFixture
{
	CLineSegmentFixture()
		: line(START_POINT, END_POINT, OUTLINE_COLOR)
	{
	}

	bool VerifyPoints(const CPoint& lhs, const CPoint& rhs)
	{
		return (lhs.x == lhs.x) && (lhs.y == rhs.y);
	}

	double GetLengthByPoints(const CPoint& startPoint, const CPoint& endPoint)
	{
		return std::hypot(endPoint.x - startPoint.x,
			endPoint.y - startPoint.y);
	}

	std::string GetExpectedStringRepresntation()
	{
		std::ostringstream stream;
		stream << "Type: " << "LineSegment" << std::endl;
		stream << "Area: " << 0.0 << std::endl;
		stream << "Perimeter: " << GetLengthByPoints(START_POINT, END_POINT) << std::endl;
		stream << "Outline Color: " << OUTLINE_COLOR << std::endl;
		stream << "StartPoint: " << START_POINT.x << " " << START_POINT.y << std::endl;
		stream << "EndPoint: " << END_POINT.x << " " << END_POINT.y << std::endl;
		return stream.str();
	}

	CLineSegment line;
};

BOOST_FIXTURE_TEST_SUITE(CLineSegment_, CLineSegmentFixture)
	BOOST_AUTO_TEST_CASE(has_a_start_point)
	{
		BOOST_CHECK(VerifyPoints(line.GetStartPoint(), START_POINT));
	}
	BOOST_AUTO_TEST_CASE(has_a_end_point)
	{
		BOOST_CHECK(VerifyPoints(line.GetEndPoint(), END_POINT));
	}
	BOOST_AUTO_TEST_CASE(has_a_area)
	{
		BOOST_CHECK(line.GetArea() == 0);
	}
	BOOST_AUTO_TEST_CASE(has_a_perimeter)
	{
		BOOST_CHECK(line.GetPerimeter() == GetLengthByPoints(START_POINT, END_POINT));
	}
	BOOST_AUTO_TEST_CASE(has_a_outline_color)
	{
		BOOST_CHECK(line.GetOutlineColor() == OUTLINE_COLOR);
	}
	BOOST_AUTO_TEST_CASE(has_a_string_representation)
	{
		BOOST_CHECK(line.ToString() == GetExpectedStringRepresntation());
	}
	BOOST_AUTO_TEST_CASE(can_be_change_start_point)
	{
		auto newStartPoint = CPoint(12, 54);
		line.SetStartPoint(newStartPoint);
		BOOST_CHECK(VerifyPoints(line.GetStartPoint(), newStartPoint));
	}
	BOOST_AUTO_TEST_CASE(can_be_change_end_point)
	{
		auto newEndPoint = CPoint(17, 44);
		line.SetEndPoint(newEndPoint);
		BOOST_CHECK(VerifyPoints(line.GetEndPoint(), newEndPoint));
	}
	BOOST_AUTO_TEST_CASE(can_be_change_outline_color)
	{
		auto newOutlineColor = "#123123";
		line.SetOutlineColor(newOutlineColor);
		BOOST_CHECK(line.GetOutlineColor() == newOutlineColor);
	}
BOOST_AUTO_TEST_SUITE_END()
