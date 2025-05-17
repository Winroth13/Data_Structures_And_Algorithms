#ifndef DISJOINTSETS_HPP
#define DISJOINTSETS_HPP

#include <unordered_map>
#include <iostream>
#include <vector>
#include <stdexcept>

template <class T>
class DisjointSets {
private:
	std::unordered_map<T, std::pair<T, int>> parentRank;
	int nrOfElements;
	bool pathCompression;
	bool unionByRank;
public:
	DisjointSets(bool pathCompression = false, bool unionByRank = false);
	int size();
	void makeSet(T u);
	T findSet(T u);
	void unionSet(T u, T v);
	T getParent(T u);
};

template <class T>
DisjointSets<T>::DisjointSets(bool pathCompression, bool unionByRank)
	: nrOfElements(0), pathCompression(pathCompression), unionByRank(unionByRank) {
}

template <class T>
int DisjointSets<T>::size()
{
	return this->nrOfElements;
}

template <class T>
void DisjointSets<T>::makeSet(T u)
{
	if (this->parentRank.contains(u)) {
		throw std::invalid_argument("Cannot makeSet() on already existent vertex.");
	}
	this->parentRank[u] = std::make_pair(u, 0);
	this->nrOfElements++;
}

template <class T>
T DisjointSets<T>::findSet(T u)
{
	if (!this->parentRank.contains(u)) {
		throw std::invalid_argument("Cannot findSet() on non-existent vertex.");
	}

	auto& [parent, rank] = this->parentRank[u]; // Type is std::pair<T, int>.

	if (u == parent) {
		return u;
	}

	if (this->pathCompression) {
		parent = findSet(parent);
		return parent;
	}
	else {
		do {
			u = parent;
			auto& [nextParent, nextRank] = this->parentRank[parent]; // Type is std::pair<T, int>.
			parent = nextParent;
		} while (u != parent);
		return u;
	}
}

template <class T>
void DisjointSets<T>::unionSet(T u, T v)
{
	T firstRoot = findSet(u);
	T secondRoot = findSet(v);

	if (firstRoot == secondRoot) {
		throw std::invalid_argument("Cannot unionSet() on same set.");
	}

	auto& [firstParent, firstRank] = this->parentRank[firstRoot]; // Type is std::pair<T, int>.
	auto& [secondParent, secondRank] = this->parentRank[secondRoot];

	if (this->unionByRank && secondRank > firstRank) {
		firstParent = secondRoot;
		if (secondRank <= firstRank) {
			secondRank = firstRank + 1;
		}
	}
	else {
		secondParent = firstRoot;
		if (firstRank <= secondRank) {
			firstRank = secondRank + 1;
		}
	}
}

template <class T>
T DisjointSets<T>::getParent(T u)
{
	if (!this->parentRank.contains(u)) {
		throw std::invalid_argument("Cannot getParent() of non-existent vertex.");
	}
	auto& [parent, rank] = this->parentRank[u]; // Type is std::pair<T, int>.
	return parent;
}

#endif