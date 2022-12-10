#include <string>

#include "../PrimitiveConsoleEnterer.h"

constexpr size_t MAX_BUFFER_SIZE = 1000ll;

const char* PrimitiveConsoleEnterer::EnterString(const char* message, char maxSymbols) noexcept
{
	while (1)
	{
		std::cout << message;

		const uint8_t stringSize = maxSymbols + 1;

		char* str = new char[stringSize];
		std::cin.getline(str, stringSize);

		for (uint8_t i = 0; i < stringSize; i++)
		{
			if (str[i] == '\0')
			{
				char* result = new char[i + 1];
				memcpy(result, str, i + 1);
				delete str;

				std::cout << std::endl;
				return result;
			}
		}
	}
}

int64_t PrimitiveConsoleEnterer::EnterInt64(const char* message,
	int64_t minValue, int64_t maxValue) noexcept
{
	return DefaultNumberEnter<int64_t>(message, minValue, maxValue);
}

int32_t PrimitiveConsoleEnterer::EnterInt32(const char* message, int32_t minValue, int32_t maxValue) noexcept
{
	return DefaultNumberEnter<int32_t>(message, minValue, maxValue);
}

uint16_t PrimitiveConsoleEnterer::EnterUInt16(const char* message, uint16_t minValue, uint16_t maxValue) noexcept
{
	return DefaultNumberEnter<uint16_t>(message, minValue, maxValue);
}

float PrimitiveConsoleEnterer::EnterFloat(const char* message, float minValue, float maxValue) noexcept
{
	return DefaultNumberEnter<float>(message, minValue, maxValue);
}


bool PrimitiveConsoleEnterer::IsStdFailed() noexcept
{
	if (std::cin.fail())
	{
		std::cin.clear();
		std::cin.ignore(MAX_BUFFER_SIZE, '\n');

		return true;
	}

	return false;
}

bool PrimitiveConsoleEnterer::IsStdClean() noexcept
{
	char buffer[MAX_BUFFER_SIZE]{};
	
	std::cin.getline(buffer, MAX_BUFFER_SIZE);
	for (size_t i = 0; i < MAX_BUFFER_SIZE; i++)
	{
		if (buffer[i] != '\0')
		{
			return false;
		}
	}

	return true;
}