#ifndef HEAP_HPP
#define HEAP_HPP

#include <stdexcept>

template <class T>
class Heap {
private:
    int capacity;
    int nrOfElements;
    T* elements;
    void expand();
    void perculateUp(const int index);
    void perculateDown(const int index);
public:
    Heap(int initialCapacity = 10);
    ~Heap();
    Heap(const Heap& other) = delete;
    Heap& operator=(const Heap& other) = delete;

    int size() const;
    bool isEmpty() const;
    void insert(const T& element);
    T extract();
    T peek() const;
};

template <class T>
Heap<T>::Heap(int initialCapacity)
{
    this->capacity = initialCapacity;
    this->nrOfElements = 0;
    this->elements = new T[this->capacity];
}

template <class T>
Heap<T>::~Heap()
{
    delete[] this->elements;
}

template <class T>
void Heap<T>::expand()
{
    // Expands the elements array if needed
    this->capacity *= 2;
    T* newArr = new T[this->capacity];
    for (int i = 0; i < nrOfElements; ++i) {
        newArr[i] = this->elements[i];
    }
    delete[] this->elements;
    this->elements = newArr;
}

template <class T>
void Heap<T>::perculateUp(const int index) {
    if (index == 0) {
        return;
    }
    int parent = (index - 1) / 2;
    if (this->elements[index] > this->elements[parent]) {
        std::swap(this->elements[index], this->elements[parent]);
        perculateUp(parent);
    }
}

template <class T>
void Heap<T>::perculateDown(const int index) {
    int leftChild = index * 2 + 1;
    int rightChild = index * 2 + 2;
    if (this->nrOfElements < leftChild) {
        return;
    }
    int bestChild = leftChild;
    if (this->nrOfElements > rightChild && this->elements[rightChild] > this->elements[leftChild]) {
        bestChild = rightChild;
    }
    if (this->elements[index] < this->elements[bestChild]) {
        std::swap(this->elements[index], this->elements[bestChild]);
        perculateDown(bestChild);
    }
}

template <class T>
int Heap<T>::size() const {
    // Return size of HeapList
    return this->nrOfElements;
}

template <class T>
bool Heap<T>::isEmpty() const {
    // Returns if empty or now
    return this->nrOfElements == 0;
}

template <class T>
void Heap<T>::insert(const T& element) {
    // Adds elements to Heap
    if (this->nrOfElements == this->capacity) {
        expand();
    }
    this->elements[this->nrOfElements] = element;
    this->nrOfElements++;
    perculateUp(nrOfElements - 1);
}

template <class T>
T Heap<T>::extract() {
    // # Removes and returns max element
    if (this->nrOfElements == 0) {
        throw std::runtime_error("Cannot extract() on empty heap.");
    }
    T extracted = this->elements[0];
    this->nrOfElements--;
    this->elements[0] = this->elements[this->nrOfElements];
    perculateDown(0);
    return extracted;
}

template <class T>
T Heap<T>::peek() const {
    // # Returns max element
    if (this->nrOfElements == 0) {
        throw std::runtime_error("Cannot peek() on empty heap.");
    }
    return this->elements[0];
}

#endif
