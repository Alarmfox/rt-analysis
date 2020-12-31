#pragma once

#include <vector>
#include <istream>
#include <ostream>

class Task {

	//friend
	friend std::ostream& operator<<(std::ostream& out, const Task& task) { return task.print(out); }
	friend std::istream& operator>>(std::istream& in, Task& task) { return task.read(in); }

private:
	unsigned int mPeriod;
	unsigned int mDeadline;
	unsigned int mExecutionTime;
	unsigned int mInterference;
	unsigned int mResponseTime;

protected:
	std::ostream& print(std::ostream& out)const;
	std::istream& read(std::istream& in);
public:
	//constructors
	Task();
	Task(const unsigned int period, const unsigned int deadline,const unsigned int executionTime);
	Task(const Task& task);
	//getters & setters
	inline const unsigned int getPeriod()const { return mPeriod; }
	inline const unsigned int getExecutionTime()const { return mExecutionTime; }
	inline const unsigned int getResponseTime() const { return mResponseTime; }
	inline const unsigned int getDeadline()const { return mDeadline; }
	inline const unsigned int getInterference()const { return mInterference; }
	inline void setInterference(const unsigned int interference) { mInterference = interference; }
	inline void setResponseTime(const unsigned int responseTime) { mResponseTime = responseTime; }
	//operators
	Task& operator = (const Task& task);
	inline bool operator < (const Task& task)const { return mDeadline < task.getDeadline(); }
	inline bool operator > (const Task& task)const { return ! (*this < task); }

	
};
