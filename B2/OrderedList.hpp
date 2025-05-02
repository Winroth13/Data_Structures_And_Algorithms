#ifndef ORDEREDLIST_HPP
#define ORDEREDLIST_HPP

#include <stdexcept>

template <class T>
class OrderedList {
private:
    struct Node {
        T data;
        Node* next;

        Node(const T& value, Node* next = nullptr) : data(value), next(next) {}
    };

    Node* front;
    int nrOfElements;

public:
    OrderedList();
    ~OrderedList();
    OrderedList(const OrderedList& other) = delete;
    OrderedList& operator=(const OrderedList& other) = delete;

    int size() const;
    bool isEmpty() const;
    void add(const T& element);
    T remove(const T& element);
    T removeAt(int index);
    T removeFirst();
    T removeLast();
    T get(const T& element) const;
    T first() const;
    T last() const;
};

template <class T>
OrderedList<T>::OrderedList() : nrOfElements(0) {
    this->front = nullptr;
}

template <class T>
OrderedList<T>::~OrderedList() {
    while (front != nullptr) {
        Node* temp = front;
        front = front->next;
        delete temp;
    }
}

template <class T>
int OrderedList<T>::size() const {
    // Returns size of OrderedList
    return this->nrOfElements;
}

template <class T>
bool OrderedList<T>::isEmpty() const {
    // Returns if OrderedList is empty or now
    return this->nrOfElements == 0;
}

template <class T>
void OrderedList<T>::add(const T& element) {
    // Adds element to the OrderedList in its correct place
    if (this->nrOfElements == 0 || front->data > element) {
        this->front = new Node(element, this->front);
    }
    else {
        Node* walker = front;
        while (walker->next != nullptr && walker->next->data < element) {
            walker = walker->next;
        }
        walker->next = new Node(element, walker->next);
    }
    this->nrOfElements++;
}

template <class T>
T OrderedList<T>::remove(const T& element) {
    // Removes and returns specific element from the OrderedList
    if (this->nrOfElements == 0) {
        throw std::out_of_range("Cannot get() on empty list.");
    }
    if (front->data == element) {
        return removeFirst();
    }
    else {
        Node* walker = this->front;
        while (walker->next != nullptr) {
            if (walker->next->data == element) {
                Node* temp = walker->next;
                T removed = temp->data;
                walker->next = temp->next;
                delete temp;
                this->nrOfElements--;
                return removed;
            }
            walker = walker->next;
        }
        throw std::invalid_argument("Element not in list.");
    }
}

template <class T>
T OrderedList<T>::removeAt(int index) {
    // Removes and returns element at specific index from the OrderedList
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
T OrderedList<T>::removeFirst() {
    // Removes and returns the first element from the OrderedList
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
T OrderedList<T>::removeLast() {
    // Removes and returns the last element from the OrderedList
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
T OrderedList<T>::get(const T& element) const {
    // Returns a specific element in the OrderedList
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
T OrderedList<T>::first() const {
    // Returns the first element in the OrderedList
    if (this->nrOfElements == 0) {
        throw std::out_of_range("Cannot first() on empty list.");
    }
    return front->data;
}

template <class T>
T OrderedList<T>::last() const {
    // Returns the last element in the OrderedList
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
