// graph_solver.cpp : Defines the entry point for the console application.
//


#include "graph_solver.h"
#include <algorithm>

//Constructor
GraphSolver::GraphSolver(const std::vector<std::vector<int>>& initial_graph) {
	graph = initial_graph;
	create_verticies();
	is_undirected_graph = is_undirected();
	has_disconnected_nodes = false;
	for (int i = 0; i < graph[0].size(); ++i) {
		if (is_disconnected(i) == true) {
			has_disconnected_nodes = true;
		}
	}
};
//Find the cost of the shortest path between two nodes
int GraphSolver::shortestPathCost(int start, int end) {
	
	int cost = 0;

	std::vector<int> path = shortestPath(start, end);

	for (int i = 0; i < path.size(); ++i) {
		if (path[i] != end) {
			cost += verticies[path[i]].adj[path[i + 1]];
		}		
	}

	return cost;
};

//Find the shortest path between two nodes
std::vector<int> GraphSolver::shortestPath(int start, int end) {
	
	std::vector<int> result;
	
	if (is_disconnected(start)) {
		result.push_back(-2);
		return result;
	}

	if (is_disconnected(end)) {
		result.push_back(-2);
		return result;
	}

	allRoutesShortestPathCost(start);
	
	Vertex current = verticies[end];
	Vertex *&prev = current.path;
	
	result.push_back(end);
	
	bool running = true;
	while (running) {
		result.push_back(prev->name);
		if (prev->name == start) {
			running = false;
			break;
		}
		else {
			current = verticies[prev->name];
			prev = current.path;
		}
	}

	std::reverse(result.begin(), result.end());
	
	return result;
};

//Use Dijkstra's algorithm to find the cost for the shortest route between the start node and all other nodes
std::vector<int> GraphSolver::allRoutesShortestPathCost(int start) {
	//dijkstra's based on code from the text

	if (has_disconnected_nodes) {
		std::vector<int> error;
		for (int i = 0; i < graph[0].size(); ++i) {
			error.push_back(-1);
		}
		return error;
	}
	
	//set initial distances for verticies adjacent to the starting vertex
	for (int i = 0; i < verticies.size(); ++i) {
		if (verticies[start].adj[i] > 0) {
			verticies[i].dist = verticies[start].adj[i];
			verticies[i].path = &verticies[start];
		}
		
	}

	verticies[start].dist = 0;
	verticies[start].known = true;


	bool unknown_exist = true;
	

	while (unknown_exist)
	{
		//find vertex with the smallest distance that is unknown
		Vertex * v = nullptr;
		for (int vert = 0; vert < verticies.size(); ++vert) {
			if (verticies[vert].known == false) {
				v = &verticies[vert];
				break;
			}
		}
		for (int vert = 0; vert < verticies.size(); ++vert) {
			
			if ((verticies[vert].dist > 0) && (verticies[vert].dist < v->dist) && (verticies[vert].known == false)) {
				v = &verticies[vert];
			

		}
		}

		v->known = true;

		Vertex  * w = nullptr;
		for(int i = 0; i < verticies.size(); ++i) {
			if (v->adj[i] > 0) {
				w = &verticies[i];
				if (!w->known) {
					int cvw = v->adj[i];

					if (v->dist + cvw < w->dist) {
						
						//update W
						w->dist = (v->dist + cvw);
						
						//yo dawg, I heard you like pointers, so I put a reference in your pointer so you can put a pointer in your pointer
						// I think . . .
						//actually https://memegenerator.net/instance/42517456/chemistry-dog-i-have-no-idea-why-my-code-works
						w->path = *&v;
					}
				}
			
			}
				
		}	
			
		unknown_exist = false;
		for (int i = 0; i < verticies.size(); ++i) {
				if (verticies[i].known == false) {
					unknown_exist = true;
					break;
				}
				
			}
	}

	std::vector<int> costs;

	for (int i = 0; i < verticies.size(); ++i) {
		int distance = verticies[i].dist;
		costs.push_back(distance);
	}
	
	return costs;
};

//helper function for Prim's. Sets the min distance for nodes adjacent to known nodes.
int GraphSolver::find_min_distance(std::vector<int> key, std::vector<bool> mstSet) {
	int min = INFIN;
	int vertex_name = 0;
	
	for (int i = 0; i < key.size(); ++i) {
		if (mstSet[i] == false && key[i] < min) {
			min = key[i];
			vertex_name = i;
		}
	}

	return vertex_name;
};

//Use Prim's algorithm to find the cost of the MST
int GraphSolver::mstCost() {
	//Prim's based on code from: http://www.geeksforgeeks.org/greedy-algorithms-set-5-prims-minimum-spanning-tree-mst-2/
	
	if (has_disconnected_nodes) {
		return -1;
	}
	if (is_undirected_graph == false) {
		return -1;
	}
	
	int cost = 0;
	std::vector<int> key;
	std::vector<int> parent;
	std::vector<bool> mstSet;
	
	for (int i = 0; i < verticies.size(); ++i) {
		key.push_back(999999999);
		mstSet.push_back(false);
		parent.push_back(0);
	}

	key[0] = 0;
	parent[0] = -1;

	
	for (int i = 0; i < verticies.size() - 1; ++i) {

		int u = find_min_distance(key, mstSet);
		
		mstSet[u] = true;
		
		for (int i = 0; i < verticies.size(); ++i) {
			if (graph[u][i] > 0 && mstSet[i] == false && graph[u][i] < key[i]) {
				parent[i] = u;
				key[i] = graph[u][i];
			}
		}		
	}

	
	for (int i = 1; i < verticies.size(); i++) { 
		cost += graph[i][parent[i]];
	}	

	return cost;
};

// determine if the graph is undirected
bool GraphSolver::is_undirected() {
	
	int len = graph[0].size();
	
	for (int row = 0; row < len; ++row) {
		for (int col = 0; col < len; ++col) {
			if (graph[row][col] != graph[col][row]) {
				return false;
			}
		}
	
	}

	return true;
};

//populate the vector of verticies with verticies created from the adjacency matrix. Used by the constructor.
void GraphSolver::create_verticies() {

	int len = graph[0].size();

	for (int row = 0; row < len; ++row) {
			Vertex v;
			v.name = row;
			v.dist = INFIN;
			v.known = false;
			v.path = nullptr;

			for (int col = 0; col < len; ++col) {
				v.adj.push_back(graph[row][col]);
			}

			verticies.push_back(v);		
	}

};

//determine whether the passed in node is disconnected
bool GraphSolver::is_disconnected(int node) {

	int len = graph[0].size();
	bool has_incoming_edges = false;
	bool has_outgoing_edges = false;


		for (int row = 0; row < len; ++row) {
			for (int col = 0; col < len; ++col) {

				if (graph[row][node] > 0) {
					has_incoming_edges = true;
				}

			}
		}

		for (int row = 0; row < len; ++row) {
			for (int col = 0; col < len; ++col) {

				if (graph[node][col] > 0) {
					has_outgoing_edges = true;
				}

			}
		}

		if (has_incoming_edges == false && has_outgoing_edges == false) {
			return true;
		}

		return false;
};

//Driver
int main()
{
	
	std::vector<std::vector<int>> undirected_graph_1{
		{ 0, 5, 1, 3, -1 },
		{ 5, 0, -1, -1, 2 },
		{ 1, -1, 0, 3, 5 },
		{ 3, -1, 3, 0, 1 },
		{ -1, 2, 5, 1, 0 }
	};

	std::vector<std::vector<int>> directed_graph_1{
		{ 0, 1, 3, 4, -1 },
		{ 5, 0, 12, -1, 7 },
		{ 1, -1, 0, 1, 5 },
		{ 3, 7, 3, 0, 1 },
		{ -1, 2, 9, -1, 0 }
	};

	std::vector<std::vector<int>> directed_graph_2{
		{ 0, -1, -1, -1, -1 },
		{ -1, 0, 12, -1, 7 },
		{ -1, -1, 0, 1, 5 },
		{ -1, 7, 3, 0, 1 },
		{ -1, 2, 9, -1, 0 }
	};

	std::vector<std::vector<int>> undirected_graph_2{
		{ 0, 2, 0, 6, 0 },
		{ 2, 0, 3, 8, 5 },
		{ 0, 3, 0, 0, 7 },
		{ 6, 8, 0, 0, 9 },
		{ 0, 5, 7, 9, 0 },
	};
	
	std::vector<std::vector<int>> undirected_graph_5{
		{ 0, 7, 2, 1, 4 },
		{ 7, 0, 6, 2, 8 },
		{ 2, 6, 0, 3, 9 },
		{ 1, 2, 3, 0, 4 },
		{ 4, 8, 9, 4, 0 }
	};

	std::vector<std::vector<int>> undirected_graph_large{
		{ 0, 12, 3, -1, 4, 5, -1 },
		{ 12, 0, -1, 99, 8, 87, -1 },
		{ 3, -1, 0, 7, 44, 9, 1 },
		{ -1, 99, 7, 0, 42, 6, 69 },
		{ 4, 8, 44, 42, 0, 2, 3 },
		{ 5, 87, 9, 6, 2, 0, 1 },
		{ -1, -1, 1, 69, 3, 1, 0 }
	};
	auto graph = new GraphSolver(undirected_graph_large);
	auto graph2 = new GraphSolver(directed_graph_1);
	auto graph3 = new GraphSolver(directed_graph_2);

	std::vector<int> out;
	//out = graph->allRoutesShortestPathCost(3);

	int cost;
	cost = graph->mstCost();
	
	for (int i : out) {
		std::cout << i << ", ";
	}
	

	std::cout << cost;

	
	//graph->shortestPath(1, 0);
	//std::cout << std::endl;
	//graph2->shortestPath(2, 0);
	//std::cout << std::endl;
	//graph3->shortestPath(0, 0);
	

	return 0;
}
 

