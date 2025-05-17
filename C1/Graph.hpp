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
#include "DisjointSets.hpp"

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
	for (const auto& [otherVertex, weight] : this->adjList[vertex]) { // Type is std::pair<T, int>.
		neighbours.push_back(otherVertex);
	}
	std::sort(neighbours.begin(), neighbours.end());
	return neighbours;
}

template<class T>
void Graph<T>::kruskals(std::vector<std::tuple<T, T, int>>& mst, int& totalCost)
{
	DisjointSets<T> dSets(true, true);
	std::multimap<int, std::pair<T, T>> prioList;
	std::map<std::pair<T, T>, bool> hasIndluded;
	totalCost = 0;

	// Makes the nodes into sets and adds unique edges to prioList.
	for (const auto& [from, paths] : this->adjList) { // Type is std::pair<T, std::pair<T, int>>.
		dSets.makeSet(from);
		for (const auto& [to, weight] : paths) { // Type is std::pair<T, int>.
			std::pair<T, T> reversePair = std::make_pair(to, from);
			if (!hasIndluded[reversePair]) {
				std::pair<int, std::pair<T, T>> newNeighbour = std::make_pair(weight, std::make_pair(from, to));
				prioList.insert(newNeighbour);
				std::pair<T, T> correctPair = std::make_pair(from, to);
				hasIndluded[correctPair] = true;
			}
		}
	}

	// Includes cheapest edges between sets.
	// Maps are already sorted.
	for (const auto& [weight, edge] : prioList) { // Type is std::pair<int, std::pair<T, T>>.
		const auto& [from, to] = edge; // Type is std::pair<T, T>.
		if (dSets.findSet(from) != dSets.findSet(to)) {
			dSets.unionSet(from, to);
			std::tuple<T, T, int> newEdge = std::make_tuple(from, to, weight);
			mst.push_back(newEdge);
			totalCost += weight;
			if (mst.size() == this->nrOfVertices - 1) {
				break;
			}
		}
	}
}

template<class T>
void Graph<T>::prims(std::vector<std::tuple<T, T, int>>& mst, int& totalCost)
{
	std::multimap<int, std::pair<T, T>> prioList;
	std::map<T, bool> hasIncluded;
	totalCost = 0;

	// Starting neighbours.
	auto& [start, neighbours] = *this->adjList.begin(); // Type is std::pair<T, std::map<T, int>>.
	hasIncluded[start] = true;
	for (const auto& [to, weight] : neighbours) {
		std::pair<int, std::pair<T, T>> newNeighbour = std::make_pair(weight, std::make_pair(start, to));
		prioList.insert(newNeighbour);
	}

	while (hasIncluded.size() < this->nrOfEdges && !prioList.empty()) {
		auto [weight, edge] = *prioList.begin(); // Type is std::pair<int, std::pair<T, T>>.
		auto& [from, to] = edge; // Type is std::pair<T, T>.
		prioList.erase(prioList.begin());

		if (!hasIncluded[to]) { // Creates default of 'false', if not already 'true'.
			std::tuple<T, T, int> newEdge = std::make_tuple(from, to, weight);
			mst.push_back(newEdge);
			totalCost += weight;

			for (const auto& [neighbour, weight] : this->adjList[to]) { // Type is std::pair<T, int>.
				std::pair<int, std::pair<T, T>> newNeighbour = std::make_pair(weight, std::make_pair(to, neighbour));
				prioList.insert(newNeighbour);
			}

			hasIncluded[to] = true;
		}
	}
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

	while (visitOrder.size() < 2 * this->nrOfVertices && !toVisit.empty()) {
		T current = toVisit.top();
		toVisit.pop();

		if (!hasVisited[current]) { // Creates default of 'false', if not already 'true'.
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

	while (visitOrder.size() < 2 * this->nrOfVertices && !toVisit.empty()) {
		T current = toVisit.front();
		toVisit.pop();

		if (!hasVisited[current]) { // Creates default of 'false', if not already 'true'.
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