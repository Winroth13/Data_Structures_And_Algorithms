#ifndef STACKLINKEDLIST_H
#define STACKLINKEDLIST_H
#include <stdexcept>

template <typename T>
class StackLinkedList
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
	int length;
public:
	StackLinkedList();
	virtual ~StackLinkedList();
	StackLinkedList(const StackLinkedList& other) = delete;
	StackLinkedList& operator=(const StackLinkedList& other) = delete;
	void push(const T& element);
	T pop();
	const T& peek() const;
	bool isEmpty()const;
	int size() const;
};

template<typename T>
inline StackLinkedList<T>::StackLinkedList(): length(0)
{
	this->head = nullptr;
}

template<typename T>
inline StackLinkedList<T>::~StackLinkedList()
{

}


template<typename T>
inline void StackLinkedList<T>::push(const T& element)
{
	this->head = new Node(element, this->head);

	this->length++;
}

template<typename T>
inline T StackLinkedList<T>::pop()
{
	if (this->length == 0) {
		throw std::runtime_error("Cannot pop() an empty stack.");
	}
	T toReturn = this->head->data;
	Node* toDelete = this->head;
	this->head = this->head->previous;
	delete toDelete;
	this->length--;
	return toReturn;
}

template<typename T>
inline const T& StackLinkedList<T>::peek() const
{
	if (this->length == 0) {
		throw std::runtime_error("Cannot peek() an empty stack.");
	}
	T toPeek = this->head->data;
	return toPeek;
}

template<typename T>
inline bool StackLinkedList<T>::isEmpty()const
{
	return this->length == 0;
}

template<typename T>
inline int StackLinkedList<T>::size()const
{
	return this->length;
}

#endif
