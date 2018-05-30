#include "stdafx.h"
#include "../StringList/CStringList.h"
#include <iostream>

struct string_list
{
	string_list()
	{
		list.PushBack("Keep Calm");
		list.PushBack("And");
		list.PushBack("Write Tests");
	}

	bool VerifyStringList(const CStringList& lhs, const CStringList& rhs)
	{
		if (lhs.GetSize() != rhs.GetSize())
		{
			return false;
		}
		auto lhsIt = lhs.begin();
		auto rhsIt = rhs.begin();
		for (; lhsIt != lhs.end() && rhsIt != rhs.end(); ++lhsIt, ++rhsIt)
		{
			BOOST_CHECK(*lhsIt == *rhsIt);
		}
		return lhsIt == lhs.end() && rhsIt == rhs.end();
	}

	CStringList baseList;
	CStringList list;
};

BOOST_FIXTURE_TEST_SUITE(StringList, string_list)
	BOOST_AUTO_TEST_SUITE(by_default)
		BOOST_AUTO_TEST_CASE(is_empty)
		{
			BOOST_CHECK(baseList.GetSize() == 0);
		}
		BOOST_AUTO_TEST_CASE(iterators_point_at_nullptr)
		{
			BOOST_CHECK(baseList.begin() == CIterator());
			BOOST_CHECK(baseList.end() == CIterator());
			BOOST_CHECK(baseList.cbegin() == CIterator());
			BOOST_CHECK(baseList.cend() == CIterator());
			BOOST_CHECK(baseList.rbegin() == CIterator(nullptr, true));
			BOOST_CHECK(baseList.rend() == CIterator(nullptr, true));
		}
	BOOST_AUTO_TEST_SUITE_END()
	BOOST_AUTO_TEST_CASE(has_copy_constructor)
	{
		CStringList copyList(list);
		BOOST_CHECK(VerifyStringList(list, copyList));
	}
	BOOST_AUTO_TEST_CASE(has_move_constructor)
	{
		CStringList copyList(list);
		CStringList moveList(std::move(copyList));
		BOOST_CHECK(copyList.GetSize() == 0);
		BOOST_CHECK(VerifyStringList(moveList, list));
	}
	BOOST_AUTO_TEST_CASE(can_push_back)
	{
		baseList.PushBack("Keep Calm");
		baseList.PushBack("And");
		BOOST_CHECK(baseList.GetSize() == 2);
		BOOST_CHECK(baseList.PopBack() == "And");
	}
	BOOST_AUTO_TEST_CASE(can_push_front)
	{
		list.PushFront("Keep Calm");
		BOOST_CHECK(list.PopFront() == "Keep Calm");
		BOOST_CHECK_EQUAL(list.PopFront(), "Keep Calm");
	}
	BOOST_AUTO_TEST_CASE(can_insert_by_iterator)
	{
		baseList.Insert(baseList.begin(), "Keep Calm");
		BOOST_CHECK_EQUAL(list.PopFront(), "Keep Calm");

		CStringList tmpList;
		tmpList.Insert(tmpList.end(), list.begin(), list.end());
		BOOST_CHECK(VerifyStringList(tmpList, list));
	}
	BOOST_AUTO_TEST_CASE(can_erase_by_iterator)
	{
		list.Erase(list.begin());
		BOOST_CHECK(list.GetSize() == 2);
		list.Erase(list.begin(), list.end());
		BOOST_CHECK(list.IsEmpty());
	}
	BOOST_AUTO_TEST_CASE(can_be_cleared)
	{
		list.Clear();
		BOOST_CHECK(list.IsEmpty());
	}
BOOST_AUTO_TEST_SUITE_END()
