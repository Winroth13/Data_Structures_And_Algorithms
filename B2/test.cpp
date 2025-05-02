#include "Heap.hpp"
#include "IndexedList.hpp"
#include "OrderedList.hpp"
#include <iostream>

int main() {
	/*Heap<int> heap;

	heap.insert(0);
	std::cout << heap.peek() << std::endl;
	heap.insert(1);
	std::cout << heap.peek() << std::endl;
	heap.insert(2);
	std::cout << heap.peek() << std::endl;
	heap.insert(-1);
	std::cout << heap.peek() << std::endl;
	heap.insert(2);
	std::cout << heap.peek() << std::endl;
	heap.insert(3);
	std::cout << heap.peek() << std::endl;

	std::cout << heap.extract() << std::endl;
	std::cout << heap.extract() << std::endl;
	std::cout << heap.extract() << std::endl;
	std::cout << heap.extract() << std::endl;
	std::cout << heap.extract() << std::endl;
	std::cout << heap.extract() << std::endl;*/

	/*IndexedList<int> indexList;
	indexList.addAt(0, 0);
	std::cout << indexList.first() << std::endl;
	std::cout << indexList.last() << std::endl << std::endl;
	indexList.addAt(0, 1);
	std::cout << indexList.first() << std::endl;
	std::cout << indexList.last() << std::endl << std::endl;
	indexList.addAt(0, 2);
	std::cout << indexList.first() << std::endl;
	std::cout << indexList.last() << std::endl << std::endl;
	indexList.addAt(3, 3);
	std::cout << indexList.first() << std::endl;
	std::cout << indexList.last() << std::endl << std::endl;

	
	for (int i = 0; i < 4; ++i){
		std::cout << indexList.getAt(i) << ", ";
	}
	std::cout << std::endl << std::endl;

	std::cout << indexList.removeFirst() << std::endl;
	std::cout << indexList.removeLast() << std::endl;
	for (int i = 0; i < 2; ++i) {
		std::cout << indexList.getAt(i) << ", ";
	}
	std::cout << std::endl << std::endl;

	indexList.addAt(0, 7);
	indexList.addAt(0, 6);
	std::cout << indexList.removeAt(2) << std::endl << std::endl;*/

	OrderedList<int> ordList;

	for (int i = 0; i < 10; ++i) {
		ordList.add(i);
	}

	ordList.remove(9);
	ordList.remove(5);
	ordList.remove(2);
	ordList.remove(0);
	
	ordList.add(0);
	ordList.add(2);
	ordList.add(5);
	ordList.add(9);

	for (int i = 0; i < 10; i++) {
		std::cout << ordList.removeFirst() << std::endl;
	}
}