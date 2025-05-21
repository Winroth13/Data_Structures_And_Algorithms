#include "Graph.hpp"
#include "Huffman.hpp"
#include <string>

int main() {
	/*Graph<std::string> graph;
	graph.addEdge("A", "B", 1);
	graph.addEdge("A", "C", 4);
	graph.addEdge("B", "D", 7);
	graph.addEdge("C", "D", 10);
	graph.addEdge("B", "F", 1);
	graph.addEdge("E", "F", 4);
	
	std::vector<std::tuple<std::string, std::string>> result;
	int cost;
	graph.dijkstras(result, cost, "A", "D");*/

	Huffman hf;
	hf.build("abcdeabca");
}