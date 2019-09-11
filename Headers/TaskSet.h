#pragma once

#include "Task.h"
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cmath>

#define UNSCHEDULABLE 0

const std::string TASK_FILE_PATH = "data/";

class TaskSet {

	//operator
	friend std::ostream& operator<<(std::ostream& out, const TaskSet& set) { return set.print(out); }

private:
	//member variables
	std::vector<Task> mTasks;
	float mUtilizationFactor;

protected:
	std::ostream& print(std::ostream& out)const;
	std::istream& read(std::istream& in);
public:
	//constructor
	explicit TaskSet() :mUtilizationFactor(0) {};
	//real-time analysis
	bool doResponseTimeAnalysis();
	bool doInterferenceTest();
	bool doLiuLaylandTest();
	//getter
	inline const float getUtilizationFactor()const { return mUtilizationFactor; }
	//user
	bool loadTasks(const std::string& filename);
	bool save(const std::string& filename)const;

private:
	//getters setters
	inline const std::vector<Task> getTasks()const { return mTasks; }
	inline void setTasks(const std::vector<Task>& tasks) { mTasks = tasks; }
	//utils
	void applyDeadlineMonotonic();
	void doProcessorUtilization();
	unsigned int doInterferenceForN(const unsigned int index, const unsigned int oldInterference)const;
	//files
	bool fromFile(const std::string& filename);
	bool toFile(const std::string& filename)const;
};

