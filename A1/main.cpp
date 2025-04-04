#include "A1.hpp"
#include <iostream>
#include <vector>

int main() {
	int arr[5] = { 72, 89, 5, 32, 65 };
	int bArr[20] = { 1, 2, 3, 4, 5 ,6, 7 , 8, 9, 10, 11, 12, 13, 14, 15, 16 , 17, 18, 19, 20 };
	int cArr[100];

	for (int i = 0; i < 100; ++i) {
		cArr[i] = i;
	}

	/*std::cout << LinearSearch(arr, 5, 72) << std::endl;
	std::cout << LinearSearch(arr, 5, 32) << std::endl;
	std::cout << LinearSearch(arr, 5, 2) << std::endl;*/

	/*Selectionsort(arr, 5);*/
	/*Insertionsort(arr, 5);
	for (int i = 0; i < 5; ++i) {
		std::cout << arr[i] << ", ";
	}*/

	/*std::cout << BinarySearch(arr, 5, 72) << std::endl;
	std::cout << BinarySearch(arr, 5, 5) << std::endl;
	std::cout << BinarySearch(arr, 5, 2) << std::endl;*/

	/*std::cout << LinearSearchRecursive(cArr, 100, 98) << std::endl;*/
	/*std::cout << LinearSearchRecursive(cArr, 100, 32) << std::endl;
	std::cout << LinearSearchRecursive(cArr, 100, 2) << std::endl;*/

	/*std::cout << BinarySearchRecursive(cArr, 100, 72) << std::endl;*/

	BinaryInsertionsort(arr, 5);
	for (int i = 0; i < 5; ++i) {
		std::cout << arr[i] << ", ";
	}
}