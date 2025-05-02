#ifndef INDEXEDLIST_HPP
#define INDEXEDLIST_HPP

#include <stdexcept>
#include <string>

template <class T>
class IndexedList {
private:
    class Node {
    public:
        T data;
        Node* next;

        Node(T data = nullptr, Node* next = nullptr) : data(data), next(next) {}
    };
    Node* front;
    int nrOfElements;
public:
    IndexedList();
    ~IndexedList();
    IndexedList(const IndexedList& other) = delete;
    IndexedList& operator=(const IndexedList& other) = delete;

    int size() const;
    bool isEmpty() const;
    T getAt(int index) const;
    T get(T element) const;
    void addAt(int index, const T& element);
    T removeFirst();
    T removeAt(int index);
    T removeLast();
    T first() const;
    T last() const;
};

template<class T>
IndexedList<T>::IndexedList() : nrOfElements(0) {
    this->front = nullptr;
}

template <class T>
IndexedList<T>::~IndexedList() {
    while (this->front != nullptr) {
        Node* temp = this->front;
        this->front = this->front->next;
        delete temp;
    }
}

template <class T>
int IndexedList<T>::size() const {
    // Returns size of IndexedList
    return this->nrOfElements;
}

template <class T>
bool IndexedList<T>::isEmpty() const {
    // Returns if empty or not
    return this->nrOfElements == 0;
}

template <class T>
T IndexedList<T>::getAt(int index) const {
    // Returns element at index
    if (index >= this->nrOfElements) {
        throw std::out_of_range("Cannot getAt() at index " + std::to_string(index) + " on list of length " + std::to_string(this->nrOfElements) + ".");
    }
    Node* walker = this->front;
    int currentIndex = 0;
    while (currentIndex < index) {
        walker = walker->next;
        currentIndex++;
    }
    return walker->data;
}

template <class T>
T IndexedList<T>::get(T element) const {
    // Returns element if it exists
    if (this->nrOfElements == 0) {
        throw std::out_of_range("Cannot get() on empty list.");
    }
    Node* walker = this->front;
    while (walker != nullptr) {
        if (walker->data == element) {
            return walker->data;
        }
        walker = walker->next;
    }
    throw std::invalid_argument("Element not in list.");
}

template <class T>
void IndexedList<T>::addAt(int index, const T& element) {
    // Adds element at an index
    if (index > this->nrOfElements || index < 0) {
        throw std::out_of_range("Cannot addAt() at index " + std::to_string(index) + " on list of length " + std::to_string(this->nrOfElements) + ".");
    }
    if (index == 0) {
        this->front = new Node(element, this->front);
    }
    else {
        Node* walker = this->front;
        int currentIndex = 0;
        while (currentIndex < index - 1) {
            walker = walker->next;
            currentIndex++;
        }
        walker->next = new Node(element, walker->next);
    }
    this->nrOfElements++;
}

template <class T>
T IndexedList<T>::removeFirst() {
    // Removes first element in the IndexedList
    if (this->nrOfElements == 0) {
        throw std::out_of_range("Cannot removeFirst() on empty list.");
    }
    T removed = this->front->data;
    Node* temp = this->front;
    this->front = this->front->next;
    delete temp;
    this->nrOfElements--;
    return removed;
}

template <class T>
T IndexedList<T>::removeAt(int index) {
    // Removes element at specific index
    if (index >= this->nrOfElements || index < 0) {
        throw std::out_of_range("Cannot removeAt() at index " + std::to_string(index) + " on list of length " + std::to_string(this->nrOfElements) + ".");
    }
    if (index == 0) {
        return removeFirst();
    }
    else {
        Node* walker = this->front;
        int currentIndex = 0;
        while (currentIndex < index - 1) {
            walker = walker->next;
            currentIndex++;
        }
        Node* temp = walker->next;
        T removed = temp->data;
        walker->next = temp->next;
        delete temp;
        this->nrOfElements--;
        return removed;
    }
}

template <class T>
T IndexedList<T>::removeLast() {
    // Removes last element in the IndexedList
    if (this->nrOfElements == 0) {
        throw std::out_of_range("Cannot removeLast() on empty list.");
    }
    if (this->nrOfElements == 1) {
        T removed = this->front->data;
        delete this->front;
        this->front = nullptr;
        this->nrOfElements--;
        return removed;
    }
    else {
        Node* walker = this->front;
        int currentIndex = 0;
        while (currentIndex < this->nrOfElements - 2) {
            walker = walker->next;
            currentIndex++;
        }
        T removed = walker->next->data;
        delete walker->next;
        walker->next = nullptr;
        this->nrOfElements--;
        return removed;
    }
}

template <class T>
T IndexedList<T>::first() const {
    // Returns the first element in the IndexedList
    if (this->nrOfElements == 0) {
        throw std::out_of_range("Cannot first() on empty list.");
    }
    return front->data;
}

template <class T>
T IndexedList<T>::last() const {
    // Returns the last element in the IndexedList
    if (this->nrOfElements == 0) {
        throw std::out_of_range("Cannot last() on empty list.");
    }
    Node* walker = this->front;
    while (walker->next != nullptr) {
        walker = walker->next;
    }
    return walker->data;
}

#endif
