#ifndef LIST
#define LIST

#include <memory>

#include "../Comparators.h"

#ifndef DEBUG && DEBUG == 1
	#define NOT_IMPLEMENTED (throw std::exception("Not implemented"))
#else
	#define NOT_IMPLEMENTED
#endif // !_DEBUG


template <class _LType>
class List
{
private:
	struct ListNode
	{
	public:
		_LType Data{};
		ListNode* Prev{};
		ListNode* Next{};

	public:
		ListNode() = delete;
		ListNode(ListNode&&) = delete;
		ListNode(const ListNode& extraObj) 
			: Data{ extraObj.Data },
			Prev{ new ListNode* (*extraObj.Prev) },
			Next{ new ListNode* (*extraObj.Next) }
		{}

		ListNode(const _LType& data, ListNode* prev, ListNode* next)
			: Data{ data }, Prev{ prev }, Next{ next }
		{}
		ListNode(_LType&& data, ListNode* prev, ListNode* next)
			: Data{ std::move(data) }, Prev{ prev }, Next{ next }
		{}

		~ListNode() = default;

		ListNode& operator = (ListNode&&) = delete;
		ListNode& operator = (const ListNode& extraObj)
		{
			Data = extraObj.Data;
			Prev = new ListNode* (*extraObj.Prev);
			Next = new ListNode* (*extraObj.Next);
		}

		bool operator == (const ListNode &extraObj)
		{
			return (Data == extraObj.Data &&
				Prev == extraObj.Prev && Next == extraObj.Next);
		}
		bool operator != (const ListNode &extraObj)
		{
			return !(*this == extraObj);
		}
	};

	using NodePtr = ListNode*;
	using NodeRef = ListNode&;
	
private:
	NodePtr m_Start{ nullptr };
	NodePtr m_End{ nullptr };
	size_t m_Size{ 0ull };

public:
	template <class _ListGetReturnType>
	class ListIterator
	{
	private:
		NodePtr m_CurrentNode{ nullptr };

	public:
		ListIterator() = delete;
		ListIterator(const ListIterator&) = default;
		ListIterator(ListIterator&& extraObj)
			: m_CurrentNode{ extraObj }
		{
			extraObj.m_CurrentNode = nullptr;
		}
		
		ListIterator(const NodePtr &node)
			: m_CurrentNode{ node }
		{}

		~ListIterator() = default;

		ListIterator& operator =(ListIterator&& extraObj)
		{
			if (m_CurrentNode != extraObj.m_CurrentNode)
			{
				m_CurrentNode = extraObj.m_CurrentNode;
				extraObj.m_CurrentNode = nullptr;
			}
		}
		ListIterator& operator =(const ListIterator& extraObj)
		{
			m_CurrentNode = extraObj.m_CurrentNode;
		}

		ListIterator operator ++(int) noexcept
		{
			Iterator temp{ *this };
			++this;
			return temp;
		}
		ListIterator& operator ++() noexcept
		{
			m_CurrentNode = m_CurrentNode->Next;
			return *this;
		}

		_NODISCARD const _ListGetReturnType operator *() const noexcept
		{
			return m_CurrentNode->Data;
		}

		_NODISCARD bool operator != (const ListIterator& extraObj) const noexcept
		{
			return m_CurrentNode != extraObj.m_CurrentNode;
		}
	};

	using Iterator = ListIterator<_LType&>;
	using ConstIterator = ListIterator<const _LType&>;

public:
	List() = default;
	List(List<_LType>&&) = delete;
	List(const List<_LType> &extraList)
	{
		for (const auto& value : extraList)
		{
			AddBack(value);
		}
	}

	List(std::initializer_list<_LType> list)
	{
		for (const auto& element : list)
		{
			AddBack(element);
		}
	}

	~List()
	{
		while (m_Start && m_Start != m_End->Next)
		{
			delete m_Start->Prev;
			m_Start = m_Start->Next;
		}
		delete m_End;
	}

	void AddBack(const _LType &value)
	{
		if (!m_Start)
		{
			NodePtr phantomNode = new ListNode{ value, nullptr, nullptr };
			m_Start = new ListNode{ value, phantomNode, phantomNode };
			m_End = m_Start;
			phantomNode->Next = m_Start;
			phantomNode->Prev = m_Start;
			
			++m_Size;
			return;
		}

		NodePtr phantomNode = m_End->Next;
		if (m_Start == m_End)
		{
			m_End = new ListNode{ value, m_Start, phantomNode };
			m_Start->Next = m_End;
			phantomNode->Prev = m_End;;
		}
		else
		{
			m_End->Next = new ListNode{ value, m_End, phantomNode };
			m_End = m_End->Next;
			phantomNode->Prev = m_End;
		}
		
		++m_Size;
	}
	void AddFront(const _LType& value)
	{
		NOT_IMPLEMENTED;
	}
	void Emplace(const _LType& value, Iterator iter)
	{		
		NOT_IMPLEMENTED;
	}

	bool Erase(const _LType &value)
	{
		bool eraseResult = false;

		NodePtr taker = m_Start;
		while (taker != m_End->Next)
		{
			ListNode* next{ taker->Next };
			
			if (taker->Data == value)
			{
				EraseNode(taker);
				eraseResult = true;
			}
			
			taker = next;
		}

		return eraseResult;
	}

	_NODISCARD size_t size() const noexcept
	{
		return m_Size;
	}
	_NODISCARD bool isEmpty() const noexcept
	{
		return !!m_Size;
	}

	_NODISCARD ConstIterator begin() const noexcept
	{
		return ConstIterator{ m_Start };
	}
	_NODISCARD ConstIterator end() const noexcept
	{
		return ConstIterator{ m_End->Next };
	}
	_NODISCARD Iterator begin() noexcept
	{
		return Iterator{ m_Start };
	}
	_NODISCARD Iterator end() noexcept
	{
		return Iterator{ m_End->Next };
	}

private:
	void EraseNode(ListNode*& node)
	{
		if (m_Start == m_End)
		{
			delete m_End->Next;
			delete m_Start;
			delete m_End;

			m_Start = m_End = nullptr;
			
			--m_Size;
			return;
		}
		
		node->Prev->Next = node->Next;
		node->Next->Prev = node->Prev;

		if (node == m_Start)
		{
			m_Start = node->Next;
		}
		if (node == m_End)
		{
			m_End = node->Prev;
		}

		delete node;
		--m_Size;
	}
};

#endif // !LIST
