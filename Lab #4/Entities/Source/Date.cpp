#include <chrono>

#include "../Date.h"
#include "../../Extra/DateValidator.h"

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