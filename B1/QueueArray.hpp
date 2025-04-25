#ifndef QUEUEARRAY_H
#define QUEUEARRAY_H
#include <stdexcept>

template <typename T>
class QueueArray
{
private:
	T* elements;
	int capacity;
	int start;
	int end;
	int length;
public:
	QueueArray(int initialCapacity = 10);
	virtual ~QueueArray();
	QueueArray(const QueueArray& other) = delete;
	QueueArray& operator=(const QueueArray& other) = delete;
	void enqueue(const T& element);
	T dequeue();
	const T& peek() const;
	bool isEmpty() const;
	int size() const;
};

template<typename T>
inline QueueArray<T>::QueueArray(int initialCapacity) : capacity(initialCapacity), start(0), end(0), length(0)
{
	this->elements = new T[this->capacity];
}

template<typename T>
inline QueueArray<T>::~QueueArray()
{
	delete[] this->elements;
}

template<typename T>
inline void QueueArray<T>::enqueue(const T& element)
{
	if (this->length == this->capacity) {
		T* newArray = new T[this->capacity * 10];

		for (int i = 0; i < this->capacity; ++i) {
			newArray[i] = this->elements[(start + i) % capacity];
		}

		this->start = 0;
		this->end = capacity;

		delete[] this->elements;
		this->elements = newArray;

		this->capacity *= 10;
	}
	this->elements[this->end] = element;
	this->end = (this->end + 1) % this->capacity;
	this->length++;
}

template<typename T>
inline T QueueArray<T>::dequeue()
{
	if (this->length == 0) {
		throw std::runtime_error("Cannot dequeue() on empty queue.");
	}
	T toRemove = this->elements[this->start];
	this->start = (this->start + 1) % this->capacity;
	this->length--;
	return toRemove;
}

template<typename T>
inline const T& QueueArray<T>::peek() const
{
	if (this->length == 0) {
		throw std::runtime_error("Cannot peek() on empty queue.");
	}
	T toPeek = this->elements[this->start];
	return toPeek;
}

template<typename T>
inline bool QueueArray<T>::isEmpty() const
{
	return this->length == 0;
}

template<typename T>
inline int QueueArray<T>::size() const
{
	return this->length;
}

#endif
