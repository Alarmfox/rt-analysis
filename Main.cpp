#include "TaskSet.h"

int main(void) {

	TaskSet set;
	set.applyRateMonotonic();
	
	if (set.doResponseTimeAnalysis()){

		std::cout << "\t******TASK PRINTING******" << std::endl;
		std::cout << "Task\tPer\tDeadln\tWCET\tRT" << std::endl;
		std::cout << set << std::endl;
		if (!set.toFile("results"))
			std::cout << "Could not save on file" << std::endl;
	}else
		std::cout << "Unschedulable set" << std::endl;


	return 0;
}