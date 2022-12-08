#ifndef CONSOLE_CORRECT_ENTERER
#define CONSOLE_CORRECT_ENTERER

#include <iostream>
#include <limits>

class PrimitiveConsoleEnterer
{
private:
	using int64Limit = std::numeric_limits<int64_t>;
	using uint64Limit = std::numeric_limits<uint64_t>;

	using int32Limit = std::numeric_limits<int32_t>;
	using uint32Limit = std::numeric_limits<uint32_t>;

	using floatLimit = std::numeric_limits<float>;

public:
	static int64_t EnterInt64(const char* message, 
		int64_t minValue = int64Limit::min(), int64_t maxValue = int64Limit::max()) noexcept;
	
	static int32_t EnterInt32(const char* message, 
		int32_t minValue = int32Limit::min(), int32_t maxValue = int32Limit::max()) noexcept;

	static uint32_t EnterUInt32(const char* message,
		uint32_t minValue = uint32Limit::min(), uint32_t maxValue = uint32Limit::max()) noexcept;

	static float EnterFloat(const char* message,
		float minValue = floatLimit::min(), float maxValue = floatLimit::max()) noexcept;

private:
	template<class _Ty>
	static _Ty DefaultEnter(const char* message, _Ty minValue, _Ty maxValue) noexcept
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

			return value;
		}
	}
	
	static bool IsStdFailed() noexcept;
	static bool IsStdClean() noexcept;	
};

#endif 
