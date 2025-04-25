#ifndef STACKARRAY_H
#define STACKARRAY_H
#include <stdexcept>

template <typename T>
class StackArray
{
private:
	T* elements;
	int capacity;
	int head;
public:
	StackArray(int initialCapacity = 10);
	virtual ~StackArray();
	StackArray(const StackArray& other) = delete;
	StackArray& operator=(const StackArray& other) = delete;
	void push(const T& element);
	T pop();
	const T& peek() const;
	bool isEmpty()const;
	int size() const;
};

template<typename T>
inline StackArray<T>::StackArray(int initialCapacity): capacity(initialCapacity), head(0)
{
	this->elements = new T[this->capacity];
}

template<typename T>
inline StackArray<T>::~StackArray()
{
	delete[] elements;
}


template<typename T>
inline void StackArray<T>::push(const T& element)
{
	if (this->head == this->capacity) {
		T* newArray = new T[capacity * 10];
		for (int i = 0; i < this->capacity; ++i) {
			newArray[i] = elements[i];
		}
		delete this->elements;
		this->elements = newArray;
		this->capacity *= 10;
	}
	this->elements[head] = element;
	this->head++;
}

template<typename T>
inline T StackArray<T>::pop()
{
	if (head == 0) {
		throw std::runtime_error("Cannot pop() on an empty stack.");
	}
	T toRemove = this->elements[this->head - 1];
	this->head--;
	return toRemove;
}

template<typename T>
inline const T& StackArray<T>::peek() const
{
	if (head == 0) {
		throw std::runtime_error("Cannot peek() on an empty stack.");
	}
	T toPeek = this->elements[this->head - 1];
	return toPeek;
}

template<typename T>
inline bool StackArray<T>::isEmpty()const
{
	return this->head == 0;
}

template<typename T>
inline int StackArray<T>::size()const
{
	return this->head;
}

#endif
