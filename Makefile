BUILD := $(shell git rev-parse --short HEAD)
PROJECTNAME=$(shell basename "$(PWD)")
CC=g++

CFLAGS=-Wall

OBJ_DIR=obj
BIN_DIR=bin

$(shell mkdir -p $(OBJ_DIR) $(BIN_DIR))

default: main.o
	$(CC) $(CFLAGS) $(OBJ_DIR)/* -o $(BIN_DIR)/$(PROJECTNAME)

main.o: task_set.o
	$(CC) $(CFLAGS) main.cpp -c -o $(OBJ_DIR)/main.o

task_set.o: task.o
	$(CC)  $(CFLAGS) src/task_set/task_set.cpp -c -o $(OBJ_DIR)/task_set.o

task.o:
	$(CC)  $(CFLAGS) src/task/task.cpp -c -o $(OBJ_DIR)/task.o

.PHONY: clean
clean:
	$(RM) -rf $(OBJ_DIR) $(BIN_DIR)


