#include <string>

#include "../PrimitiveConsoleEnterer.h"

constexpr auto MAX_BUFFER_SIZE = 1000ll;

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

int64_t PrimitiveConsoleEnterer::EnterInt64(const char* message,
	int64_t minValue, int64_t maxValue) noexcept
{
	return DefaultEnter<int64_t>(message, minValue, maxValue);
}

int32_t PrimitiveConsoleEnterer::EnterInt32(const char* message, int32_t minValue, int32_t maxValue) noexcept
{
	return DefaultEnter<int32_t>(message, minValue, maxValue);
}

uint32_t PrimitiveConsoleEnterer::EnterUInt32(const char* message, uint32_t minValue, uint32_t maxValue) noexcept
{
	return DefaultEnter<uint32_t>(message, minValue, maxValue);
}

float PrimitiveConsoleEnterer::EnterFloat(const char* message, float minValue, float maxValue) noexcept
{
	return DefaultEnter<float>(message, minValue, maxValue);
}
