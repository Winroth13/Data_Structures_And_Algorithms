#ifndef HUFFMAN_HPP
#define HUFFMAN_HPP

#include <string>
#include <unordered_map>
#include <iostream>
#include <vector>
#include <map>

class Huffman
{
private:
	class Node
	{
	public:
		std::string data;
		Node* lChild;
		Node* rChild;

		Node(std::string data = "", Node* lChild = nullptr, Node* rChild = nullptr) { this->data = data; this->lChild = lChild; this->rChild = rChild; }
	};

	Node* decodingTree;
	std::unordered_map<std::string, std::string> encodingTable;

	void generateTableRecursive(const Node* currentNode, std::string route);
public:
	Huffman();
	~Huffman() = default;
	Huffman(const Huffman& other) = delete;
	Huffman operator=(const Huffman& other) = delete;
	std::string encode(std::string data);
	std::string decode(std::string bits);
	void build(std::string data);
};

Huffman::Huffman()
{
	decodingTree = nullptr;
}

std::string Huffman::encode(std::string data)
{
	// Encodes the incoming text string into a binary string
	// eg, output should be "010100011000111"
	std::string output;

	for (char character : data) {
		std::string charString{ character };
		output.append(encodingTable[charString]);
	}

	return output;
}

std::string Huffman::decode(std::string bits)
{
	// Decodes an incoming bit string into a text string
	std::string output;
	Node* walker = decodingTree;

	for (char bit : bits) {
		if (bit == '0') {
			walker = walker->lChild;
		}
		else {
			walker = walker->rChild;
		}

		if (walker->data != "") {
			output.append(walker->data);
			walker = decodingTree;
		}
	}

	return output;
}

void Huffman::generateTableRecursive(const Node* currentNode, std::string route)
{
	if (currentNode->data != "") {
		this->encodingTable[currentNode->data] = route;
	}
	else {
		generateTableRecursive(currentNode->lChild, route + "0");
		generateTableRecursive(currentNode->rChild, route + "1");
	}
}

void Huffman::build(std::string data)
{
	// Builds the encoding tree and decoding table
	// based on the frequencies you calculate in the data string

	//Building tree.
	std::unordered_map<std::string, int> frequencies;
	for (char character : data) {
		std::string charString{ character };
		if (!frequencies.contains(charString)) {
			frequencies[charString] = 1;
		}
		else {
			frequencies[charString]++;
		}
	}

	std::multimap<int, Node*> nodeMap;
	for (const auto& [symbol, frequency] : frequencies) { // Type is std::pair<std::string, int>.
		std::pair<int, Node*> newNode = std::make_pair(frequency, new Node(symbol));
		nodeMap.insert(newNode);
	}

	while (nodeMap.size() > 1) {
		const auto [lowFrequency, lowNode] = *nodeMap.begin(); // Type is std::pair<int, Node*>.
		nodeMap.erase(nodeMap.begin());
		const auto [highFrequency, highNode] = *nodeMap.begin(); // Type is std::pair<int, Node*>.
		nodeMap.erase(nodeMap.begin());

		std::pair<int, Node*> newNode = std::make_pair(lowFrequency + highFrequency, new Node("", lowNode, highNode));
		nodeMap.insert(newNode);
	}

	const auto& [totalFrequency, rootNode] = *nodeMap.begin();

	this->decodingTree = rootNode;

	// Creating encoding table.
	generateTableRecursive(rootNode, "");
}

#endif