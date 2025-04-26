#ifndef QUEUESTACKS_H
#define QUEUESTACKS_H
#include <stdexcept>
#include "StackArray.hpp"

template <typename T>
class QueueStacks
{
private:
	int length;
	StackArray<T> tailStack;
	StackArray<T> reverseStack;
public:
	QueueStacks();
	virtual ~QueueStacks();
	QueueStacks(const QueueStacks& other) = delete;
	QueueStacks& operator=(const QueueStacks& other) = delete;
	void enqueue(const T& element);
	T dequeue();
	const T& peek();	// Cannot be const in this version
	bool isEmpty() const;
	int size() const;
};

template<typename T>
inline QueueStacks<T>::QueueStacks() : length(0)
{
}

template<typename T>
inline QueueStacks<T>::~QueueStacks()
{
}

template<typename T>
inline void QueueStacks<T>::enqueue(const T& element)
{
	this->tailStack.push(element);
	this->length++;
}

template<typename T>
inline T QueueStacks<T>::dequeue()
{
	if (this->length == 0) {
		throw std::runtime_error("Cannot dequeue() on empty queue.");
	}
	while (!this->tailStack.isEmpty()) {
		this->reverseStack.push(this->tailStack.pop());
	}
	T toReturn = this->reverseStack.pop();
	while (!this->reverseStack.isEmpty()) {
		this->tailStack.push(this->reverseStack.pop());
	}
	this->length--;
	return toReturn;
}

template<typename T>
inline const T& QueueStacks<T>::peek()
{
	if (this->length == 0) {
		throw std::runtime_error("Cannot peek() on empty queue.");
	}
	while (!this->tailStack.isEmpty()) {
		this->reverseStack.push(this->tailStack.pop());
	}
	T toPeek = this->reverseStack.peek();
	while (!this->reverseStack.isEmpty()) {
		this->tailStack.push(this->reverseStack.pop());
	}
	return toPeek;
}

template<typename T>
inline bool QueueStacks<T>::isEmpty() const
{
	return this->length == 0;
}

template<typename T>
inline int QueueStacks<T>::size() const
{
	return this->length;
}

#endif