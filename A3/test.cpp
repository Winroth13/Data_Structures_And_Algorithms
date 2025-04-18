#include "A3.hpp"
#include <iostream>

int main() {
	int arr[10] = { 4, 6, 4, 8, 7, 9, 0, 1, 2, 3 };
	/*Countingsort(arr, 10);*/
	/*for (int i = 0; i < 10; ++i) {
		std::cout << arr[i] << ", ";
	}*/
	int arr2[10] = { 41, 63, 23, 64, 78, 99, 100, 52, 60, 5 };

	/*RadixsortCounting(arr2, 10);
	for (int i = 0; i < 10; ++i) {
		std::cout << arr2[i] << ", ";
	}*/

	/*RadixsortBuckets(arr2, 10);
	for (int i = 0; i < 10; ++i) {
		std::cout << arr2[i] << ", ";
	}*/

	std::string arr3[10] = { "abc", "aaa", "bbb", "ccc", "ff", "aaaa", "a", "ki", "di", "fa" };
	RadixsortStrings(arr3, 10);
	for (int i = 0; i < 10; ++i) {
		std::cout << arr3[i] << ", ";
	}

	/*std::string test[27] = { "", "a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z" };
	for (int i = 0; i < 27; ++i) {
		std::cout << LetterIndex(test[i], 1) << std::endl;
	}*/
}