#ifndef GRAPH_SOLVER_H
#define GRAPH_SOLVER_H

#include <iostream>

#include <vector>

#define INFIN 99999999;

class GraphSolver {

public:

	GraphSolver(const std::vector<std::vector<int>>& initial_graph);
	
	int shortestPathCost(int start, int end);
	
	std::vector<int> shortestPath(int start, int end);
	
	std::vector<int> allRoutesShortestPathCost(int start);
	
	int mstCost();

private:

	struct Vertex {

		int name;
		std::vector<int> adj;
		int dist;
		bool known;
		Vertex* path;
	};
	
	std::vector<std::vector<int>> graph;

	std::vector<Vertex> verticies;

	int find_min_distance(std::vector<int> key, std::vector<bool> mstSet);
	
	void create_verticies();

	bool is_undirected();

	bool is_disconnected(int node);

	bool has_disconnected_nodes;
	
	bool is_undirected_graph;


};



#endif