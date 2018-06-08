#include "stdafx.h"
#include "CStringList.h"
#include <cassert>

SNode::SNode(const std::string& data, SNode* prev, std::unique_ptr<SNode>&& next)
	:data(data)
	,prev(prev)
	,next(std::move(next))
{
}

CIterator::CIterator(SNode* node, bool isReverse)
	:m_node(node)
	,m_isReverse(isReverse)
{
}

bool CIterator::operator==(const CIterator& rhs) const
{
	return (m_node == rhs.m_node) && (m_isReverse == rhs.m_isReverse);
}

bool CIterator::operator!=(CIterator const & rhs) const
{
	return !(*this == rhs);
}

CIterator& CIterator::operator--()
{
	m_node = (m_isReverse) ? m_node->next.get() : m_node->prev;
	return *this;
}

CIterator& CIterator::operator++()
{
	m_node = m_isReverse ? m_node->prev : m_node->next.get();
	return *this;
}

CIterator CIterator::operator--(int)
{
	auto temp = *this;
	--*this;
	return temp;
}

CIterator CIterator::operator++(int)
{
	auto temp = *this;
	++*this;
	return temp;
}

std::string & CIterator::operator*() const
{
	return m_node->data;
}

SNode* CIterator::operator->() const
{
	return m_node;
}

CStringList::CStringList(const CStringList& list)
{
	Insert(end(), list.begin(), list.end());
}

CStringList::CStringList(CStringList&& list)
{
	m_size = list.m_size;
	m_firstPtr = std::move(list.m_firstPtr);
	m_lastPtr = list.m_lastPtr;
	list.m_lastPtr = nullptr;
	list.m_size = 0;
}

CStringList::~CStringList()
{
	Clear();
}

size_t CStringList::GetSize() const
{
	return m_size;
}

bool CStringList::IsEmpty() const
{
	return (m_size == 0);
}

void CStringList::PushFront(const std::string& data)
{
	auto newPtr = std::make_unique<SNode>(data, nullptr, std::move(m_firstPtr));
	if (newPtr->next)
	{
		newPtr->next->prev = newPtr.get();
	}
	else
	{
		m_lastPtr = newPtr.get();
	}
	m_firstPtr = std::move(newPtr);
	++m_size;
}

void CStringList::PushBack(const std::string& data)
{
	auto newPtr = std::make_unique<SNode>(data, m_lastPtr, nullptr);
	auto* newLastPtr = newPtr.get();

	if (m_lastPtr)
	{
		m_lastPtr->next = std::move(newPtr);
	}
	else
	{
		m_firstPtr = std::move(newPtr);
	}
	m_lastPtr = newLastPtr;
	++m_size;
}

std::string CStringList::PopFront()
{
	auto data = m_firstPtr->data;
	Erase(begin());
	return data;
}

std::string CStringList::PopBack()
{
	auto data = m_lastPtr->data;
	Erase(rbegin());
	return data;
}

void CStringList::Insert(const CIterator & it, const std::string & data)
{
	if (it == begin())
	{
		PushFront(data);
	}
	else if (it == end())
	{
		PushBack(data);
	}
	else
	{
		auto node = std::make_unique<SNode>(data, it->prev, std::move(it->prev->next));
		it->prev = node.get();
		node->prev->next = std::move(node);
		++m_size;
	}
}

void CStringList::Insert(const CIterator & it, const CIterator & first, const CIterator & last)
{
	for (auto currIt = first; currIt != last; ++currIt)
	{
		Insert(it, *currIt);
	}
}

void CStringList::Erase(const CIterator& it)
{
	if (GetSize() == 0)
	{
		throw std::out_of_range("String list is already empty");
	}
	if (GetSize() == 1)
	{
		m_firstPtr = nullptr;
		m_lastPtr  = nullptr;
		m_size = 0;
		return;
	}
	if (it == begin())
	{
		m_firstPtr = std::move(m_firstPtr->next);
		m_firstPtr->prev = nullptr;
	}
	else if (it.m_node == m_lastPtr)
	{
		m_lastPtr = it->prev;
		m_lastPtr->next = nullptr;
	}
	else
	{
		it->next->prev = it->prev;
		it->prev->next = std::move(it->next);
	}
	--m_size;
}

void CStringList::Erase(const CIterator& first, const CIterator& last)
{
	for (auto it = first; it != last; ++it)
	{
		Erase(it);
	}
}

CIterator CStringList::begin()
{
	return CIterator(m_firstPtr.get());
}

CIterator CStringList::end()
{
	if (IsEmpty())
	{
		return begin();
	}
	return CIterator(m_lastPtr->next.get());
}

CIterator const CStringList::begin() const
{
	return CIterator(m_firstPtr.get());
}

CIterator const CStringList::end() const
{
	if (IsEmpty())
	{
		return begin();
	}
	return CIterator(m_lastPtr->next.get());
}


CIterator const CStringList::cbegin() const
{
	return begin();
}

CIterator const CStringList::cend() const
{
	return end();
}

CIterator CStringList::rbegin()
{
	return CIterator(m_lastPtr, true);
}

CIterator CStringList::rend()
{
	return (m_size == 0) ? rbegin() : CIterator(m_firstPtr.get(), true);
}

CIterator const CStringList::rbegin() const
{
	return CIterator(m_firstPtr.get(), true);
}

CIterator const CStringList::rend() const
{
	if (IsEmpty())
	{
		return rbegin();
	}
	return CIterator(m_lastPtr->next.get(), true);
}

void CStringList::Clear()
{
	m_lastPtr = nullptr;
	m_firstPtr = nullptr;
	m_size = 0;
}