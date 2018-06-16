#pragma once
#include <string>
#include <memory>
#include <algorithm>
#include <vector>

struct SNode
{
public:
	SNode(const std::string& data, std::unique_ptr<SNode>&& next);
	std::string data;
	std::unique_ptr<SNode> next;
};

class CStringList
{
public:
	CStringList() = default;
	CStringList(const CStringList& list);
	~CStringList();

	CStringList& operator=(const CStringList& list);
	void AddToBegin(const std::string& value);
	std::string GetFront() const;
	size_t GetSize() const;
	bool IsEmpty() const;
	void PrintList(std::ostream& out) const;

	void Clear();
private:
	std::unique_ptr<SNode> m_firstPtr;
	size_t m_size = 0;
};

