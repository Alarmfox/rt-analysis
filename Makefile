build: main
	g++ obj/* -o bin/rt-analysis

main: task_set
	g++ main.cpp -c -o obj/main.o

task_set: task
	g++ src/task_set/task_set.cpp -c -o obj/task_set.o

task: 
	g++ src/task/task.cpp -c -o obj/task.o

clean:
	rm -f obj/* bin/*


