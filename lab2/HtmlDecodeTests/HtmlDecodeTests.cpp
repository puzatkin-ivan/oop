#include "stdafx.h"
#include "../HtmlDecode/HtmlDecode.h"

BOOST_AUTO_TEST_SUITE(HtmlDecode_function)
	BOOST_AUTO_TEST_CASE(makes_no_change_string_without_html)
	{
		std::string input = "Thó string doesn't contain html-entities";
		auto result = HtmlDecode(input);
		BOOST_CHECK_EQUAL(input, result);
	}
	BOOST_AUTO_TEST_CASE(decode_a_single_html_entity)
	{
		std::string input = "The string does contain html-entity 1 &lt; 2";
		std::string expectedResult = "The string does contain html-entity 1 < 2";
		auto result = HtmlDecode(input);
		BOOST_CHECK_EQUAL(expectedResult, result);
	}
	BOOST_AUTO_TEST_CASE(decode_all_html_entity)
	{
		std::string input = "&lt;p&gt;The string doesn&apos;t contain &quot;html-entities&quot;&lt;/p&gt;";
		std::string expectedResult = "<p>The string doesn't contain \"html-entities\"</p>";
		auto result = HtmlDecode(input);
		BOOST_CHECK_EQUAL(expectedResult, result);
	}
BOOST_AUTO_TEST_SUITE_END()
