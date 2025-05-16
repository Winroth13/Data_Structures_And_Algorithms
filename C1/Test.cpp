#include "Graph.hpp"
#include <string>

int main() {
	Graph<std::string> graph;
	graph.addEdge("A", "B", 1);
	graph.addEdge("A", "C", 1);
	graph.addEdge("B", "D", 1);
	std::cout << graph.depthFirstSearch("A") << std::endl;
	std::cout << graph.breadthFirstSearch("A") << std::endl;
	/*graph.getAllNeighboursTo("A");
	std::vector<std::tuple<std::string, std::string, int>> result;
	int cost;
	graph.kruskals(result, cost);*/
}