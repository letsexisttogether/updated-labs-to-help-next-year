#pragma once

#include <iostream>

class Int32Holder
{
private:
	int32_t m_Value{};

public:
	Int32Holder() = delete;
	Int32Holder(const Int32Holder& extraHolder)
	{
		m_Value = extraHolder.m_Value;
	}
	Int32Holder(Int32Holder&& extraHolder) = delete;

	Int32Holder(int32_t value)
		: m_Value (value)
	{}

	void operator = (const Int32Holder& extraHolder) noexcept
	{
		m_Value = extraHolder.m_Value;
	}
	
	friend std::ostream& operator << (std::ostream& writeStream, const Int32Holder& thisObject)
		noexcept
	{
		writeStream << thisObject.m_Value;
		return writeStream;
	}
};
