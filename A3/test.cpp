#include "A3.hpp"
#include <iostream>

int main() {
	int arr[10] = { 4, 6, 4, 8, 7, 9, 0, 1, 2, 3 };
	/*Countingsort(arr, 10);*/
	/*for (int i = 0; i < 10; ++i) {
		std::cout << arr[i] << ", ";
	}*/
	int arr2[10] = { 41, 63, 23, 64, 78, 99, 100, 52, 60, 5 };

	RadixsortCounting(arr2, 10);
	for (int i = 0; i < 10; ++i) {
		std::cout << arr2[i] << ", ";
	}
}