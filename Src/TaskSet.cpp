#include "TaskSet.h"

unsigned int TaskSet::doInterferenceForN(const unsigned int index, const unsigned int oldInterference) const
{
	unsigned int partialInterference = 0;

	for (unsigned int i = 0; i < index; i++) {

		partialInterference += ceil(((float)oldInterference / mTasks[i].getPeriod())) * mTasks[i].getExecutionTime();
		//std::cout <<"Partial: "<< partialInterference << std::endl;
		//std::cout <<"Division: "<< ((float)oldInterference / mTasks[i].getPeriod()) << std::endl;
		//std::cout <<"Ceil: "<< ceil((float)(oldInterference / mTasks[i].getPeriod())) << std::endl;
		

	}
		

	return partialInterference;
}

TaskSet::TaskSet(const std::string& filename) {
	
	unsigned int period, execTime;

	std::string file = TASK_FILE_PATH + filename + ".txt";
	std::ifstream input(file);

	if (input.fail()) {
		std::cout << "Wrong file path! Terminating"<<std::endl;
		exit(-1);
	}

	while(!input.eof()) {

		input >> period >> execTime;
		Task task(period, execTime);
		mTasks.push_back(task);

	}

	input.close();

}


bool TaskSet::doResponseTimeAnalysis() {

	unsigned int oldInterference, newInterference;

	for (unsigned int i = 0; i < mTasks.size(); i++) {
		
		newInterference = mTasks[i].getExecutionTime();

		do
		{
			oldInterference = newInterference;
			newInterference = mTasks[i].getExecutionTime() + doInterferenceForN(i, oldInterference);
			if (newInterference > mTasks[i].getPeriod())
				return false;
			else if (newInterference == oldInterference) {
				mTasks[i].setResponseTime(newInterference);
				//std::cout << newInterference << std::endl;
			}
				

		} while (newInterference > oldInterference);
	}
	return true;

}

void TaskSet::printSet() const
{
	std::cout << "\t******TASK PRINTING******"<<std::endl;
	std::cout << "Task\tPer\tWCET\tPRIO\tRT" << std::endl;
		for (unsigned int i = 0; i < mTasks.size(); i++) {
			std::cout << 'J' << i+1 << '\t';
			std::cout << mTasks[i].getPeriod() << '\t';
			std::cout << mTasks[i].getExecutionTime() << '\t';
			std::cout << mTasks[i].getPriority() << '\t';
			std::cout << mTasks[i].getResponseTime() <<std::endl;
	}
		
}
/*
void TaskSet::sortByPeriod()
{
	std::sort(mTasks.begin(), mTasks.end());
}

*/





