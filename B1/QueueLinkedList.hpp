#ifndef QUEUELINKEDLIST_H
#define QUEUELINKEDLIST_H
#include <stdexcept>

template <typename T>
class QueueLinkedList
{
private:
	class Node
	{
	public:
		T data;
		Node* previous;
		Node(T data, Node* previous = nullptr)
			: data(data), previous(previous) {
		}
	};
	Node* head;
	Node* tail;
	int length;
public:
	QueueLinkedList();
	virtual ~QueueLinkedList();
	QueueLinkedList(const QueueLinkedList& other) = delete;
	QueueLinkedList& operator=(const QueueLinkedList& other) = delete;
	void enqueue(const T& element);
	T dequeue();
	const T& peek() const;
	bool isEmpty() const;
	int size() const;
};

template<typename T>
inline QueueLinkedList<T>::QueueLinkedList(): length(0)
{
	head = nullptr;
	tail = nullptr;
}

template<typename T>
inline QueueLinkedList<T>::~QueueLinkedList()
{
	Node* currentNode = this->head;
	for (int i = 0; i < this->length; ++i) {
		Node* toDelete = currentNode;
		currentNode = currentNode->previous;
		delete toDelete;
	}
}

template<typename T>
inline void QueueLinkedList<T>::enqueue(const T& element)
{
	if (this->length == 0) {
		this->tail = new Node(element);
		this->head = this->tail;
	}
	else {
		this->tail->previous = new Node(element);
		this->tail = this->tail->previous;
	}

	this->length++;
}

template<typename T>
inline T QueueLinkedList<T>::dequeue()
{
	if (this->length == 0) {
		throw std::runtime_error("Cannot dequeue() an empty queue.");
	}
	T toRetrun = this->head->data;
	Node* toDelete = this->head;
	this->head = this->head->previous;
	delete toDelete;
	this->length--;
	return toRetrun;
}

template<typename T>
inline const T& QueueLinkedList<T>::peek() const
{
	if (this->length == 0) {
		throw std::runtime_error("Cannot peek() an empty queue.");
	}
	T toPeek = this->head->data;
	return toPeek;
}

template<typename T>
inline bool QueueLinkedList<T>::isEmpty() const
{
	return this->length == 0;
}

template<typename T>
inline int QueueLinkedList<T>::size() const
{
	return this->length;
}

#endif
