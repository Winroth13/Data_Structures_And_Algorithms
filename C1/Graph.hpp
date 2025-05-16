#ifndef GRAPH_H
#define GRAPH_H
#include <utility>
#include <vector>
#include <climits>
#include <tuple>
#include <string>
#include <map>
#include <stdexcept>
#include <algorithm>

const int INFINIT_COST = INT_MAX;

template <class T>
class Graph
{
private:
	// for you decide
	std::map<T, std::map<T, int>> adjList;
	int nrOfVertices;
	int nrOfEdges;;
public:
	Graph();
	virtual ~Graph() = default;
	Graph(const Graph& other) = delete;
	Graph& operator=(const Graph& other) = delete;
	void addVertex(T theNode);
	void addEdge(T from, T to, int weight = 0);
	std::vector<T> getAllNeighboursTo(T vertex);
	int getNrOfVertices() const;
	int getNrOfEdges() const;
	void kruskals(std::vector<std::tuple<T, T, int>>& mst, int& totalCost);
	void prims(std::vector<std::tuple<T, T, int>>& mst, int& totalCost);
	void readFromFile(std::string file);

	std::string depthFirstSearch(T from);
	std::string breadthFirstSearch(T from);
};


#endif

template<class T>
Graph<T>::Graph() : nrOfVertices(0), nrOfEdges(0) {}

template<class T>
void Graph<T>::addVertex(T theNode)
{
	if (this->adjList.contains(theNode)) {
		throw std::invalid_argument("Cannot add already existing vertex.");
	}
	this->adjList[theNode] = std::map<T, int>();
	this->nrOfVertices++;
}

template<class T>
void Graph<T>::addEdge(T from, T to, int weight)
{
	if (!this->adjList.contains(from)) {
		addVertex(from);
	}
	if (!this->adjList.contains(to)) {
		addVertex(to);
	}
	this->adjList[from][to] = weight;
	this->adjList[to][from] = weight;
	this->nrOfEdges += 2;
}

template<class T>
std::vector<T> Graph<T>::getAllNeighboursTo(T vertex)
{
	if (!this->adjList.contains(vertex)) {
		throw std::invalid_argument("Cannot get neibours of non-exostent vertex.");
	}
	std::vector<T> neighbours;
	for (auto edge : this->adjList[vertex]) {
		neighbours.push_back(edge.first);
	}
	std::sort(neighbours.begin(), neighbours.end());
	return neighbours;
}

template<class T>
void Graph<T>::kruskals(std::vector<std::tuple<T, T, int>>& mst, int& totalCost)
{

}

template<class T>
void Graph<T>::prims(std::vector<std::tuple<T, T, int>>& mst, int& totalCost)
{

}

template<class T>
int Graph<T>::getNrOfVertices() const
{
	return this->nrOfVertices;
}

template<class T>
int Graph<T>::getNrOfEdges() const
{
	return this->nrOfEdges;
}

template <class T>
std::string Graph<T>::depthFirstSearch(T from)
{
	return "";
}
template <class T>
std::string Graph<T>::breadthFirstSearch(T from)
{
	return "";
}