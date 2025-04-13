#include "A2.hpp"
#include <iostream>

int main() {
	int arr[10] = { 9, 7, 5, 3, 1, 8, 6, 4, 2, 0 };
	QuicksortHoareImproved(arr, 10);

	for (int i = 0; i < 10; ++i) {
		std::cout << arr[i] << ", ";
	}
	std::cout << std::endl;

	/*int arr[8] = { 1, 8, 7, 6, 5, 4, 3, 2 };

	Heapsort(arr, 8);

	for (int i = 0; i < 8; ++i) {
		std::cout << arr[i] << ", ";
	}
	std::cout << std::endl;*/

	return 1;
}