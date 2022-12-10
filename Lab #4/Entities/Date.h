#ifndef DATE
#define DATE

#include <iostream>

struct Date
{
private:
	uint16_t m_Day;
	uint16_t m_Month;
	uint16_t m_Year;

public:
	Date() = delete;
	Date(const Date& date) = default;
	Date(Date&& date) = default;

	Date(uint16_t day, uint16_t month, uint16_t year);

	~Date() = default;

	uint16_t day() const noexcept;
	uint16_t month() const noexcept;
	uint16_t year() const noexcept;


	Date& operator = (const Date&) = default;
	Date& operator = (Date&&) = default;

	bool operator == (const Date& extraObj) const noexcept;

	friend std::ostream& operator << (std::ostream& writeStream, const Date& thisObj) noexcept;

	friend class DateValidator;
};

#endif // !DATE
