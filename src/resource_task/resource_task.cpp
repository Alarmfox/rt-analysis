#include "resource_task.h"

std::ostream& ResourceTask::print(std::ostream& out) const
{
	Task::print(out);
	out << mBlockingTime << '\t';
	for (unsigned int i = 0; i < mResourceSemaphores.size(); i++)
		out << mResourceSemaphores[i].getValue()<< '\t';
	return out;
}

ResourceTask::ResourceTask():Task(), mBlockingTime(0)
{
}

ResourceTask::ResourceTask(const unsigned int period, const unsigned int deadline, const unsigned int executionTime, std::vector<Semaphore>& semaphores):Task(period, deadline, executionTime), mBlockingTime(0)
{
}

ResourceTask::ResourceTask(const ResourceTask& task):Task(task), mResourceSemaphores(task.getResourceSemaphores()), mBlockingTime(task.getBlockingTime())
{
}

ResourceTask& ResourceTask::operator=(const ResourceTask& task)
{
	if (this != &task) {
		Task::operator=(task);
		mBlockingTime = task.getBlockingTime();
		mResourceSemaphores = task.getResourceSemaphores();
	}

	return *this;
}
