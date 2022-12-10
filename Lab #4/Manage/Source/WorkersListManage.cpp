#include <iostream>

#include "../WorkersListManage.h"

constexpr uint8_t MAX_SURNAME_SIZE = 25;
constexpr uint8_t MAX_NAME_SIZE = 30;
constexpr uint8_t MAX_PATRONYMIC_SIZE = MAX_NAME_SIZE;

constexpr uint8_t MAX_POSITION_NAME_SIZE = 20;

void WorkersListManager::AddWorker() noexcept
{
	using PCE = PrimitiveConsoleEnterer;

	//Worker worker(PCE::EnterString("Enter surname: ", MAX_SURNAME_SIZE),
	//	PCE::EnterString("Enter name", MAX_SURNAME_SIZE), 
	//	PCE::EnterString("Enter patronymic: ", MAX_PATRONYMIC_SIZE),
	//	PCE::EnterString("Enter position: ", MAX_POSITION_NAME_SIZE),
	//	Date{PCE::EnterUInt16("Day: ", 1, 31)}
}