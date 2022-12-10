#ifndef DYNAMIC_ARRAY
#define DYNAMIC_ARRAY

#include <iostream>

template <class _DAType, size_t _reservedSize = 25ul>
class DynamicArray
{
private:
	size_t m_ReservedSize = _reservedSize;
	size_t m_Size{};
	_DAType* m_Data{};

public:
	template <class _DAGetReturnType>
	class DAIterator
	{
	private:
		_DAType* m_Current{};

	public:
		DAIterator() = delete;
		DAIterator(const DAIterator&) noexcept = default;
		DAIterator(DAIterator&& extraObj) noexcept
			: m_Current(extraObj.m_Current)
		{
			extraObj.m_Current = nullptr;
		}

		DAIterator(_DAType* const& ptr)
			: m_Current(ptr)
		{}

		~DAIterator() = default;

		DAIterator& operator ++() noexcept
		{
			++m_Current;
			return *this;
		}
		DAIterator operator ++(int) noexcept
		{
			DAIterator temp{ *this };
			++this;
			return temp;
		}

		bool operator != (const DAIterator& extraObj) const noexcept
		{
			return m_Current != extraObj.m_Current;
		}

		_DAGetReturnType operator *() const noexcept
		{
			return *m_Current;
		}
	};

	using Iterator = DAIterator<_DAType&>;
	using ConstIterator = DAIterator<const _DAType&>;

public:
	DynamicArray()
		: m_Data((_DAType*) ::operator new(m_ReservedSize * sizeof(_DAType)))
	{}
	DynamicArray(const DynamicArray<_DAType>& extraObj)
		: m_ReservedSize(extraObj.m_ReservedSize), m_Size(extraObj.m_Size),
		m_Data((_DAType*) ::operator new(m_ReservedSize * sizeof(_DAType)))

	{
		memcpy(m_Data, extraObj.m_Data, m_Size * _DAType);
	}
	DynamicArray(DynamicArray<_DAType>&& extraObj)
		: m_ReservedSize(extraObj.m_ReservedSize), m_Size(extraObj.m_Size),
		m_Data(extraObj.m_Data)
	{
		extraObj.m_Data = nullptr;
		extraObj.m_Size = 0;
		extraObj.m_ReservedSize = 0;
	}

	DynamicArray(size_t count, _DAType value)
		: m_Size(count)
	{
		RecalculateReservedSize();
		AllocateArrayMemory();

		for (size_t i = 0; i < m_Size; i++)
		{
			m_Data[i] = value;
		}
	}
	DynamicArray(std::initializer_list<_DAType> dataList)
		: m_Size(dataList.size())
	{
		RecalculateReservedSize();
		AllocateArrayMemory();

		for (const _DAType& value : dataList)
		{
			AddBack(value);
		}
	}

	~DynamicArray()
	{
		std::destroy_n(m_Data, m_ReservedSize);
	}

	void AddBack(const _DAType& value)
	{
		ReAllocateArrayMemory();
		new (&m_Data[m_Size++]) _DAType{ value };
	}
	void AddBack(_DAType&& value)
	{
		ReAllocateArrayMemory();
		new (&m_Data[m_Size++]) _DAType{ std::move(value) };
	}

	_NODISCARD size_t size() const noexcept
	{
		return m_Size;
	}

	_NODISCARD ConstIterator begin() const noexcept
	{
		return ConstIterator(&m_Data[0]);
	}
	_NODISCARD ConstIterator end() const noexcept
	{
		return ConstIterator(&m_Data[m_Size]);
	}
	_NODISCARD Iterator begin() noexcept
	{
		return Iterator(&m_Data[0]);
	}
	_NODISCARD Iterator end() noexcept
	{
		return Iterator(&m_Data[m_Size]);
	}

	DynamicArray& operator =(const DynamicArray<_DAType>& extraObj) noexcept
	{
		m_ReservedSize = extraObj.m_ReservedSize;
		m_Size = extraObj.m_Size;
		m_Data = (_DAType*) ::operator new(m_ReservedSize * sizeof(_DAType));
		memcpy(m_Data, extraObj.m_Data, m_Size);
	}
	DynamicArray& operator =(DynamicArray<_DAType>&& extraObj) noexcept
	{
		if (m_Data == extraObj.m_Data)
		{
			return;
		}

		m_ReservedSize = extraObj.m_ReservedSize;
		m_Size = extraObj.m_Size;
		m_Data = extraObj.m_Data;

		extraObj.m_Data = nullptr;
		extraObj.m_Size = 0;
		extraObj.m_ReservedSize = 0;
	}

	_DAType& operator [](size_t index) const noexcept
	{
		return m_Data[index];
	}

private:
	void ReAllocateArrayMemory()
	{
		if (m_Size >= m_ReservedSize)
		{
			_DAType* temp = m_Data;
			const size_t oldReservedSize = m_ReservedSize;

			RecalculateReservedSize();
			AllocateArrayMemory();

			memcpy(m_Data, temp, m_Size * sizeof(_DAType));
			std::destroy_n(temp, oldReservedSize);
		}
	}

	void RecalculateReservedSize()
	{
		while (m_Size >= m_ReservedSize)
		{
			m_ReservedSize *= 2;
		}
	}
	void AllocateArrayMemory()
	{
		m_Data = (_DAType*) ::operator new(m_ReservedSize * sizeof(_DAType));
	}
};

#endif // !DYNAMIC_ARRAY