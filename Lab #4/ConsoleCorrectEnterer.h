#ifndef CONSOLE_CORRECT_ENTERER
#define CONSOLE_CORRECT_ENTERER

#include <iostream>

#include "./List.h"

class ConsoleCorrectEnterer
{
public:
	template<class _EType>
	static _EType EnterNumber(const char* message, _EType min, _EType max)
	{
		if (typeid(_EType) != typeid(int32_t)
			&& typeid(_EType) != typeid(float)
			&& typeid(_EType) != typeid(double))
		{
			throw std::invalid_argument("The _EType argument is not a number");
		}

		_EType value{};

		while (1)
		{
			std::cout << message;

			std::cin >> value;
			
			if (typeid(value) != typeid(value))
			{

			}


			if (value < min || value > max)
			{
				std::cout << "The value is out of range. ";
				continue;
			}

			break;
		}

		return value;
	}
};

#endif 
