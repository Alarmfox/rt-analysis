#pragma once

#include <iostream>

class Task {

	//friend
	friend std::ostream& operator<<(std::ostream& out, const Task& task) { return task.print(out); }

private:
	unsigned int mPeriod;
	unsigned int mExecutionTime;
	unsigned int mPriority;
	unsigned int mResponseTime;

protected:
	std::ostream& print(std::ostream& out)const;

public:
	//constructors
	Task();
	Task(const unsigned int period, const unsigned int executionTime);
	//getters & setters
	inline const unsigned int getPeriod()const { return mPeriod; }
	inline const unsigned int getExecutionTime()const { return mExecutionTime; }
	inline const unsigned int getPriority()const { return mPriority; }
	inline const unsigned int getResponseTime() const { return mResponseTime; }
	inline void setPriority(const unsigned int priority) { mPriority = priority; }
	inline void setResponseTime(const unsigned int responseTime) { mResponseTime = responseTime; }
	//operators
	Task& operator = (const Task& task);
	inline bool operator < (const Task& task)const { return mPeriod < task.getPeriod(); }
	//utilities

	
};
