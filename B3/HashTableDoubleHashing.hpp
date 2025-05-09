#ifndef HASHTABLEDOUBLEHASHING_HPP
#define HASHTABLEDOUBLEHASHING_HPP

#include <stdexcept>

class HashTableDoubleHashing
{
private:
	int* data;
	bool* removed;
	int numberOfElements;
	int capacity;

	void insertData(int element);
	void rehash();
	int extraHash(const int element, const int itteration) const;
public:
	HashTableDoubleHashing(int capacity = 7);
	~HashTableDoubleHashing();
	HashTableDoubleHashing(const HashTableDoubleHashing& other) = delete;
	HashTableDoubleHashing& operator=(const HashTableDoubleHashing& other) = delete;

	void insert(int element);
	void remove(int element);
	int find(int element);
	int size() const;
	int* getData() const;
};

HashTableDoubleHashing::HashTableDoubleHashing(int capacity)
{
	this->capacity = capacity;
	this->numberOfElements = 0;
	this->data = new int[this->capacity];
	this->removed = new bool[this->capacity];
	for (int i = 0; i < this->capacity; ++i) {
		this->data[i] = -1;
		this->removed[i] = false;
	}
}

HashTableDoubleHashing::~HashTableDoubleHashing()
{
	delete[] this->data;
	delete[] this->removed;
}

int HashTableDoubleHashing::size() const
{
	return this->numberOfElements;
}

int* HashTableDoubleHashing::getData() const
{
	return this->data;
}

int HashTableDoubleHashing::extraHash(const int element, const int itteration) const
{
	return itteration * (1 + (element % (this->capacity - 2)));
}

void HashTableDoubleHashing::insertData(int element)
{
	int index = element % capacity;
	int itteration = 0;
	while (this->data[index] != -1) {
		itteration++;
		index = (element % this->capacity + extraHash(element, itteration)) % this->capacity;
	}
	this->data[index] = element;
	this->removed[index] = false;
}

void HashTableDoubleHashing::rehash()
{
	int* oldTable = data;
	int oldCapacity = this->capacity;
	this->capacity = this->capacity * 2 - 1;
	data = new int[this->capacity];
	delete removed;
	removed = new bool[this->capacity];
	for (int i = 0; i < this->capacity; i++) {
		removed[i] = false;
		data[i] = -1;
	}
	for (int i = 0; i < oldCapacity; i++) {
		if (oldTable[i] != -1) {
			insertData(oldTable[i]);
		}
	}
	delete[] oldTable;
}

void HashTableDoubleHashing::insert(int element)
{
	if (this->numberOfElements == this->capacity) {
		rehash();
	}
	insertData(element);
	this->numberOfElements++;
}

void HashTableDoubleHashing::remove(int element)
{
	int index = element % this->capacity;
	int itteration = 0;
	while (this->data[index] != element
		&& (this->data[index] != -1 || this->removed[index] == true)
		&& itteration < this->capacity)
	{
		itteration++;
		index = (element % this->capacity + extraHash(element, itteration)) % this->capacity;
	}
	if (this->data[index] == element) {
		this->data[index] = -1;
		this->removed[index] = true;
		this->numberOfElements--;
	}
	else {
		throw std::invalid_argument("Cannot remove() non-existing element.");
	}
}

int HashTableDoubleHashing::find(int element)
{
	int index = element % this->capacity;
	int itteration = 0;
	while (this->data[index] != element
		&& (this->data[index] != -1 || this->removed[index] == true)
		&& itteration < this->capacity)
	{
		itteration++;
		index = (element % this->capacity + extraHash(element, itteration)) % this->capacity;
	}
	if (this->data[index] == element) {
		// This is not how I would implement it, but what CodeGrade wants.
		return element;
	}
	else {
		throw std::invalid_argument("Cannot find() non-existing element.");
	}
}

#endif