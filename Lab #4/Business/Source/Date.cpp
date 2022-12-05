#include <chrono>

#include "../Date.h"

							 /* DateValidator */
class DateValidator
{
private:
	Date m_Date;

public:
	DateValidator() = delete;
	DateValidator(const DateValidator&) = delete;
	DateValidator(DateValidator&&) = delete;

	DateValidator(const Date& date)
		: m_Date{ date }
	{}

	~DateValidator() = default;

	bool IsValid() const noexcept
	{
		uint16_t day = m_Date.m_Day;
		uint16_t month = m_Date.m_Month;
		uint16_t year = m_Date.m_Year;

		bool isComponentsValid = 1 <= day && day <= 31
			&& 1 <= month && month <= 12 
			&& 1990 <= year && year <= 2024;
		bool doesMonthHaveDay = !(month != 1 && month != 3 && month != 5 && month != 7
			&& month != 8 && month != 10 && month != 12 && day > 30);
		
		bool isLeapYear = year % 4 && !(year % 100) && !(year % 400);
		bool isFebDayValid = !((month == 2) && (day > 29 && isLeapYear
			|| day > 28 && !isLeapYear));

		return isComponentsValid && doesMonthHaveDay && isFebDayValid;
	}

	DateValidator& operator = (const DateValidator&) = delete;
	DateValidator& operator = (DateValidator&&) = delete;
};

							 /* Date */
Date::Date(uint16_t day, uint16_t month, uint16_t year)
	: m_Day{ day }, m_Month{ month }, m_Year{ year }
{
	if (DateValidator validator{ *this }; !validator.IsValid())
	{
		throw std::invalid_argument("The date is invalide");
	}
}

uint16_t Date::day() const noexcept
{
	return m_Day;
}
uint16_t Date::month() const noexcept
{
	return m_Month;
}
uint16_t Date::year() const noexcept
{
	return m_Year;
}

bool Date::operator == (const Date& extraObj) const noexcept
{
	return (m_Day == extraObj.m_Day && m_Month == extraObj.m_Month
		&& m_Year == extraObj.m_Year);
}

std::ostream& operator << (std::ostream& writeStream, const Date& thisObj) noexcept
{
	writeStream << thisObj.m_Day << '.' << thisObj.m_Month << '.' << thisObj.m_Year;
	return writeStream;
}
