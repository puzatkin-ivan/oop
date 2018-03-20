#include "stdafx.h"
#include "../vector/processVector.h"

bool IsVectorsEqual(const std::vector<double> & lhs, const std::vector<double> & rhs)
{
	return lhs == rhs;
}

BOOST_AUTO_TEST_SUITE(Vector)
	BOOST_AUTO_TEST_SUITE(GetNumbers_function)
		BOOST_AUTO_TEST_CASE(get_empty_vector_from_empty_istream)
		{
			std::stringstream inputDoubleNumbers("");
			auto numbers = GetNumbers(inputDoubleNumbers);
			std::vector<double> expectedNumbers;
			BOOST_CHECK(IsVectorsEqual(numbers, expectedNumbers));
		}
		BOOST_AUTO_TEST_CASE(get_double_numbers_from_istream)
		{
			std::stringstream inputDoubleNumbers("4.13 3.14 1.34 4.31 3.41");
			auto numbers = GetNumbers(inputDoubleNumbers);
			std::vector<double> expectedNumbers = { 4.13, 3.14, 1.34, 4.31, 3.41 };
			BOOST_CHECK(IsVectorsEqual(numbers, expectedNumbers));
		}
	BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE(ProcessVector_function)
		BOOST_AUTO_TEST_CASE(makes_empty_vector_from_empty_vector)
		{
			std::vector<double> empty;
			ProcessVector(empty);
			BOOST_CHECK(empty.empty());
		}
		BOOST_AUTO_TEST_CASE(does_no_change_vector_containing_zero)
		{
			std::vector<double> numbers = { 0, 1, 2, 3, 4, 5 };
			auto expectedNumbers(numbers);
			ProcessVector(numbers);
			BOOST_CHECK(IsVectorsEqual(numbers, expectedNumbers));
		}
		BOOST_AUTO_TEST_CASE(does_no_change_vector_containing_a_single_element)
		{
			std::vector<double> numbers = { 1 };
			auto expectedNumbers(numbers);
			ProcessVector(numbers);
			BOOST_CHECK(IsVectorsEqual(numbers, expectedNumbers));
		}
		BOOST_AUTO_TEST_CASE(process_input_with_values)
		{
			std::vector<double> numbers = { -1, 4, 5, 6, 7 };
			std::vector<double> expectedNumbers = { 1, -4, -5, -6, -7 };
			ProcessVector(numbers);
			BOOST_CHECK(IsVectorsEqual(numbers, expectedNumbers));
		}
		BOOST_AUTO_TEST_CASE(process_input_with_one_repeated_values)
		{
			std::vector<double> numbers = { -1, -1, -1, -1, -1 };
			std::vector<double> expectedNumbers = { 1, 1, 1, 1, 1 };
			ProcessVector(numbers);
			BOOST_CHECK(IsVectorsEqual(numbers, expectedNumbers));
		}

		BOOST_AUTO_TEST_CASE(process_usually_input)
		{
			std::vector<double> numbers = { 312, 314, 707, 602, 910 };
			std::vector<double> expectedNumbers = { 312 * 312, 314 * 312, 707 * 312, 602 * 312, 910 * 312 };
			ProcessVector(numbers);
			BOOST_CHECK(IsVectorsEqual(numbers, expectedNumbers));
		}
	BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()