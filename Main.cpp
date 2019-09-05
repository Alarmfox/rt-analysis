#include "TaskSet.h"

int main(void) {

	TaskSet set;

	if (set.doResponseTimeAnalysis())
		set.printSet();
	else std::cout << "Unschedulable set" << std::endl;

	return 0;
}