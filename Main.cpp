#include "TaskSet.h"

int main(void) {

	TaskSet set;
	set.applyDeadlineMonotonic();

	if (set.doResponseTimeAnalysis()) {

		std::cout << "\t******TASK PRINTING******" << std::endl;
		std::cout << "Task\tPer\tDeadln\tWCET\tRT" << std::endl;
		std::cout << set << std::endl;
		
	}
	else {
		std::cout << "Unschedulable set" << std::endl;
	}
	if (!set.toFile("results"))
		std::cout << "Could not save on file" << std::endl;

	system("PAUSE");
	return 0;
}