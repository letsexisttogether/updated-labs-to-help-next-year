#pragma once

#include <memory>

#include "comparators.h"

template <class _LType>
class List
{
private:
	template <class _NType = _LType>
	struct ListNode
	{
	public:
		_NType Data{};
		ListNode<_NType>* Prev{};
		ListNode<_NType>* Next{};

	public:
		ListNode() = delete;
		ListNode(ListNode&&) = delete;
		ListNode(const ListNode& extraObj) 
			: Data(extraObj.Data), 
			Prev(new ListNode<_NType>* (*extraObj.Prev)),
			Next(new ListNode<_NType>* (*extraObj.Next))
		{}

		ListNode(const _NType& data, ListNode<_NType>* prev, ListNode<_NType>* next)
			: Data(data), Prev(prev), Next(next)
		{}
		ListNode(_NType& data, ListNode<_NType>* prev, ListNode<_NType>* next)
			: Data(std::move(data)), Prev(prev), Next(next)
		{}

		~ListNode() = default;

		ListNode* operator = (ListNode&&) = delete;
		ListNode& operator = (const ListNode& extraObj)
		{
			Data = extraObj.Data;
			Prev = new ListNode<_NType>*(*extraObj.Prev);
			Next = new ListNode<_NType>*(*extraObj.Next);
		}
		bool operator == (const ListNode<_NType>& extraObj)
		{
			return (Data == extraObj.Data &&
				Prev == extraObj.Prev && Next == extraObj.Next);
		}
		bool operator != (const ListNode<_NType>& extraObj)
		{
			return !(*this == extraObj);
		}
	};

	using Node = ListNode<_LType>;
	using NodePtr = ListNode<_LType>*;
	using NodeRef = ListNode<_LType>&;
	
public:
	class Iterator
	{
	private:
		NodePtr m_CurrentNode{};
		const NodePtr m_DefaultNode{};

	public:
		Iterator() = delete;
		Iterator(const NodePtr &node)
			: m_CurrentNode(node), m_DefaultNode(node)
		{}
		~Iterator() = default;

		bool MoveNext() noexcept
		{
			if (m_CurrentNode->Next != nullptr
				&& m_CurrentNode->Next != m_CurrentNode 
				&& m_CurrentNode->Next != m_DefaultNode)
			{
				m_CurrentNode = m_CurrentNode->Next;
				return true;
			}

			return false;
		}

		//bool MoveBack() noexcept
		//{
		//	if (m_CurrentNode->Prev != m_CurrentNode && m_CurrentNode->Prev != m_DefaultNode)
		//	{
		//		m_CurrentNode = m_CurrentNode->Prev;
		//		return true;
		//	}
		//	return false;
		//}

		_LType& GetCurrent() const noexcept
		{
			return m_CurrentNode->Data;
		}
		NodePtr GetCurrentNode() const noexcept
		{
			return m_CurrentNode;
		}
		void Reset() noexcept
		{
			m_CurrentNode = m_DefaultNode;
		}
		
		// TODO: доделать операторы указанные далее
		// _LType& opeartor* (const Iterator& thisObj);
		// 
		_LType& operator *()
		{
			return GetCurrent();
		}
		Iterator& operator ++() noexcept
		{
			MoveNext();
			return *this;
		}
		Iterator operator ++(int) noexcept
		{
			Iterator temp{ *this };
			++this;
			return temp;
		}
		bool operator != (const Iterator& extraObj) const noexcept
		{
			return m_CurrentNode != extraObj.m_CurrentNode
				|| m_DefaultNode != extraObj.m_DefaultNode;
		}
	};

private:
	NodePtr m_Strat{ nullptr };
	NodePtr m_End{ nullptr };
	size_t m_Size{ 0 };

public:
	List() = default;
	List(List<_LType>&&) = delete;
	List(const List<_LType> &extraList)
	{
		NodePtr tempNode = extraList.m_Strat;
		while (tempNode->Next != extraList.m_Strat)
		{
			AddBack(tempNode->Data);
			tempNode = tempNode->Next;
		}
		AddBack(extraList.m_End->Data);

	}

	List(std::initializer_list<_LType> list)
	{
		for (const _LType element : list)
		{
			AddBack(element);
		}
	}

	~List()
	{
		while (m_Size-- > 0)
		{
			delete m_Strat->Prev;
			m_Strat = m_Strat->Next;
		}
	}

	void AddBack(const _LType &value)
	{
		if (CreateStartNode(value))
		{
			return;
		}
		else if (m_Strat == m_End)
		{
			m_End = new Node(value, m_Strat, m_Strat);
			m_Strat->Next = m_End;
			m_Strat->Prev = m_End;
		}
		else
		{
			NodePtr newNode{ new Node(value, m_End, m_Strat) };
			m_End->Next = newNode;
			m_End = newNode;
			m_Strat->Prev = m_End;
		}
		
		++m_Size;
	}
	void AddFront(const _LType& value)
	{
		if (!m_Strat)
		{
			m_Strat = new Node(value, nullptr, nullptr);
			m_End = m_Strat;
		}
	}
	void Emplace(const _LType& value, Iterator iter)
	{		
		NodePtr oldNextNode{ iter.GetCurrentNode()->Next };
		
		iter.GetCurrentNode()->Next = new Node(value, iter.GetCurrentNode(), oldNextNode);
		oldNextNode->Prev = iter.GetCurrentNode()->Next;

	}

	bool Delete(const _LType &value)
	{
		if (!m_Strat)
		{
			return false;
		}

		NodePtr temp = m_Strat;
		do
		{
			if (temp->Data == value)
			{
				if (temp == m_Strat)
				{
					m_Strat = temp->Next;
				}
				else if (temp == m_End)
				{
					m_End = temp->Prev;
				}
				else
				{
					temp->Prev->Next = temp->Next;
					temp->Next->Prev = temp->Prev;
				}
				delete temp;
				--m_Size;
				return true;
			}
			m_Strat = m_Strat->Next;
		} while (m_Strat->Next != temp);

		return false;
	}

	template<class _SType = _LType>
	_LType * const Search(_SType predValue, bool Predicate(const _LType&, const _SType&) 
		= Comps::SimpleComp<_LType>) const noexcept
	{
		Iterator iter{ begin() };
		do
		{
			if (Predicate(iter.GetCurrent(), predValue))
			{
				_LType* const ptr = &iter.GetCurrent();
				return ptr;
			}

		} while (iter.MoveNext());

		return nullptr;
	}

	size_t Size() const noexcept
	{
		return m_Size;
	}
	bool IsEmpty() const noexcept
	{
		return !!m_Size;
	}

	_NODISCARD Iterator begin() noexcept
	{
		return Iterator{ m_Strat };
	}
	_NODISCARD Iterator end() noexcept
	{
		return Iterator{ m_End };
	}

private:
	bool CreateStartNode(const _LType& value)
	{
		if (!m_Strat)
		{
			m_Strat = new Node(value, nullptr, nullptr);
			m_End = m_Strat;
			++m_Size;

			return true;
		}

		return false;
	}
};
