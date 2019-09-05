#pragma once

#include "Task.h"
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cmath>

const std::string TASK_FILE_PATH = "data/";

class TaskSet {

	//friend
	friend std::ostream& operator<<(std::ostream& out, const TaskSet& set) { return set.print(out); }

private:
	std::vector<Task> mTasks;
	unsigned int doInterferenceForN(const unsigned int index, const unsigned int oldInterference)const;

protected:
	std::ostream& print(std::ostream& out)const;

public:
	//constructor
	TaskSet(const std::string& filename = "tasks");
	//getters & setters
	inline void setTasks(const std::vector<Task>& tasks) { mTasks = tasks; }
	//rta
	bool doResponseTimeAnalysis();
	//utilities
	bool toFile(const std::string& filename)const;
	void applyRateMonotonic();
};

