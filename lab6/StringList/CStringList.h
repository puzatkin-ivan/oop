#pragma once
#include <memory>
#include <string>

struct SNode
{
public:
	SNode(const std::string& data, SNode* prev, std::unique_ptr<SNode>&& next);
	std::string data;
	SNode* prev;
	std::unique_ptr<SNode> next;
};

class CIterator
{
	friend class CStringList;
public:
	CIterator() = default;
	CIterator(SNode* node, bool isReverse = false);

	std::string & operator*() const;
	CIterator & operator--();
	CIterator & operator++();
	CIterator operator--(int);
	CIterator operator++(int);
	SNode* operator->() const;

	bool operator==(CIterator const & rhs) const;
	bool operator!=(CIterator const & rhs) const;
private:
	SNode* m_node = nullptr;
	bool m_isReverse = false;
};

class CStringList
{
public:
	CStringList() = default;
	CStringList(const CStringList& list);
	CStringList(CStringList&& list);
	~CStringList();

	size_t GetSize() const;
	bool IsEmpty() const;

	void PushFront(const std::string& data);
	void PushBack(const std::string& data);

	std::string PopFront();
	std::string PopBack();

	void Insert(const CIterator & it, const std::string & data);
	void Insert(const CIterator & it, const CIterator & first, const CIterator & last);

	void Erase(const CIterator& it);
	void Erase(const CIterator& first, const CIterator& last);

	CIterator begin();
	CIterator end();
	CIterator const begin() const;
	CIterator const end() const;

	CIterator const cbegin() const;
	CIterator const cend() const;
	
	CIterator rbegin();
	CIterator rend();
	CIterator const rbegin() const;
	CIterator const rend() const;

	void Clear();
private:
	std::unique_ptr<SNode> m_firstPtr;
	SNode* m_lastPtr = nullptr;
	size_t m_size = 0;
};