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

std::istream& TaskSet::read(std::istream& in)
{
	unsigned int period, execTime, deadline;
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

bool TaskSet::doInterferenceTest()
{
	unsigned int interference;

	for (unsigned int i = 0; i < mTasks.size(); i++) {
		interference = 0;
		for (int j = 0; j < i; j++) {
			interference += ceil(((float)mTasks[i].getDeadline()/ mTasks[j].getPeriod())) * mTasks[j].getExecutionTime();
		}
		//std::cout << "Interference for task " << i+1 << ": " << interference << std::endl;
		mTasks[i].setInterference(interference);
		
		if (mTasks[i].getInterference() + mTasks[i].getExecutionTime() > mTasks[i].getDeadline()) {
			return false;
		}	
	}
	return true;
}

bool TaskSet::doLiuLaylandTest()
{
	int n = mTasks.size();
	return mUtilizationFactor <= (n * exp2(1/n) - 1);
}

bool TaskSet::init(const std::string& filename)
{

	return true;
}

bool TaskSet::loadTasks(const std::string& filename)
{
	if (!mTasks.empty())
		mTasks.clear();
	if (filename.empty())
		return false;

	fromFile(filename);
	applyDeadlineMonotonic();
	doProcessorUtilization();

	return true;
	
}

bool TaskSet::save(const std::string& filename) const
{
	return toFile(filename);
}

bool TaskSet::toFile(const std::string& filename) const
{
	std::ofstream file(TASK_FILE_PATH + filename + ".txt");

	if (file.fail()) {
		return false;
	}
	file << "Utilization factor " << mUtilizationFactor << std::endl;
	file << *this;

	file.close();
	return true;
	
}


bool TaskSet::fromFile(const std::string& filename)
{
	std::string file = TASK_FILE_PATH + filename + ".txt";
	std::ifstream input(file);

	if (input.fail()) {
		return false;
	
	}
	read(input);
	input.close();

	return true;
}

void TaskSet::applyDeadlineMonotonic()
{
	std::sort(mTasks.begin(), mTasks.end());
}

void TaskSet::doProcessorUtilization()
{
	mUtilizationFactor = 0;
	for (unsigned int i = 0; i < mTasks.size(); i++)
		mUtilizationFactor += ((float) mTasks[i].getExecutionTime()) / mTasks[i].getDeadline();
}







