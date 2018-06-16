#include "stdafx.h"
#include "../exam/StringList.h"
#include <sstream>

BOOST_AUTO_TEST_SUITE(StringList)
	BOOST_AUTO_TEST_CASE(has_a_constructor_by_default)
	{
		CStringList list;
		BOOST_CHECK(list.IsEmpty());
		BOOST_CHECK_THROW(list.GetFront(), std::logic_error);
	}
	BOOST_AUTO_TEST_CASE(add_to_begin_data)
	{
		CStringList list;
		BOOST_CHECK(list.IsEmpty());
		list.AddToBegin("first");
		list.AddToBegin("second");
		list.AddToBegin("third");
		BOOST_CHECK(list.GetSize() == 3);
		BOOST_CHECK(list.GetFront() == "third");
	}
	BOOST_AUTO_TEST_CASE(has_copy_constructor)
	{
		CStringList list;
		list.AddToBegin("StringList");
		list.AddToBegin("Exam");
		CStringList newList(list);
		BOOST_CHECK(list.GetSize() == newList.GetSize());
		BOOST_CHECK(list.GetFront() == newList.GetFront());
	}
	struct StringListFixture
	{
		StringListFixture()
		{
			list.AddToBegin("from the European mainland by the English Channel and North Sea.");
			list.AddToBegin("an island separated");
			list.AddToBegin("is");
			list.AddToBegin("Great Britain");
		}
		CStringList list;
	};

	BOOST_FIXTURE_TEST_SUITE(when_string_list_is_not_empty, StringListFixture)
		BOOST_AUTO_TEST_CASE(has_operator_copy_list)
		{
			CStringList newList;
			newList = list;
			BOOST_CHECK(newList.GetSize() == list.GetSize());
			BOOST_CHECK(newList.GetFront() == list.GetFront());
			newList = CStringList();
			BOOST_CHECK(newList.IsEmpty());
			BOOST_CHECK_THROW(newList.GetFront(), std::logic_error);
		}
		BOOST_AUTO_TEST_CASE(get_front)
		{
			CStringList emptyList;
			BOOST_CHECK(emptyList.IsEmpty());
			BOOST_CHECK_THROW(emptyList.GetFront(), std::logic_error);
			BOOST_CHECK(!list.IsEmpty());
			BOOST_CHECK(list.GetFront() == "Great Britain");
			list.AddToBegin("new first");
			BOOST_CHECK(list.GetFront() == "new first");
		}
		BOOST_AUTO_TEST_CASE(clear_list)
		{
			BOOST_CHECK(!list.IsEmpty());
			list.Clear();
			BOOST_CHECK(list.GetSize() == 0);
			BOOST_CHECK_THROW(list.GetFront(), std::logic_error);
		}
		BOOST_AUTO_TEST_CASE(print_list)
		{
			std::stringstream out;
			CStringList emptyList;
			BOOST_CHECK(emptyList.IsEmpty());
			emptyList.PrintList(out);
			BOOST_CHECK(out.str().empty());
			list.PrintList(out);
			BOOST_CHECK(out.str() == "Great Britain\nis\nan island separated\nfrom the European mainland by the English Channel and North Sea.\n");
		}
	BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
