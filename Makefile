CC = g++
CFLAGS = -std=c++11
INCLUDE_DIRS = -I./include
TARGET_SOURCES = ./src/graph_solver.cpp
TEST_SOURCES = ./src/graph_test.cpp ./src/graph_solver.cpp
EXECUTABLE = graph
TEST_EXECUTABLE = test_graph

.PHONY: all target tests

all: target tests

target: $(EXECUTABLE)

tests: $(TEST_EXECUTABLE)

$(EXECUTABLE): 
	$(CC) $(CFLAGS) $(INCLUDE_DIRS) $(TARGET_SOURCES) -o $(EXECUTABLE)

$(TEST_EXECUTABLE): 
	$(CC) $(CFLAGS) $(INCLUDE_DIRS) -D CATCH_TEST $(TEST_SOURCES) -o $(TEST_EXECUTABLE)

clean:
	rm $(EXECUTABLE) $(TEST_EXECUTABLE)
