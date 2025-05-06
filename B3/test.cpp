#include "BST.hpp"

#include <string>
#include <iostream>

int main() {
	BST<int> bst;

	bst.insert(8);
	bst.insert(4);
	bst.insert(2);
	bst.insert(1);
	bst.insert(3);
	bst.insert(6);
	bst.insert(7);
	bst.insert(5);
	bst.remove(7);
	bst.remove(1);
	bst.remove(6);
	bst.remove(8);

	std::cout << bst.toGraphviz();
	//std::cout << bst.inOrderTraversal();
	/*std::cout << bst.find(2) << std::endl;
	std::cout << bst.find(6) << std::endl;*/
	//std::cout << bst.getMin();
}