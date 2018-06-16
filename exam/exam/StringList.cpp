#include "stdafx.h"
#include "StringList.h"

SNode::SNode(const std::string& data, std::unique_ptr<SNode>&& next)
	:data(data)
	,next(std::move(next))
{
}

CStringList::CStringList(const CStringList& list)
{
	*(this) = list;
}

CStringList::~CStringList()
{
	Clear();
}

CStringList& CStringList::operator=(const CStringList& list)
{
	Clear();
	auto item = list.m_firstPtr.get();
	std::vector<std::string> tmp;
	for (size_t index = 0; index < list.GetSize(); ++index)
	{
		tmp.push_back(item->data);
		item = item->next.get();
	}
	for (size_t index = tmp.size(); index >= 1; --index)
	{
		AddToBegin(tmp[index - 1]);
	}
	return *(this);
}

void CStringList::AddToBegin(const std::string& value)
{
	auto newData = std::make_unique<SNode>(value, std::move(m_firstPtr));
	m_firstPtr = std::move(newData);
	++m_size;
}

std::string CStringList::GetFront() const
{
	if (m_size == 0)
	{
		throw std::logic_error("StringList is empty");
	}
	return m_firstPtr->data;
}

size_t CStringList::GetSize() const
{
	return m_size;
}

bool CStringList::IsEmpty() const
{
	return m_size == 0;
}

void CStringList::PrintList(std::ostream& out) const
{
	auto item = m_firstPtr.get();
	for (size_t index = 0; index < m_size; ++index)
	{
		out << item->data << std::endl;
		item = item->next.get();
	}
}

void CStringList::Clear()
{
	m_size = 0;
	m_firstPtr = nullptr;
}