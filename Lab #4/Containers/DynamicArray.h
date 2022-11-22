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
	class ConstIterator
	{
	private:
		_DAType* m_Current{};
	
	public:
		ConstIterator() = delete;
		ConstIterator(const ConstIterator& extraObj) = default;
		ConstIterator(ConstIterator&& extraObj)
			: m_Current(extraObj.m_Current)
		{
			if (m_Current != extraObj)
			{
				m_Current = extraObj;
				extraObj.m_Current = nullptr;
			}
		}

		ConstIterator(_DAType *const &valuePtr)
			: m_Current(valuePtr)
		{}

		~ConstIterator() = default;
	
		// TODO: Add two of opeartor = (const Iterator&, Iterator&&) 
		ConstIterator& operator = (const ConstIterator&) noexcept = default;
		ConstIterator& operator = (ConstIterator&& extraObj)
		{
			if (m_Current != extraObj)
			{
				m_Current = extraObj;
				extraObj.m_Current = nullptr;
			}
			return this;
		}
		
		ConstIterator& operator ++() noexcept
		{
			++m_Current;
			return *this;
		}
		ConstIterator operator ++(int) noexcept
		{
			ConstIterator temp{ *this };
			++this;

			return temp;
		}

		_DAType operator *() const noexcept
		{
			return *m_Current;
		}

		bool operator != (const ConstIterator& extraObj) const noexcept
		{
			return m_Current != extraObj.m_Current;
		}
	};

	DynamicArray() 
		: m_Data(new _DAType[m_ReservedSize])
	{}
	DynamicArray(const DynamicArray<_DAType>& extraObj)
		: m_ReservedSize(extraObj.m_ReservedSize), m_Size(extraObj.m_Size),
		m_Data(new _DAType[m_ReservedSize])
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
		m_Data = new _DAType[m_ReservedSize];

		for (size_t i = 0; i < m_Size; i++)
		{
			m_Data[i] = value;
		}
	}
	DynamicArray(std::initializer_list<_DAType> dataList)
		: m_Size(dataList.size())
	{
		RecalculateReservedSize();
		m_Data = new _DAType[m_ReservedSize];

		for (const _DAType& value : dataList)
		{
			AddBack(value);
		}
	}

	~DynamicArray()
	{
		delete[] m_Data;
	}

	void AddBack(const _DAType& value)
	{
		if (m_Size >= m_ReservedSize)
		{
			RecalculateReservedSize();	
			
			_DAType* temp = m_Data;
			m_Data = new _DAType[m_ReservedSize];
			memcpy(m_Data, temp, m_Size * sizeof(_DAType));
			delete[] temp;
		}

		m_Data[m_Size] = value;
		++m_Size;
	}

	_NODISCARD size_t Size() const noexcept
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

	DynamicArray& operator = (const DynamicArray<_DAType>& extraObj) noexcept
	{
		m_ReservedSize = extraObj.m_ReservedSize;
		m_Size = extraObj.m_Size;
		m_Data = new _DAType[m_ReservedSize];
		memcpy(m_Data, extraObj.m_Data, m_Size);
	}
	DynamicArray& operator = (DynamicArray<_DAType>&& extraObj) noexcept
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

	_DAType& operator[] (size_t index) const noexcept
	{
		return m_Data[index];
	}

private:
	void RecalculateReservedSize()
	{
		while (m_Size >= m_ReservedSize)
		{
			m_ReservedSize *= 2;
		}
	}
};

#endif // !DYNAMIC_ARRAY