#ifndef WORKERS_LIST_MANAGE

#include "../Containers/List.h"
#include "../Entities/Worker.h"
#include "../Extra/PrimitiveConsoleEnterer.h"

//Entity
class WorkersListManager
{
private:
	List<Worker> m_Workers;
	
public:
	WorkersListManager() = default;
	WorkersListManager(const WorkersListManager&) = delete;
	WorkersListManager(WorkersListManager&&) = delete;

	void AddWorker() noexcept;


	WorkersListManager& operator = (const WorkersListManager&) = delete;
	WorkersListManager& operator = (WorkersListManager&&) = delete;
};

#endif // !WORKERS_LIST_MANAGE
