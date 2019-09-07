#include "TaskSet.h"

unsigned int TaskSet::doInterferenceForN(const unsigned int index, const unsigned int oldInterference) const
{
	unsigned int partialInterference = 0;

	for (unsigned int i = 0; i < index; i++) {

		partialInterference += ceil(((float)oldInterference / mTasks[i].getPeriod())) * mTasks[i].getExecutionTime();
		
	}
		
	return partialInterference;
}


std::ostream& TaskSet::print(std::ostream& out) const
{
	for (unsigned int i = 0; i < mTasks.size(); i++) {
		out << 'J' << i + 1 << '\t';
		out << mTasks[i] << std::endl;
	}
	return out;
	
}

TaskSet::TaskSet(const std::string& filename) {
	
	unsigned int period, execTime, deadline;

	std::string file = TASK_FILE_PATH + filename + ".txt";
	std::ifstream input(file);

	if (input.fail()) {
		std::cout << "Wrong file path! Terminating"<<std::endl;
		exit(-1);
	}

	while(!input.eof()) {

		input >> period >> deadline >>execTime;
		Task task(period,deadline, execTime);
		mTasks.push_back(task);

	}

	input.close();

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

bool TaskSet::toFile(const std::string& filename) const
{
	std::ofstream file(TASK_FILE_PATH + filename + ".txt");

	if (file.fail()) {
		return false;
	}
	file << *this;

	file.close();
	return true;
	
}

void TaskSet::applyDeadlineMonotonic()
{
	std::sort(mTasks.begin(), mTasks.end());
}







