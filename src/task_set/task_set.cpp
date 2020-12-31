#include "task_set.h"
#include <iostream>
unsigned int TaskSet::doInterferenceForN(const unsigned int index, const unsigned int oldInterference) const{
	unsigned int partialInterference = 0;

	for (unsigned int i = 0; i < index; i++) {
		partialInterference += ceil(((float)oldInterference / mTasks[i].getPeriod())) * mTasks[i].getExecutionTime();	
	}
		
	return partialInterference;
}


std::ostream& TaskSet::print(std::ostream& out) const{
	for (unsigned int i = 0; i < mTasks.size(); i++) {
		out << 'J' << i + 1 << '\t';
		out << mTasks[i] << std::endl;
	}
	return out;
	
}

std::istream& TaskSet::read(std::istream& in){
	if (!mTasks.empty()){
		mTasks.clear();
	}
	while (!in.eof()) {	
		Task task;
		in >> task;
		mTasks.push_back(task);
	}
	
	return in;
}


bool TaskSet::doResponseTimeAnalysis() {


	unsigned int previousResponseTime, nextResponseTime;
	for (unsigned int i = 0; i < mTasks.size(); i++) {	
		nextResponseTime = mTasks[i].getExecutionTime();
		do
		{
			previousResponseTime = nextResponseTime;
			nextResponseTime = mTasks[i].getExecutionTime() + doInterferenceForN(i, previousResponseTime);
			if (nextResponseTime > mTasks[i].getDeadline()) {
				mTasks[i].setResponseTime(UNSCHEDULABLE);
				return false;
			}
				
			else if (nextResponseTime == previousResponseTime) {
				mTasks[i].setResponseTime(nextResponseTime);
				//std::cout << nextResponseTime << std::endl;
			}
				

		} while (nextResponseTime > previousResponseTime);
	}
	return true;

}

bool TaskSet::doInterferenceTest(){
	unsigned int interference;

	for (unsigned int i = 0; i < mTasks.size(); i++) {
		interference = 0;
		for (unsigned int j = 0; j < i; j++) {
			interference += ceil(((float)mTasks[i].getDeadline()/ mTasks[j].getPeriod())) * mTasks[j].getExecutionTime();
		}
		mTasks[i].setInterference(interference);
		
		if (mTasks[i].getInterference() + mTasks[i].getExecutionTime() > mTasks[i].getDeadline()) {
			return false;
		}	
	}
	return true;
}

bool TaskSet::doLiuLaylandTest(){
	int n = mTasks.size();
	return mUtilizationFactor <= (n * exp2(1/n) - 1);
}


void TaskSet::saveToFile(const std::string& filename) const{

	std::ofstream file;
	file.exceptions ( std::ifstream::failbit | std::ifstream::badbit );

	try
	{
		file.open(filename, std::fstream::out);
		file << "Utilization factor " << mUtilizationFactor << std::endl;
		file << *this;

		file.close();
	}
	catch(const std::ios_base::failure& e)
	{
		throw e;
	}
	
}


void TaskSet::loadFromFile(const std::string& filename){
	std::ifstream file;
	file.exceptions ( std::ifstream::failbit | std::ifstream::badbit );
	try
	{
		file.open(filename,std::ios_base::in);
		read(file);
		file.close();
		doProcessorUtilization();
		
	}
	catch(const std::ifstream::failure& e)
	{
		throw e;
	}

}

void TaskSet::applyDeadlineMonotonic(){
	std::sort(mTasks.begin(), mTasks.end());
}

void TaskSet::applyRateMonotonic(){
	std::sort(mTasks.begin(), mTasks.end(), [](const Task& t1, const Task& t2) {
		return t1.getPeriod() < t2.getPeriod();
	});

}

void TaskSet::doProcessorUtilization(){
	mUtilizationFactor = 0;
	for (unsigned int i = 0; i < mTasks.size(); i++)
		mUtilizationFactor += ((float) mTasks[i].getExecutionTime()) / mTasks[i].getDeadline();
}







