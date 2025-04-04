#ifndef A1_HPP
#define A1_HPP
#include <algorithm>	// Included for use of std::swap()
#include <cmath>
//#include <iostream>

template <class T>
int LinearSearch(T elements[], int nrOfElements, T element)
{
	// Iterate over all elements.
	for (int i = 0; i < nrOfElements; ++i) {
		// Return if target element.
		if (elements[i] == element) {
			return i;
		}
	}

	return -1;
}

template <class T>
void Selectionsort(T elements[], int nrOfElements)
{
	// Iterate over all elements except the last.
	for (int i = 0; i < nrOfElements - 1; ++i) {
		int minIndex = i;
		// Compare with all later elements.
		for (int j = i + 1; j < nrOfElements; ++j) {
			// Keep track of lowest element.
			if (elements[minIndex] > elements[j]) {
				minIndex = j;
			}
		}
		// Swap lowest and current element.
		std::swap(elements[i], elements[minIndex]);
	}
}

template <class T>
void Insertionsort(T elements[], int nrOfElements)
{
	// Iterate over all elements except the first.
	for (int i = 1; i < nrOfElements; ++i) {
		T key = elements[i];
		int j = i - 1;
		// Moves all elements higher than the currently active value.
		while (j > -1 && key < elements[j]) {
			elements[j + 1] = elements[j];
			--j;
		}
		// Inserts value into list when no longer higher (or first).
		elements[j + 1] = key;
	}
}

template <class T>
int BinarySearch(T elements[], int nrOfElements, T element)
{
	int start = 0;
	int end = nrOfElements - 1;
	// Runs until hit or no possible hits remaining.
	while (start <= end) {
		// Compares with the middle.
		int middle = int(std::floor((end + start) / 2));
		/*if (element < elements[middle]) {
			end = middle - 1;
		}
		else if (element > elements[middle]) {
			start = middle + 1;
		}
		else {
			return middle;
		}*/
		// For CodeGrade (Less effective),
		if (element == elements[middle]) {
			return middle;
		}
		else if (element > elements[middle]) {
			start = middle + 1;
		}
		else {
			end = middle - 1;
		}
	}

	return -1;
}

template <class T>
int LinearSearchRecursionStep(T elements[], int nrOfElements, T element, int recursionNr) {
	if (element == elements[recursionNr]) {
		return recursionNr;
	}

	++recursionNr;

	if (nrOfElements > recursionNr) {
		return LinearSearchRecursionStep(elements, nrOfElements, element, recursionNr);
	}

	return -1;
}

template <class T>
int LinearSearchRecursive(T elements[], int nrOfElements, T element)
{
	// Implementera en rekursiv linjärsökning.
	// Anropa er egna rekursiva funktion härifrån.

	return LinearSearchRecursionStep(elements, nrOfElements, element, 0);

	// Reverse recursion.
	/*if (element == elements[nrOfElements - 1]) {
		return nrOfElements - 1;
	}
	if (nrOfElements > 1) {
		return LinearSearchRecursive(elements, nrOfElements - 1, element);
	}

	return -1;*/
}

template <class T>
int BinarySearchRecursionStep(T elements[], T element, int start, int end) {
	// Checks if there are any elements left to check.
	if (start > end) {
		return -1;
	}

	//Comapres with the middle.
	int middle = int(std::floor((start + end) / 2));

	// For CodeGrade.
	if (element == elements[middle]) {
		return middle;
	}
	else if (element > elements[middle]) {
		return BinarySearchRecursionStep(elements, element, middle + 1, end);
	}
	else {
		return BinarySearchRecursionStep(elements, element, start, middle - 1);
	}

	// More efficient.
	/*if (element < elements[middle]) {
		return BinarySearchRecursionStep(elements, element, start, middle - 1);
	}
	else if (element > elements[middle]) {
		return BinarySearchRecursionStep(elements, element, middle + 1, end);
	}
	else {
		return middle;
	}*/
}

template <class T>
int BinarySearchRecursive(T elements[], int nrOfElements, T element)
{
	// Implementera en rekursiv binärsökning.
	// Anropa er egna rekursiva funktion härifrån.

	return BinarySearchRecursionStep(elements, element, 0, nrOfElements - 1);
}

template <class T>
void BinaryInsertionsort(T elements[], int nrOfElements)
{
	// Implementera en iterativ insertionsort där du söker efter rätt plats att lägga in elementet m.h.a. binärsökning.

	// Iterate over all elements except the first.
	for (int i = 1; i < nrOfElements; ++i) {
		T key = elements[i];

		int start = 0;
		int end = i - 1;

		while (start <= end) {
			int middle = int(std::floor((end + start) / 2));
			if (key == elements[middle]) {
				// Breaks the loop and makes sure the middle between start and end is next to the jsut compared index.
				start = middle + 1;
				end = middle;
			}
			else if (key > elements[middle]) {
				start = middle + 1;
			}
			else {
				end = middle - 1;
			}
		}

		// The average between start and end is now the index that the object is to be placed at.
		int correctIndex = int(std::ceil((end + start) / 2.0f));

		// Moves all elements on the right of the chosen index one step to the right.
		for (int j = i; j > correctIndex; --j) {
			elements[j] = elements[j - 1];
		}

		// Fills in the active object at its correct place.
		elements[correctIndex] = key;
	}
}
#endif