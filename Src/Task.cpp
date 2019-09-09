#include "Task.h"

std::ostream& Task::print(std::ostream& out) const
{
	out << getPeriod() << '\t';
	out << getDeadline() << '\t';
	out << getExecutionTime() << '\t';
	out << getResponseTime() << '\t';
	out << getInterference() << '\t';

	return out;
}

Task::Task() :mPeriod(0), mExecutionTime(0), mResponseTime(0), mDeadline(0), mInterference(0)
{
	
}

Task::Task(const unsigned int period, const unsigned int deadline, const unsigned int executionTime) : mPeriod(period), mExecutionTime(executionTime), mResponseTime(0), mDeadline(deadline), mInterference(0)
{
}

Task::Task(const Task& task):mPeriod(task.getPeriod()), mDeadline(task.getDeadline()), mExecutionTime(task.getExecutionTime()), mResponseTime(task.getResponseTime()), mInterference(task.getInterference())
{}


Task& Task::operator=(const Task& task)
{
	if(this != &task){
		mExecutionTime = task.getExecutionTime();
		mPeriod = task.getPeriod();
		mResponseTime = task.getResponseTime();
		mDeadline = task.getDeadline();
		mInterference = task.getInterference();
	}
	return *this;
}


