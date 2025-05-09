#include "BST.hpp"
#include "HashTableLinearProbing.hpp"
#include "AVL.hpp"

#include <string>
#include <iostream>

int main() {
	/*HashTableLinearProbing table;
	table.insert(0);
	table.insert(1);
	table.insert(9);
	table.insert(17);
	table.insert(3);
	table.remove(1);
	table.remove(3);
	table.insert(22);
	table.insert(33);
	table.insert(44);
	table.insert(55);
	table.insert(100);*/

	AVL<int> avl;

	avl.insert(8);
	avl.insert(4);
	avl.insert(2);
	avl.insert(1);
	avl.insert(3);
	avl.insert(6);
	avl.insert(7);
	avl.insert(5);
	avl.remove(7);
	avl.remove(1);
	avl.remove(6);
	avl.remove(8);

	std::cout << avl.toGraphviz();
	//std::cout << bst.inOrderTraversal();
	/*std::cout << bst.find(2) << std::endl;
	std::cout << bst.find(6) << std::endl;*/
	//std::cout << bst.getMin();
}