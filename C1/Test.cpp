#include "Graph.hpp"
#include "DisjointSets.hpp"
#include <string>

int main() {
	/*Graph<std::string> graph;
	graph.addEdge("A", "B", 1);
	graph.addEdge("A", "C", 5);
	graph.addEdge("B", "D", 3);
	graph.addEdge("C", "D", 2);
	graph.addEdge("B", "F", 1);
	graph.addEdge("E", "F", 4);*/

	/*for (std::string neighbour : graph.getAllNeighboursTo("A")) {
		std::cout << neighbour << std::endl;
	}*/

	/*std::cout << graph.depthFirstSearch("A") << std::endl;
	std::cout << graph.breadthFirstSearch("A") << std::endl;*/

	//std::vector<std::tuple<std::string, std::string, int>> result;
	//int cost;
	//graph.kruskals(result, cost);
	//graph.prims(result, cost);

	DisjointSets<std::string> dSet(false, false);

	std::string nodes[10] = { "A", "B", "C", "D", "E", "F", "G", "H", "I", "J" };

	for (std::string node : nodes) {
		dSet.makeSet(node);
	}

	dSet.unionSet("A", "B");
	dSet.unionSet("B", "C");
	dSet.unionSet("D", "C");
	dSet.unionSet("E", "F");
	dSet.unionSet("G", "H");
	dSet.unionSet("I", "E");
	dSet.unionSet("G", "F");

	for (std::string current : nodes) {
		std::cout << current << std::endl;
		std::cout << "Parent: " << dSet.getParent(current) << std::endl;
		std::cout << "Set: " << dSet.findSet(current) << std::endl;
	}
}