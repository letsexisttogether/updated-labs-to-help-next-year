#ifndef WORKER
#define WORKER

#include <iostream>
#include <string>

#include "Date.h"

struct Worker
{
private:
	const char* m_Surname;
	const char* m_Name;
	const char* m_Patronymic;
	const char* m_Position;
	Date m_BirthDate;
	uint16_t m_Experience;
	float m_Wage;
	bool m_IsTeacher;

public:
	Worker() = delete;
	Worker(const Worker& extraObj) = default;
	Worker(Worker&& extraObj) = default;
	
	Worker(const char* surname, const char* name, const char* patronymics, const char* position,
		const Date& birthDate, uint16_t experience, float wage, bool isTeacher);

	~Worker() = default;

	const char* surname() const noexcept;
	const char* name() const noexcept;
	const char* patronymic() const noexcept;
	const char* position() const noexcept;
	const Date& birthDate() const noexcept;
	float wage() const noexcept;
	bool isTeacher() const noexcept;

	Worker& operator = (const Worker& worker) = default;
	Worker& operator = (Worker&& worker) = default;

	bool operator == (const Worker& extraObj) const noexcept;

	friend std::ostream& operator << (std::ostream& writeStream, const Worker& thisObj);
};

#endif 