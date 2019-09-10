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

	//friend
	friend std::ostream& operator<<(std::ostream& out, const TaskSet& set) { return set.print(out); }

private:
	std::vector<Task> mTasks;
	float mUtilizationFactor;
	bool mFailed;
	unsigned int doInterferenceForN(const unsigned int index, const unsigned int oldInterference)const;
	void applyDeadlineMonotonic();
	void doProcessorUtilization();
	void fromFile(const std::string& filename);

protected:
	std::ostream& print(std::ostream& out)const;
	std::istream& read(std::istream& in);
public:
	//constructor
	explicit TaskSet(const std::string& filename = "tasks");
	//getters & setters
	inline const std::vector<Task> getTasks()const { return mTasks; }
	inline const float getUtilizationFactor()const { return mUtilizationFactor; }
	inline const bool getReadingStatus()const { return mFailed; }
	inline void setTasks(const std::vector<Task>& tasks) { mTasks = tasks; }
	//real-time analysis
	bool doResponseTimeAnalysis();
	bool doInterferenceTest();
	bool doLiuLaylandTest();
	//utilities
	bool toFile(const std::string& filename)const;
	bool readSetFromFile(const std::string& filename);
	
};

