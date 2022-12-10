#include "../Worker.h"

Worker::Worker(const char* surname, const char* name, const char* patronymics, const char* position,
	const Date& birthDate, uint16_t experience, float wage, bool isTeacher)
	: m_Surname{ surname }, m_Name{ name }, m_Patronymic{ patronymics }, m_Position{ position },
	m_BirthDate{ birthDate }, m_Experience{ experience }, m_Wage{ wage }, m_IsTeacher{ isTeacher }
{}

const char* Worker::surname() const noexcept
{
	return m_Surname;
}
const char* Worker::name() const noexcept
{
	return m_Name;
}
const char* Worker::patronymic() const noexcept
{
	return m_Patronymic;
}
const char* Worker::position() const noexcept
{
	return m_Position;
}
const Date& Worker::birthDate() const noexcept
{
	return m_BirthDate;
}
float Worker::wage() const noexcept
{
	return m_Wage;
}
bool Worker::isTeacher() const noexcept
{
	return m_IsTeacher;
}

bool Worker::operator == (const Worker& extraObj) const noexcept
{
	return (m_Surname == extraObj.m_Surname && m_Name == extraObj.m_Name
		&& m_Patronymic == extraObj.m_Patronymic && m_Position == extraObj.m_Position
		&& m_BirthDate == extraObj.m_BirthDate && m_Experience == extraObj.m_Experience 
		&& m_Wage == extraObj.m_Wage && m_IsTeacher == extraObj.m_IsTeacher);
}

std::ostream& operator << (std::ostream& writeStream, const Worker& thisObj)
{
	writeStream << thisObj.m_Surname << ' ' << thisObj.m_Name << ' ' << thisObj.m_Patronymic
		<< ' ' << thisObj.m_BirthDate << ' ' << thisObj.m_Experience
		<< thisObj.m_Wage;
	writeStream << ((thisObj.m_IsTeacher) ? (" Yes") : (" No"));
	return writeStream;
}