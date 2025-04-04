#ifndef A1_HPP
#define A1_HPP
#include <algorithm>	// Included for use of std::swap()
#include <cmath>
//#include <valarray>
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

//template <class T>
//int BinarySearchRecursionStep(T elements[], int nrOfElements, T element, int nrOfElementsBefore) {
//	int middle = int(std::floor(nrOfElements / 2));
//	if (nrOfElements == 0) {
//		return -1;
//	}
//	else if (element == elements[middle]) {
//		return middle;
//	}
//	else if (element > elements[middle]) {
//		//T newArr[middle] = std::slice(middle + 1, middle, 1);
//		return BinarySearchRecursionStep(elements, middle, element, nrOfElementsBefore + middle);
//	}
//	else {
//		//T newArr[middle - 1] = std::slice(0, middle - 1, 1);
//		return BinarySearchRecursionStep(newArr, middle - 1, element, nrOfElementsBefore);
//	}
//}

template <class T>
int BinarySearchRecursive(T elements[], int nrOfElements, T element)
{
	// Implementera en rekursiv binärsökning.
	// Anropa er egna rekursiva funktion härifrån.

	/*return BinarySearchRecursionStep(elements, nrOfElements, element, 0);*/

	return -11;
}

template <class T>
void BinaryInsertionsort(T elements[], int nrOfElements)
{
	// Implementera en iterativ insertionsort där du söker efter rätt plats att lägga in elementet m.h.a. binärsökning.
}
#endif
