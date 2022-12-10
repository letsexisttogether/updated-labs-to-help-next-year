#ifndef DateValidator

#include "../Entities/Date.h"

class DateValidator
{
private:
	Date m_Date;

public:
	DateValidator() = delete;
	DateValidator(const DateValidator&) = delete;
	DateValidator(DateValidator&&) = delete;

	DateValidator(const Date& date);

	~DateValidator() = default;

	bool IsValid() const noexcept;

	DateValidator& operator = (const DateValidator&) = delete;
	DateValidator& operator = (DateValidator&&) = delete;
};

#endif // !DateValidator
