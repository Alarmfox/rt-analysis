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

private:
	std::vector<Task> mTasks;
	unsigned int doInterferenceForN(const unsigned int index, const unsigned int oldInterference)const;

public:
	TaskSet(const std::string& filename = "tasks");

	bool doResponseTimeAnalysis();

	void printSet()const;
	//void sortByPeriod();

};

