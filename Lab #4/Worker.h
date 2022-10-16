#pragma once

#include <iostream>
#include <string>

#include "date.h"

struct Worker
{
public:
	enum class Position
	{
		Flight_Attendant,
		Pilot,
		Cleaner
	};

public:
	std::string Surname{};
	std::string Name{};
	std::string Partonymic{};
	// Position Pos{};	
	Date BirthDate{};
	uint16_t Experience{};
	float Wage{};
	bool IsTeacher{};

	Worker() = default;
	Worker(const Worker& extraObj)
	{
		Surname = extraObj.Surname;
		Name = extraObj.Name;
		Partonymic = extraObj.Partonymic;
		BirthDate = extraObj.BirthDate;
		Experience = extraObj.Experience;
		Wage = extraObj.Wage;
		IsTeacher = extraObj.IsTeacher;
	}
	Worker(std::string surname, std::string name, std::string patronymics, Date birthDate,
		uint16_t experience, float wage, bool isTeacher) 
		: Surname(surname), Name(name), Partonymic(patronymics), BirthDate(birthDate),
		Experience(experience), Wage(wage), IsTeacher(isTeacher)
	{}

	bool operator == (const Worker& extraObj)
	{
		return (Surname == extraObj.Surname && Name == extraObj.Name
			&& Partonymic == extraObj.Partonymic && BirthDate == extraObj.BirthDate
			&& Experience == extraObj.Experience && Wage == extraObj.Wage
			&& IsTeacher == extraObj.IsTeacher);

	}

	friend std::ostream& operator << (std::ostream& writeStream, const Worker& thisObj)
	{
		writeStream << thisObj.Surname << ' ' << thisObj.Name << ' ' << thisObj.Partonymic 
			<< ' ' << thisObj.BirthDate << ' ' << thisObj.Experience 
			<< thisObj.Wage;
		(thisObj.IsTeacher) ? writeStream << ' ' << "връ" : writeStream << ' ' << "ЭГ";
		return writeStream;
	}
};