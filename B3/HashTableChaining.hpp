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

	void rehash();
	void insertData(Data* data);

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

void HashTableChaining::insertData(Data* data)
{
	int index = data->val % capacity;
	if (this->elements[index] == nullptr) {
		this->elements[index] = data;
	}
	else {
		Data* lastElement = this->elements[index];
		while (lastElement->next != nullptr) {
			lastElement = lastElement->next;
		}
		lastElement->next = data;
	}
}

void HashTableChaining::rehash()
{
	Data** oldTable = elements;
	int oldCapacity = this->capacity;
	this->capacity = this->capacity * 2 - 1;
	elements = new Data * [this->capacity];
	Data* currentData;
	for (int i = 0; i < oldCapacity; i++) {
		currentData = oldTable[i];
		while (currentData != nullptr) {
			insertData(currentData);
			currentData = currentData->next;
		}
	}
	delete[] oldTable;
}

void HashTableChaining::insert(int element)
{
	if (this->numberOfElements == this->capacity) {
		rehash();
	}
	Data* data = new Data(element);
	insertData(data);
	this->numberOfElements++;
}

void HashTableChaining::remove(int element)
{
	int index = element % capacity;
	if (this->elements[index] == nullptr || (this->elements[index]->val != element && this->elements[index]->next == nullptr)) {
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