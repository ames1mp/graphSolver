/*
	Homework #5:

	Write graph traversal implementations of algorithms.  

	Commands to run:
	Mac OSX: Modify the makefile to include -stdlib=libc++
	EOS: run 'make' from the command line in the root of the project.

	Concepts Covered:
	Graph Algorithms (two most likely, but up to you)
	Pointers
	Includes

*/

#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"
#include "graph_solver.h"
#include <vector>

// An undirected graph.
std::vector<std::vector<int>> undirected_graph_1 {
	{0, 5, 1, 3, -1},
    {5, 0, -1, -1, 2},
    {1, -1, 0, 3, 5},
    {3, -1, 3, 0, 1},
    {-1, 2, 5, 1, 0}
};

// Another undirected graph.
std::vector<std::vector<int>> undirected_graph_2{
	{ 0, 7, 2, 1, 4 },
	{ 7, 0, 6, 2, 8 },
	{ 2, 6, 0, 3, 9 },
	{ 1, 2, 3, 0, 4 },
	{ 4, 8, 9, 4, 0 }
};

// A larger undirected graph.
std::vector<std::vector<int>> undirected_graph_3{
	{ 0, 12, 3, -1, 4, 5, -1 },
	{ 12, 0, -1, 99, 8, 87, -1 },
	{ 3, -1, 0, 7, 44, 9, 1},
	{ -1, 99, 7, 0, 42, 6, 69 },
	{ 4, 8, 44, 42, 0, 2, 3 },
	{ 5, 87, 9, 6, 2, 0, 1 },
	{ -1, -1, 1, 69, 3, 1, 0 }
};

// An undirected graph with a disconnected node.
std::vector<std::vector<int>> undirected_graph_disconnected{
	{ 0, -1, 1, 3, -1 },
	{ -1, 0, -1, -1, -1 },
	{ 1, -1, 0, 3, 5 },
	{ 3, -1, 3, 0, 1 },
	{ -1, -1, 5, 1, 0 }
};

// A directed graph.
std::vector<std::vector<int>> directed_graph_1 {
	{0, 1, 3, 4, -1},
    {5, 0, 12, -1, 7},
    {1, -1, 0, 1, 5},
    {3, 7, 3, 0, 1},
    {-1, 2, 9, -1, 0}
};

//A directed graph with a disconnected node
std::vector<std::vector<int>> directed_graph_disconnected{
	{ 0, -1, -1, -1, -1 },
	{ -1, 0, 12, -1, 7 },
	{ -1, -1, 0, 1, 5 },
	{ -1, 7, 3, 0, 1 },
	{ -1, 2, 9, -1, 0 }
};

// Classes and Methods
// class GraphSolver
// int shortestPathCost(int start, int end)
// std::vector<int> shortestPath(int start, int end)
// std::vector<int> allRoutesShortestPath(int start)
// int mstCost()

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~SHORTEST PATH TESTS~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
TEST_CASE( "Shortest Path from 0 to 4 in undirected_graph_1", "[valid]") {
	auto graph_solver = new GraphSolver(undirected_graph_1);

	// Shortest path from 0 to 4.  
	// Vector contains start and end along 
	// with intermediate nodes.
	std::vector<int> path {0,3,4};
	REQUIRE(graph_solver->shortestPath(0,4) == path);
}

TEST_CASE("Shortest Path from 0 to 6 in undirected_graph_3", "[valid]") {
	auto graph_solver = new GraphSolver(undirected_graph_3);

	// Shortest path from 0 to 6.  
	// Vector contains start and end along 
	// with intermediate nodes.
	std::vector<int> path{ 0,2,6 };
	REQUIRE(graph_solver->shortestPath(0, 6) == path);
}
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~SHORTEST PATH COST TESTS~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
TEST_CASE( "Shortest Path Cost from one node to another undirected_graph_1", "[valid]") {
	auto graph_solver = new GraphSolver(undirected_graph_1);

	REQUIRE(graph_solver->shortestPathCost(0,4) == 4);
}

TEST_CASE("Shortest Path Cost from one node to another undirected_graph_3", "[valid]") {
	auto graph_solver = new GraphSolver(undirected_graph_3);

	REQUIRE(graph_solver->shortestPathCost(0,6) == 4);
}
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~SHORTEST PATH TO ALL OTHER NODES TESTS~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
TEST_CASE( "Shortest Path Cost from one node to all others undirected_graph_1", "[valid]") {
	auto graph_solver = new GraphSolver(undirected_graph_1);

	// Shortest path cost for each node connected to 0.
	std::vector<int> pathCost {0, 5, 1, 3, 4};
	REQUIRE(graph_solver->allRoutesShortestPathCost(0) == pathCost);
}
//graph with a disconnected node returns a vector containing -1s of a length equal to the number of verticies.
TEST_CASE("Shortest Path Cost from one node to all others undirected_graph_disconnected", "[invalid]") {
	auto graph_solver = new GraphSolver(undirected_graph_disconnected);

	// Shortest path cost for each node connected to 0.
	std::vector<int> pathCost{ -1, -1, -1, -1, -1 };
	REQUIRE(graph_solver->allRoutesShortestPathCost(0) == pathCost);
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~MINIMUM SPANNING TREE TESTS~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
TEST_CASE( "Minimum Spanning Tree undirected_graph_1", "[valid]") {
	auto graph_solver = new GraphSolver(undirected_graph_1);

	REQUIRE(graph_solver->mstCost() == 7);
}

TEST_CASE("Minimum Spanning Tree undirected_graph_2", "[valid]") {
	auto graph_solver = new GraphSolver(undirected_graph_2);

	REQUIRE(graph_solver->mstCost() == 9);
}

TEST_CASE("Minimum Spanning Tree undirected_graph_3", "[valid]") {
	auto graph_solver = new GraphSolver(undirected_graph_3);

	REQUIRE(graph_solver->mstCost() == 21);
}

//directed graph should return -1
TEST_CASE("Minimum Spanning Tree directed_graph_1", "[invalid]") {
	auto graph_solver = new GraphSolver(directed_graph_1);

	REQUIRE(graph_solver->mstCost() == -1);
}
//directed graph with disconnected node should return -1
TEST_CASE("Minimum Spanning Tree directed_graph_disconnected", "[invalid]") {
	auto graph_solver = new GraphSolver(directed_graph_disconnected);

	REQUIRE(graph_solver->mstCost() == -1);
}


//undirected graph with disconnected node should return -1
TEST_CASE("Minimum Spanning Tree undirected_graph_diconnected", "[invalid]") {
	auto graph_solver = new GraphSolver(undirected_graph_disconnected);

	REQUIRE(graph_solver->mstCost() == -1);
}