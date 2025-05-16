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
#include <iostream>
#include <stack>
#include <queue>

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
		throw std::invalid_argument("Cannot get neighbours. of non-existent vertex.");
	}
	std::vector<T> neighbours;
	for (std::pair<std::string, int> edge : this->adjList[vertex]) {
		neighbours.push_back(edge.first);
	}
	std::sort(neighbours.begin(), neighbours.end());
	return neighbours;
}

template<class T>
void Graph<T>::kruskals(std::vector<std::tuple<T, T, int>>& mst, int& totalCost)
{
	/*std::map<int, std::pair<T, T>> prioList;
	T from, to;
	int weight;
	for (std::pair<T, std::map<T, int>> nodeAdj : this->adjList) {
		from = nodeAdj.first;
		for (std::pair<T, int> edge : nodeAdj.second) {
			std::tie(to, weight) = edge;
			std::cout << "From: " << from << " To: " << to << " Weight: " << std::to_string(weight) << std::endl;
		}
	}*/
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
	if (!this->adjList.contains(from)) {
		throw  std::invalid_argument("Cannot DFS from non-existent vertex.");
	}
	std::map<T, bool> hasVisited;
	std::stack<T> toVisit;
	toVisit.push(from);
	std::string visitOrder;

	while (!toVisit.empty()) {
		T current = toVisit.top();
		toVisit.pop();

		if (!hasVisited[current]) {
			visitOrder.append(current + ",");
			hasVisited[current] = true;

			std::vector<T> neighbours = this->getAllNeighboursTo(current);
			for (auto rItter = neighbours.rbegin(); rItter != neighbours.rend(); rItter++) {
				toVisit.push(*rItter);
			}
		}
	}

	visitOrder.pop_back();

	return visitOrder;
}

template <class T>
std::string Graph<T>::breadthFirstSearch(T from)
{
	if (!this->adjList.contains(from)) {
		throw  std::invalid_argument("Cannot BFS from non-existent vertex.");
	}

	std::map<T, bool> hasVisited;
	std::queue<T> toVisit;
	toVisit.push(from);
	std::string visitOrder;

	while (!toVisit.empty()) {
		T current = toVisit.front();
		toVisit.pop();

		if (!hasVisited[current]) {
			visitOrder.append(current + ",");
			hasVisited[current] = true;

			for (T neighbour : this->getAllNeighboursTo(current)) {
				toVisit.push(neighbour);
			}
		}
	}

	visitOrder.pop_back();

	return visitOrder;
}