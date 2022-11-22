#ifndef DYNAMIC_ARRAY
#define DYNAMIC_ARRAY

#include <iostream>

template <class _DAType>
class DynamicArray
{
private:
	size_t m_ReservedSize = 25ul;
	size_t m_Size{};
	_DAType* m_Data{};

public:
	DynamicArray() = default;
	DynamicArray(const DynamicArray<_DAType>& extraObj)
		: m_ReservedSize(extraObj.m_ReservedSize), m_Size(extraObj.m_Size),
		m_Data(new _DAType[m_ReservedSize])
	{
		memcpy(m_Data, extraObj.m_Data, m_Size);
	}
	DynamicArray(DynamicArray<_DAType>&& extraObj)
		: m_ReservedSize(extraObj.m_ReservedSize), m_Size(extraObj.m_Size),
		m_Data(extraObj.m_Data)
	{
		extraObj.m_Data = nullptr;
		extraObj.m_Size = 0;
		extraObj.m_ReservedSize = 0;		
	}

	~DynamicArray()
	{
		delete[] m_Data;
	}

	DynamicArray& operator = (const DynamicArray<_DAType>& extraObj)
	{
		m_ReservedSize = extraObj.m_ReservedSize;
		m_Size = extraObj.m_Size;
		m_Data = new _DAType[m_ReservedSize];
		memcpy(m_Data, extraObj.m_Data, m_Size);
	}

	DynamicArray& operator = (DynamicArray<_DAType>&& extraObj)
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
};

#endif // !DYNAMIC_ARRAY