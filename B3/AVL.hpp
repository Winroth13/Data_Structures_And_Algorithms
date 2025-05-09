#ifndef AVL_HPP
#define AVL_HPP

#include <string>

template <class T>
class AVL {
private:
	class Node {
	public:
		T data;
		Node* left;
		Node* right;
		Node* parent;
		int height;

		Node(T val, Node* parent = nullptr) : data(val), left(nullptr), right(nullptr), parent(parent), height(0) {}
	};

	Node* root;

	void rotate(Node* currentParent, const bool isRotateRight);
	void balanceRecurcive(Node* current);
	Node* insertRecurcive(Node* current, T element);
	Node* getMinRecursive(Node* current);
	Node* findRecursive(Node* current, T element);
	std::string inOrderTreversalRecursive(Node* current);
	std::string preOrderTreversalRecursive(Node* current);
	std::string postOrderTreversalRecursive(Node* current);
public:
	AVL();

	void insert(T element);

	T getMin();

	bool find(T element);

	void remove(T element);

	std::string inOrderTraversal();

	std::string preOrderTraversal();

	std::string postOrderTraversal();

	std::string toGraphviz();
	std::string toGraphvizRec(std::string data, Node* current, int& nodeID);
};

template <class T>
AVL<T>::AVL() : root(nullptr) {}

template <class T>
void AVL<T>::rotate(Node* currentParent, const bool isRotateRight) {
	Node* newParent;

	if (isRotateRight) {
		newParent = currentParent->left;
		currentParent->left->parent = currentParent;
		currentParent->left = newParent->right;
		newParent->right = currentParent;
	}
	else {
		newParent = currentParent->right;
		currentParent->right->parent = currentParent;
		currentParent->right = newParent->left;
		newParent->left = currentParent;
	}

	newParent->parent = currentParent->parent;
	if (currentParent->parent == nullptr) {
		this->root = newParent;
	}
	else if (currentParent->parent->right == currentParent) {
		currentParent->parent->right = newParent;
	}
	else {
		currentParent->parent->left = newParent;
	}

	currentParent->parent = newParent;
}

template <class T>
void AVL<T>::balanceRecurcive(Node* current) {
	if (current == nullptr) {
		return;
	}

	int rightHeight = -1;
	int leftHeight = -1;

	if (current->right != nullptr) {
		rightHeight = current->right->height;
	}

	if (current->left != nullptr) {
		leftHeight = current->left->height;
	}

	if (rightHeight > leftHeight + 1) { // Right heavy
		if (current->right->left != nullptr
			&& (current->right->right == nullptr || current->right->left->height > current->right->left->height)) {
			rotate(current->right, true);
		}
		rotate(current, false);
		current->height = leftHeight + 1;
		current->parent->height = std::max(current->height, current->parent->right->height) + 1;
	}
	else if (leftHeight > rightHeight + 1) { // Left heavy
		if (current->left->right != nullptr
			&& (current->left->left == nullptr || current->left->right->height > current->left->left->height)) {
			rotate(current->left, false);
		}
		rotate(current, true);
		current->height = rightHeight + 1;
		current->parent->height = std::max(current->height, current->parent->left->height) + 1;
	}
	else {
		current->height = std::max(leftHeight, rightHeight) + 1;
		balanceRecurcive(current->parent);
	}
}

template <class T>
class AVL<T>::Node* AVL<T>::insertRecurcive(Node* current, T element) {
	if (element > current->data) {
		if (current->right != nullptr) {
			return insertRecurcive(current->right, element);
		}
		else {
			current->right = new Node(element, current);
			return current->right;
		}
	}
	else if (element < current->data) {
		if (current->left != nullptr) {
			return insertRecurcive(current->left, element);
		}
		else {
			current->left = new Node(element, current);
			return current->left;
		}
	}
}

template <class T>
void AVL<T>::insert(T element) {
	if (this->root == nullptr) {
		this->root = new Node(element);
	}
	else {
		Node* newNode = insertRecurcive(this->root, element);
		balanceRecurcive(newNode->parent);
	}
}

template <class T>
class AVL<T>::Node* AVL<T>::getMinRecursive(Node* current) {
	if (current->left == nullptr) {
		return current;
	}
	else {
		return getMinRecursive(current->left);
	}
}

template <class T>
T AVL<T>::getMin() {
	return getMinRecursive(this->root)->data;
}

template <class T>
class AVL<T>::Node* AVL<T>::findRecursive(Node* current, T element) {
	if (element > current->data && current->right != nullptr) {
		return findRecursive(current->right, element);
	}
	else if (element < current->data && current->left != nullptr) {
		return findRecursive(current->left, element);
	}
	else if (element == current->data) {
		return current;
	}
	else {
		return nullptr;
	}
}

template <class T>
bool AVL<T>::find(T element)
{
	return findRecursive(this->root, element) != nullptr;
}

template <class T>
void AVL<T>::remove(T element) {
	Node* toRemove = findRecursive(this->root, element);
	Node* replacement;
	if (toRemove->left == nullptr && toRemove->right == nullptr) {
		replacement = nullptr;
	}
	else {
		if (toRemove->left == nullptr) {
			replacement = toRemove->right;
		}
		else if (toRemove->right == nullptr) {
			replacement = toRemove->left;
		}
		else {
			replacement = getMinRecursive(toRemove->right);
			if (replacement->parent != toRemove) {
				replacement->parent->left = replacement->right;
				if (replacement->right != nullptr) {
					replacement->right->parent = replacement->parent;
				}
				replacement->right = toRemove->right;
			}
			replacement->left = toRemove->left;
			toRemove->left->parent = replacement;
		}
		replacement->parent = toRemove->parent;
	}
	if (this->root == toRemove) {
		this->root = replacement;
	}
	else if (toRemove->parent->left == toRemove) {
		toRemove->parent->left = replacement;
	}
	else {
		toRemove->parent->right = replacement;
	}

	if (replacement != nullptr) {
		balanceRecurcive(replacement);
	}
	else {
		balanceRecurcive(toRemove->parent);
	}

	delete toRemove;
}

template <class T>
std::string AVL<T>::inOrderTreversalRecursive(Node* current) {
	std::string data = "";
	if (current->left != nullptr) {
		data += inOrderTreversalRecursive(current->left);
	}
	data += std::to_string(current->data) + ",";
	if (current->right != nullptr) {
		data += inOrderTreversalRecursive(current->right);
	}
	return data;
}

template <class T>
std::string AVL<T>::inOrderTraversal() {
	// Create a string and add elements in order and separated by space.
	// i.e. a AVL inserted with values 1, 2 and 3 becomes the following string
	// '1,2,3,'
	std::string data = inOrderTreversalRecursive(this->root);
	return data;
}

template <class T>
std::string AVL<T>::preOrderTreversalRecursive(Node* current) {
	std::string data = "";
	data += std::to_string(current->data) + ",";
	if (current->left != nullptr) {
		data += preOrderTreversalRecursive(current->left);
	}
	if (current->right != nullptr) {
		data += preOrderTreversalRecursive(current->right);
	}
	return data;
}

template <class T>
std::string AVL<T>::preOrderTraversal() {
	// Create a string and add elements pre order and separated by space.
	// i.e. a AVL inserted with values 1, 2 and 3 becomes the following string
	// '1,2,3,'
	std::string data = preOrderTreversalRecursive(this->root);
	return data;
}

template <class T>
std::string AVL<T>::postOrderTreversalRecursive(Node* current) {
	std::string data = "";
	if (current->left != nullptr) {
		data += postOrderTreversalRecursive(current->left);
	}
	if (current->right != nullptr) {
		data += postOrderTreversalRecursive(current->right);
	}
	data += std::to_string(current->data) + ",";
	return data;
}

template <class T>
std::string AVL<T>::postOrderTraversal() {
	// Create a string and add elements post order and separated by space.
	// i.e. a AVL inserted with values 1, 2 and 3 becomes the following string
	// '3,2,1,'
	std::string data = postOrderTreversalRecursive(this->root);
	return data;
}

template <class T>
std::string AVL<T>::toGraphviz()
{
	int nodeID = 0;
	std::string data = "";
	if (root != nullptr)
	{
		data += "digraph {\n";
		data += "\tRoot [shape=plaintext];\n";
		data += "\t\"Root\" -> 0 [color=black];\n";
		data = toGraphvizRec(data, this->root, nodeID);
		data += "}\n";
	}
	return data;
}

template <class T>
std::string AVL<T>::toGraphvizRec(std::string data, Node* current, int& nodeID)
{
	int my_nodeID = nodeID;
	data += "\t" + std::to_string(my_nodeID) + " [label=\"" + std::to_string(current->data) + "\"];\n";
	nodeID++;
	if (current->left != nullptr)
	{
		data += "\t" + std::to_string(my_nodeID) + " -> " + std::to_string(nodeID) + " [color=blue];\n";
		data = toGraphvizRec(data, current->left, nodeID);
	}
	else
	{
		data += "\t" + std::to_string(nodeID) + " [label=nill,style=invis];\n";
		data += "\t" + std::to_string(my_nodeID) + " -> " + std::to_string(nodeID) + " [style=invis];\n";
	}
	nodeID++;
	if (current->right != nullptr)
	{
		data += "\t" + std::to_string(my_nodeID) + " -> " + std::to_string(nodeID) + " [color=red];\n";
		data = toGraphvizRec(data, current->right, nodeID);
	}
	else
	{
		data += "\t" + std::to_string(nodeID) + " [label=nill,style=invis];\n";
		data += "\t" + std::to_string(my_nodeID) + " -> " + std::to_string(nodeID) + " [style=invis];\n";
	}
	return data;
}

#endif