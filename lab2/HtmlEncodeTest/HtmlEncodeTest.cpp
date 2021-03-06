#include "stdafx.h"
#include "../HtmlEncode/HtmlEncode.h"

BOOST_AUTO_TEST_SUITE(HtmlEncode_function)
	BOOST_AUTO_TEST_CASE(makes_no_change_string_without_html)
	{
		std::string input = "Thу string doesnot contain html-entities";
		auto result = HtmlEncode(input);
		BOOST_CHECK_EQUAL(input, result);
	}
	BOOST_AUTO_TEST_CASE(encode_all_html_entities)
	{
		std::string input = "<p>\"Tim & his team\"</p>";
		std::string expectedResult = "&lt;p&gt;&quot;Tim &amp; his team&quot;&lt;/p&gt;";
		auto result = HtmlEncode(input);
		BOOST_CHECK_EQUAL(expectedResult, result);
	}
BOOST_AUTO_TEST_SUITE_END()
