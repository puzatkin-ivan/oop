#include "stdafx.h"
#include "../GeometricShapes/CShapeController.h"
#include <sstream>

struct CShapeControllerFixture_
{
	CShapeControllerFixture_()
		: controller(shape, ostream)
	{
		controller.AddItem("linesegment", std::make_unique<CAddLineSegmentCommand>(shape));
		controller.AddItem("circle", std::make_unique<CAddCircleCommand>(shape));
		controller.AddItem("rectangle", std::make_unique<CAddRectangleCommand>(shape));
		controller.AddItem("triangle", std::make_unique<CAddTriangleCommand>(shape));
		controller.AddItem("info", std::make_unique<CPrintMinPerimeterCommand>(shape, ostream));
	}
	std::stringstream ostream;
	CShapeController controller;
	std::vector<std::unique_ptr<IShape>> shape;

	std::string VerifyPrintTriangle(const std::vector<CPoint>& vertices, double area, double perimeter, const std::string& outlineColor, const std::string& fillcolor)
	{
		std::stringstream stream;
		stream << "Type: "
			   << "Triangle" << std::endl;
		stream << "Area: " << area << std::endl;
		stream << "Perimeter: " << perimeter << std::endl;
		stream << "Outline Color: " << outlineColor << std::endl;
		stream << "Fill Color: " << fillcolor << std::endl;
		stream << "Vertex1: " << vertices[0].x << " " << vertices[0].y << std::endl;
		stream << "Vertex2: " << vertices[1].x << " " << vertices[1].y << std::endl;
		stream << "Vertex3: " << vertices[2].x << " " << vertices[2].y << std::endl;
		stream << std::endl;
		return stream.str();
	}

	std::string ExpectedOutputAfterExecuteCommand(const std::vector<CPoint>& vertices, double area, double perimeter, const std::string& outlineColor, const std::string& fillcolor)
	{
		std::stringstream stream;
		stream << "Minimum perimeter of the shape:\n"
			   << VerifyPrintTriangle(vertices, area, perimeter, outlineColor, fillcolor) << std::endl;
		stream << "Maximum area of the shape:\n"
			   << VerifyPrintTriangle(vertices, area, perimeter, outlineColor, fillcolor) << std::endl;
		return stream.str();
	}

	std::string VerifyPrintInfo()
	{
		std::stringstream stream;
		stream << "Info About Shapes:" << std::endl;
		stream << VerifyPrintTriangle({ CPoint(0, 0), CPoint(5, 12), CPoint(5, 0) }, 30, 30, "#1231", "#1231");
		stream << VerifyPrintTriangle({ CPoint(0, 0), CPoint(5, 12), CPoint(5, 0) }, 30, 30, "#1231", "#1231");
		stream << VerifyPrintTriangle({ CPoint(0, 0), CPoint(5, 12), CPoint(5, 0) }, 30, 30, "#1231", "#1231");
		return stream.str();
	}
};

BOOST_FIXTURE_TEST_SUITE(ShapeController, CShapeControllerFixture_)
	BOOST_AUTO_TEST_SUITE(Commands)
		BOOST_AUTO_TEST_CASE(run_add_line_segment)
		{
			std::stringstream commandNone;
			CAddLineSegmentCommand addLine(shape);
			BOOST_CHECK_THROW(addLine.Execute(commandNone), std::invalid_argument);
			std::stringstream istream("linesegment 12 45 12 12");
			BOOST_CHECK_THROW(addLine.Execute(istream), std::invalid_argument);

			istream = std::stringstream("linesegment 12 45 12 12 #123");
			BOOST_CHECK_NO_THROW(addLine.Execute(istream));

			istream = std::stringstream("linesegment 12 45 12 12 #123 #extra");
			BOOST_CHECK_THROW(addLine.Execute(istream), std::invalid_argument);
		}
		BOOST_AUTO_TEST_CASE(run_add_cicrle)
		{
			BOOST_CHECK(shape.size() == 0);
			std::stringstream istream("circle 12 123 123 451231");
			CAddCircleCommand addCircle(shape);
			BOOST_CHECK_THROW(addCircle.Execute(istream), std::invalid_argument);

			istream = std::stringstream("circle 12 123 123 451231 123");
			BOOST_CHECK_NO_THROW(addCircle.Execute(istream));
			BOOST_CHECK(shape.size() == 1);

			istream = std::stringstream("circle 12 123 123 451231 123 extra");
			BOOST_CHECK_THROW(addCircle.Execute(istream), std::invalid_argument);
		}
		BOOST_AUTO_TEST_CASE(run_add_rectangle)
		{
			std::stringstream istream("rectangle 12 123 123 321123 #12331");
			CAddRectangleCommand command1(shape);
			BOOST_CHECK_THROW(command1.Execute(istream), std::invalid_argument);

			istream = std::stringstream("rectangle 12 123 123 321123 #12331 #da12");
			CAddRectangleCommand command2(shape);
			BOOST_CHECK_NO_THROW(command2.Execute(istream));

			istream = std::stringstream("rectangle 12 123 123 321123 #12331 #da12 #extra");
			CAddRectangleCommand command3(shape);
			BOOST_CHECK_THROW(command3.Execute(istream), std::invalid_argument);
		}
		BOOST_AUTO_TEST_CASE(run_add_triangle)
		{
			std::stringstream istream("triangle 12 212 321 451231 123 1231 #1231");
			CAddTriangleCommand command1(shape);
			BOOST_CHECK_THROW(command1.Execute(istream), std::invalid_argument);

			istream = std::stringstream("triangle 12 212 321 451231 123 1231 #1231 #1231");
			CAddTriangleCommand command2(shape);
			BOOST_CHECK_NO_THROW(command2.Execute(istream));

			istream = std::stringstream("triangle 12 212 321 451231 123 1231 #1231 #1231 #extra");
			CAddTriangleCommand command3(shape);
			BOOST_CHECK_THROW(command3.Execute(istream), std::invalid_argument);
		}
		BOOST_AUTO_TEST_CASE(run_print_info)
		{
			std::stringstream istream;
			CPrintInfoCommand command(shape, ostream);
			BOOST_CHECK(shape.size() == 0);
			BOOST_CHECK_NO_THROW(command.Execute(istream));
			BOOST_CHECK(ostream.str() == "Shapes is empty.\n");

			ostream = std::stringstream();
			CAddTriangleCommand addTriangle(shape);
			istream.str("triangle 0 0 5 12 5 0 #1231 #1231");
			BOOST_CHECK_NO_THROW(addTriangle.Execute(istream));
			std::stringstream input2("triangle 0 0 5 12 5 0 #1231 #1231");
			BOOST_CHECK_NO_THROW(addTriangle.Execute(input2));
			std::stringstream input3("triangle 0 0 5 12 5 0 #1231 #1231");
			BOOST_CHECK_NO_THROW(addTriangle.Execute(input3));
			BOOST_CHECK_NO_THROW(command.Execute(istream));
			std::ofstream put("123.txt");
			put << ostream.str();
			BOOST_CHECK(ostream.str() == VerifyPrintInfo());
		}
		BOOST_AUTO_TEST_CASE(run_print_min_perimeter)
		{
			CPrintMinPerimeterCommand command(shape, ostream);
			BOOST_CHECK(shape.size() == 0);
			std::stringstream istream;
			command.Execute(istream);
			BOOST_CHECK(ostream.str() == "Shapes is empty.\n");

			ostream = std::stringstream();
			CAddTriangleCommand addTriangle(shape);
			istream = std::stringstream("triangle 0 0 5 56 5 0 #1231 #1231");
			BOOST_CHECK_NO_THROW(addTriangle.Execute(istream));
			istream = std::stringstream("triangle 0 0 5 12 5 0 #1231 #1231");
			BOOST_CHECK_NO_THROW(addTriangle.Execute(istream));
			CPrintMinPerimeterCommand command2(shape, ostream);
			BOOST_CHECK_NO_THROW(command2.Execute(istream));

			std::vector<CPoint> vertices = { CPoint(0, 0), CPoint(5, 12), CPoint(5, 0) };
			auto expectedOutput = "Minimum perimeter of the shape:\n" + VerifyPrintTriangle(vertices, 30, 30, "#1231", "#1231");
			BOOST_CHECK(ostream.str() == expectedOutput);
		}
		BOOST_AUTO_TEST_CASE(run_print_max_area)
		{
			BOOST_CHECK(shape.size() == 0);
			CPrintMaxAreaCommand printMaxAreaWhenShapeIsEmpty(shape, ostream);
			std::stringstream istream;
			printMaxAreaWhenShapeIsEmpty.Execute(istream);
			BOOST_CHECK(ostream.str() == "Shapes is empty.\n");

			istream = std::stringstream("triangle 0 0 5 12 5 0 #1231 #1231");
			CAddTriangleCommand addTriangleCommand(shape);
			BOOST_CHECK_NO_THROW(addTriangleCommand.Execute(istream));

			istream = std::stringstream("triangle 0 0 5 10 5 0 #1231 #1231");
			BOOST_CHECK_NO_THROW(addTriangleCommand.Execute(istream));

			BOOST_CHECK(shape.size() == 2);
			CPrintMaxAreaCommand(shape, ostream);

			std::vector<CPoint> vertices = { CPoint(0, 0), CPoint(5, 12), CPoint(5, 0) };
			std::stringstream output;
			CPrintMaxAreaCommand printMaxArea(shape, output);
			printMaxArea.Execute(istream);
			auto expectedOutput = "Maximum area of the shape:\n" + VerifyPrintTriangle(vertices, 30, 30, "#1231", "#1231");
			BOOST_CHECK(output.str() == expectedOutput);
		}
	BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_CASE(run_commands)
	{
		std::stringstream input("info\ntriangle 0 5 6 7 12 21 #a21 #122\n");
		BOOST_CHECK_NO_THROW(controller.Run(input));
		std::stringstream inputError("show world");
		BOOST_CHECK_THROW(controller.Run(inputError), std::invalid_argument);
	}

BOOST_AUTO_TEST_SUITE_END()
