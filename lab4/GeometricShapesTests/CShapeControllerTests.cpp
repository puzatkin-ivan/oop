#include "stdafx.h"
#include "../GeometricShapes/CShapeController.h"

struct CShapeControllerFixture_
{
	CShapeController controller;
};

BOOST_FIXTURE_TEST_SUITE(ShapeController, CShapeControllerFixture_)
	BOOST_AUTO_TEST_CASE(handle_an_unknown_command)
	{
		std::string command = "show all figure";
		BOOST_CHECK_THROW(controller.HandleCommand(command), std::invalid_argument);
	}
	BOOST_AUTO_TEST_CASE(add_linesegment_with_invalid_count_parameter)
	{
		std::string command = "linesegment 12 45 12";
		BOOST_CHECK_THROW(controller.HandleCommand(command), std::invalid_argument);
	}
	BOOST_AUTO_TEST_CASE(add_circle_with_invalid_count_parameter)
	{
		std::string command = "circle 12 45";
		BOOST_CHECK_THROW(controller.HandleCommand(command), std::invalid_argument);
	}
	BOOST_AUTO_TEST_CASE(add_rectangle_with_invalid_count_parameter)
	{
		std::string command = "rectangle 12 45";
		BOOST_CHECK_THROW(controller.HandleCommand(command), std::invalid_argument);
	}
	BOOST_AUTO_TEST_CASE(add_triangle_with_invalid_count_parameter)
	{
		std::string command = "triangle 12 45";
		BOOST_CHECK_THROW(controller.HandleCommand(command), std::invalid_argument);
	}
	BOOST_AUTO_TEST_CASE(print_min_perimeter_will_not_exception_when_shapes_is_empty)
	{
		BOOST_CHECK_NO_THROW(controller.PrintMinPerimeter());
	}
	BOOST_AUTO_TEST_CASE(print_max_area_will_not_exception_when_shapes_is_empty)
	{
		BOOST_CHECK_NO_THROW(controller.PrintMaxArea());
	}
BOOST_AUTO_TEST_SUITE_END()
