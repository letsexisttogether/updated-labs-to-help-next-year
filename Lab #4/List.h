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
		ListNode(const _NType& data, ListNode<_NType>* prev, ListNode<_NType>* next)
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
		const NodePtr m_DefaultNode{};

	public:
		Iterator() = delete;
		Iterator(NodePtr node)
			: m_CurrentNode(node), m_DefaultNode(node)
		{}

		_LType& GetCurrent() const noexcept
		{
			return m_CurrentNode->Data;
		}
		bool MoveNext() noexcept
		{
			if (m_CurrentNode->Next != m_CurrentNode && m_CurrentNode->Next != m_DefaultNode)
			{
				m_CurrentNode = m_CurrentNode->Next;
				return true;
			}

			return false;
		}
		bool MoveBack() noexcept
		{
			if (m_CurrentNode->Prev != m_CurrentNode && m_CurrentNode->Prev != m_DefaultNode)
			{
				m_CurrentNode = m_CurrentNode->Prev;
				return true;
			}
			return false;
		}
		void Reset() noexcept
		{
			m_CurrentNode = m_DefaultNode;
		}
		
		void operator ++() noexcept
		{
			MoveNext();
		}
		bool operator != (const NodePtr extraNode) const noexcept
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
	List(std::initializer_list<_LType> list)
	{
		for (const _LType& element : list)
		{
			Add(element);
		}
	}

	void Add(const TypeRef m_Value)
	{
		if (!m_Strat)
		{
			m_Strat = new Node(m_Value, nullptr, nullptr);
			m_End = m_Strat;
		}
		else if (m_Strat == m_End)
		{
			m_End = new Node(m_Value, m_Strat, m_Strat);
			m_Strat->Next = m_End;
			m_Strat->Prev = m_End;
		}
		else
		{
			NodePtr newNode = new Node(m_Value, m_End, m_Strat);
			m_End->Next = newNode;
			m_End = newNode;
			m_Strat->Prev = m_End;
		}
		
		++m_Size;
	}
	bool Delete(_LType m_Value)
	{
		if (!m_Strat)
		{
			return false;
		}

		NodePtr temp = m_Strat;
		do
		{
			if (temp->Data == m_Value)
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
		List<_LType>::Iterator iter{ Begin() };
		do
		{
			if (Predicate(iter.GetCurrent(), predValue))
			{
				_LType* const ptr{ &iter.GetCurrent() };
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

	_NODISCARD NodePtr Begin() const noexcept
	{
		return m_Strat;
	}
	_NODISCARD NodePtr End() const noexcept
	{

		return (m_End + sizeof(NodePtr));
	}
};
