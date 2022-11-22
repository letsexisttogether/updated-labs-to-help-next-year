#pragma once

#include <iostream>

class Date
{
public:
	class DateValidator
	{
	private:
		Date* m_Date{};

	public:
		DateValidator() = delete;
		DateValidator(const DateValidator&) = delete;
		DateValidator(DateValidator&&) = delete;

		DateValidator(Date* date)
			: m_Date(date)
		{}

		~DateValidator() = default;

		bool IsValid() const noexcept
		{
			uint16_t day = m_Date->m_Day;
			uint16_t month = m_Date->m_Month;
			uint16_t year = m_Date->m_Year ;

			if (month != 1 && month != 3 && month != 5 && month != 7 && month != 8
				&& month != 10 && month != 12 && day > 30)
			{
				return false;
			}
			if (month == 2 && !IsLeapYear(year) && day > 28)
			{
				return false;
			}

			return true;
		}

		DateValidator& operator = (const DateValidator&) = delete;
		DateValidator& operator = (DateValidator&&) = delete;

	private:
		bool IsLeapYear(uint16_t year) const noexcept
		{
			if (!(year % 4) || !(year % 100) || !(year % 400))
			{
				return true;
			}

			return false;
		}
	};

private:
	uint16_t m_Day{};
	uint16_t m_Month{};
	uint16_t m_Year{};

public:
	Date() = default;
	Date(uint16_t day, uint16_t month, uint16_t year)
		: m_Day(day), m_Month(month), m_Year(year)
	{
		DateValidator validator(this);
		if (!validator.IsValid())
		{
			throw std::invalid_argument("The date is invalide");
		}
	}
	~Date() = default;
	
	uint16_t Day() const noexcept
	{
		return m_Day;
	}
	uint16_t Month() const noexcept
	{
		return m_Month; 
	}
	uint16_t Year() const noexcept
	{
		return m_Year;
	}
	
	bool operator == (const Date& extraObj)
	{
		return (m_Day == extraObj.m_Day && m_Month == extraObj.m_Month
			&& m_Year == extraObj.m_Year);
	}
	friend std::ostream& operator << (std::ostream & writeStream, const Date & thisObj) noexcept
	{
		writeStream << thisObj.m_Day << '.' << thisObj.m_Month << '.' << thisObj.m_Year;
		return writeStream;
	}
};