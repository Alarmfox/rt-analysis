#pragma once

#include "../task/task.h"
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cmath>

#define UNSCHEDULABLE 0

class TaskSet {

	//operator
	friend std::ostream& operator<<(std::ostream& out, const TaskSet& set) { return set.print(out); }
	friend std::istream& operator>>(std::istream& in, TaskSet& set) { return set.read(in); }

private:
	//member variables
	std::vector<Task> mTasks;
	float mUtilizationFactor;

protected:
	std::ostream& print(std::ostream& out)const;
	std::istream& read(std::istream& in);
public:
	//constructor
	explicit TaskSet() :mUtilizationFactor(0) { };
	//real-time analysis
	bool doResponseTimeAnalysis();
	bool doInterferenceTest();
	bool doLiuLaylandTest();
	//getter
	inline const float getUtilizationFactor()const { return mUtilizationFactor; }
	//user
	void loadFromFile(const std::string& filename);
	void saveToFile(const std::string& filename)const;
	void applyDeadlineMonotonic();
	void applyRateMonotonic();

private:
	//getters setters
	inline const std::vector<Task> getTasks()const { return mTasks; }
	inline void setTasks(const std::vector<Task>& tasks) { mTasks = tasks; }
	//utils
	void doProcessorUtilization();
	unsigned int doInterferenceForN(const unsigned int index, const unsigned int oldInterference)const;
	
};

