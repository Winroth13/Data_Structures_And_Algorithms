#ifndef HASHTABLECHAINING_HPP
#define HASHTABLECHAINING_HPP

#include <stdexcept>

class HashTableChaining
{
private:
	class Data {
	public:
		int val;
		Data* next;

		Data(int val) : val(val), next(nullptr) {}
	};

	Data** elements;

	int numberOfElements;
	int capacity;

public:
	HashTableChaining(int capacity = 7);
	~HashTableChaining();
	HashTableChaining(const HashTableChaining& other) = delete;
	HashTableChaining& operator=(const HashTableChaining& other) = delete;

	void insert(int element);
	void remove(int element);
	int find(int element);
	int size() const;
	int getIndex(int element) const;
};

HashTableChaining::HashTableChaining(int capacity)
{
	this->capacity = capacity;
	this->numberOfElements = 0;
	this->elements = new Data * [this->capacity];
	for (int i = 0; i < this->capacity; ++i) {
		this->elements[i] = nullptr;
	}
}
HashTableChaining::~HashTableChaining()
{
	for (int i = 0; i < this->capacity; ++i) {
		Data* toRemove = elements[i];
		while (toRemove != nullptr) {
			Data* temp = toRemove;
			toRemove = toRemove->next;
			delete temp;
		}
	}
	delete[] elements;
}

int HashTableChaining::size() const
{
	return this->numberOfElements;
}

int HashTableChaining::getIndex(int element) const
{
	// Returns index of the element if it exists, throw exception if not exists.
	int index = element % capacity;
	Data* currentElement = this->elements[index];
	while (currentElement != nullptr && currentElement->val != element) {
		currentElement = currentElement->next;
	}
	if (currentElement == nullptr) {
		throw std::invalid_argument("Cannot getIndex() on non-existing element.");
	}
	else {
		return index;
	}
}

void HashTableChaining::insert(int element)
{
	int index = element % capacity;
	if (this->elements[index] == nullptr) {
		this->elements[index] = new Data(element);
	}
	else {
		Data* lastElement = this->elements[index];
		while (lastElement->next != nullptr) {
			lastElement = lastElement->next;
		}
		lastElement->next = new Data(element);
	}
	this->numberOfElements++;
}

void HashTableChaining::remove(int element)
{
	int index = element % capacity;
	if (this->elements[index] == nullptr || this->elements[index]->val != element && this->elements[index]->next == nullptr) {
		throw std::invalid_argument("Cannot remove() non-existing element.");
	}
	else if (this->elements[index]->val == element) {
		Data* toRemove = this->elements[index];
		this->elements[index] = toRemove->next;
		delete toRemove;
	}
	else {
		Data* currentElement = this->elements[index];
		while (currentElement->next != nullptr && currentElement->next->val != element) {
			currentElement = currentElement->next;
		}
		if (currentElement->next == nullptr) {
			throw std::invalid_argument("Cannot remove() non-existing element.");
		}
		else {
			Data* toRemove = currentElement->next;
			currentElement->next = toRemove->next;
			delete toRemove;
		}
	}
	this->numberOfElements--;
}

int HashTableChaining::find(int element)
{
	int index = element % capacity;
	Data* currentElement = this->elements[index];
	while (currentElement != nullptr && currentElement->val != element) {
		currentElement = currentElement->next;
	}
	if (currentElement == nullptr) {
		throw std::invalid_argument("Cannot find() on non-existing element.");
	}
	else {
		return element;
	}
}

#endif