#ifndef HEAPLIST_HPP
#define HEAPLIST_HPP

#include "IndexedList.hpp"
#include <stdexcept>

template <class T>
class HeapList {
private:
	IndexedList<T> elements;
	void perculateUp(const int index);
	void perculateDown(const int index);
public:
	HeapList() = default;
	~HeapList() = default;
	HeapList(const HeapList& other) = delete;
	HeapList& operator=(const HeapList& other) = delete;

	int size() const;
	bool isEmpty() const;
	void insert(const T& element);
	T extract();
	T peek() const;
};

template <class T>
int HeapList<T>::size() const {
	// Returns size of Heap
	return this->elements.size();
}

template <class T>
bool HeapList<T>::isEmpty() const {
	// Returns if empty or now
	return this->elements.isEmpty();
}

template <class T>
void HeapList<T>::perculateUp(const int index) {
	if (index == 0) {
		return;
	}
	int parentIndex = (index - 1) / 2;
	if (this->elements.getAt(parentIndex) < this->elements.getAt(index)) {
		T indexValue = this->elements.removeAt(index);
		T parentValue = this->elements.removeAt(parentIndex);
		this->elements.addAt(parentIndex, indexValue);
		this->elements.addAt(index, parentValue);
		perculateUp(parentIndex);
	}
}

template <class T>
void HeapList<T>::perculateDown(const int index) {
	int leftChild = index * 2 + 1;
	int rightChild = index * 2 + 2;
	if (leftChild >= this->elements.size()) {
		return;
	}
	int bestChild = leftChild;
	if (rightChild < this->elements.size() && this->elements.getAt(rightChild) > this->elements.getAt(leftChild)) {
		bestChild = rightChild;
	}
	if (this->elements.getAt(index) < this->elements.getAt(bestChild)) {
		T childValue = this->elements.removeAt(bestChild);
		T indexValue = this->elements.removeAt(index);
		this->elements.addAt(index, childValue);
		this->elements.addAt(bestChild, indexValue);
		perculateDown(bestChild);
	}
}

template <class T>
void HeapList<T>::insert(const T& element) {
	// Adds elements to Heap
	this->elements.addAt(elements.size(), element);
	perculateUp(elements.size() - 1);
}

template <class T>
T HeapList<T>::extract() {
	// Removes and returns max element
	T removed = this->elements.removeFirst();
	if (this->elements.size() != 0) {
		this->elements.addAt(0, this->elements.removeLast());
		perculateDown(0);
	}
	return removed;
}

template <class T>
T HeapList<T>::peek() const {
	// Returns max element
	return this->elements.first();
}

#endif