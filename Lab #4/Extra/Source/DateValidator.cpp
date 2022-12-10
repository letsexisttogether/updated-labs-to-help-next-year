#include "../DateValidator.h"

DateValidator::DateValidator(const Date& date)
	: m_Date{ date }
{}

bool DateValidator::IsValid() const noexcept
{
	uint16_t day = m_Date.m_Day;
	uint16_t month = m_Date.m_Month;
	uint16_t year = m_Date.m_Year;

	bool areComponentsValid = 1 <= day && day <= 31
		&& 1 <= month && month <= 12
		&& 1990 <= year && year <= 2024;
	bool doesMonthHaveDay = !(month != 1 && month != 3 && month != 5 && month != 7
		&& month != 8 && month != 10 && month != 12 && day > 30);

	bool isLeapYear = year % 4 && !(year % 100) && !(year % 400);
	bool isFebDayValid = !((month == 2) && (day > 29 && isLeapYear
		|| day > 28 && !isLeapYear));

	return areComponentsValid && doesMonthHaveDay && isFebDayValid;
}