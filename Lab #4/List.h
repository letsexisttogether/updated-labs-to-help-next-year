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
		_NType Data;
		ListNode<_NType>* Prev;
		ListNode<_NType>* Next;

	public:
		ListNode() = delete;
		ListNode(_NType data, ListNode<_NType>* prev, ListNode<_NType>* next)
			: Data(data), Prev(prev), Next(next)
		{}
	};

public:
	using Node = ListNode<_LType>;
	using NodePtr = ListNode<_LType>*;
	using NodeRef = ListNode<_LType>&;
	using ListRef = List<_LType>&;
	using TypeRef = _LType&;
	
	class Iterator
	{
	private:
		NodePtr m_CurrentNode{};
		NodePtr m_DefaultNode{};

	public:
		Iterator() = delete;
		Iterator(NodePtr node)
			: m_CurrentNode(node), m_DefaultNode(node)
		{}

		const _LType& GetCurrent()
		{
			return m_CurrentNode->Data;
		}
		bool MoveNext()
		{
			if (m_CurrentNode->Next != m_CurrentNode && m_CurrentNode->Next != m_DefaultNode)
			{
				m_CurrentNode = m_CurrentNode->Next;
				return true;
			}

			return false;
		}
		bool MoveBack()
		{
			if (m_CurrentNode->Prev != m_CurrentNode && m_CurrentNode->Prev != m_DefaultNode)
			{
				m_CurrentNode = m_CurrentNode->Prev;
				return true;
			}
			return false;
		}
		void GetDefault()
		{
			m_CurrentNode = m_DefaultNode;
		}
		
		void operator ++()
		{
			MoveNext();
		}
		bool operator != (const NodePtr extraNode)
		{
			return (m_CurrentNode != extraNode);
		}
	};

private:
	NodePtr m_Strat{ nullptr };
	NodePtr m_End{ nullptr };
	size_t m_Size{ 0 };

public:
	List() = default;
	List(const ListRef extraList)
	{
		NodePtr tempNode = extraList.m_Strat;
		while (tempNode->Next != extraList.m_Strat)
		{
			Add(tempNode->Data);
			tempNode = tempNode->Next;
		}
		Add(extraList.m_End->Data);

	}

	void Add(_LType value)
	{
		if (!m_Strat)
		{
			m_Strat = new Node(value, nullptr, nullptr);
			m_End = m_Strat;
		}
		else if (m_Strat == m_End)
		{
			m_End = new Node(value, m_Strat, m_Strat);
			m_Strat->Next = m_End;
			m_Strat->Prev = m_End;
		}
		else
		{
			NodePtr newNode = new Node(value, m_End, m_Strat);
			m_End->Next = newNode;
			m_End = newNode;
			m_Strat->Prev = m_End;
		}
		
		++m_Size;
	}
	bool Delete(_LType value)
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
	const TypeRef Search(_SType predValue, bool Predicate(const _LType&, const _SType&) 
		= Comps::SimpleComp<_LType>) const noexcept
	{
		List<_LType>::Iterator iter = Begin();
		do
		{
			if (Predicate(iter.GetCurrent(), predValue))
			{
				return iter.GetCurrent();
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

	_NODISCARD NodePtr Begin() const noexcept
	{
		return m_Strat;
	}
	_NODISCARD NodePtr End() const noexcept
	{

		return (m_End + sizeof(NodePtr));
	}

	void operator = (const ListRef extraList)
	{
		*this = List<_LType>{ extraList };
	}
};
