#ifndef CONSOLE_CORRECT_ENTERER
#define CONSOLE_CORRECT_ENTERER

#include <iostream>
#include <limits>

class PrimitiveConsoleEnterer
{
private:
	using int64Limit = std::numeric_limits<int64_t>;
	using int32Limit = std::numeric_limits<int32_t>;
	using uint16Limit = std::numeric_limits<uint16_t>;

	using floatLimit = std::numeric_limits<float>;

	using stringLimit = std::numeric_limits<signed char>;

public:
	static const char* EnterString(const char* message, 
		char maxSymbols = stringLimit::max()) noexcept;
	
	static int64_t EnterInt64(const char* message, 
		int64_t minValue = int64Limit::min(), int64_t maxValue = int64Limit::max()) noexcept;
	
	static int32_t EnterInt32(const char* message, 
		int32_t minValue = int32Limit::min(), int32_t maxValue = int32Limit::max()) noexcept;

	static uint16_t EnterUInt16(const char* message,
		uint16_t minValue = uint16Limit::min(), uint16_t maxValue = uint16Limit::max()) noexcept;

	static float EnterFloat(const char* message,
		float minValue = floatLimit::min(), float maxValue = floatLimit::max()) noexcept;

private:
	template<class _Ty>
	static _Ty DefaultNumberEnter(const char* message, _Ty minValue, _Ty maxValue) noexcept
	{
		while (1)
		{
			std::cout << message;

			_Ty value;
			std::cin >> value;

			if (IsStdFailed() || !IsStdClean())
			{
				std::cout << "The value entered is of a wrong format\n";
				continue;
			}
			if (value < minValue || value > maxValue)
			{
				std::cout << "The value is out of range\n";
				continue;
			}

			std::cout << std::endl;
			return value;
		}
	}
	
	static bool IsStdFailed() noexcept;
	static bool IsStdClean() noexcept;	
};

#endif 
