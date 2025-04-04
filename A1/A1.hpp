#ifndef A1_HPP
#define A1_HPP
#include <algorithm>	// Included for use of std::swap()

template <class T>
int LinearSearch(T elements[], int nrOfElements, T element)
{
	//Implementera en iterativ linj�rs�kning.

	for (int i = 0; i < nrOfElements; ++i) {
		if (element[i] == element) {
			return i;
		}
	}

	return -1;
}

template <class T>
void Selectionsort(T elements[], int nrOfElements)
{
	// Implementera en iterativ selectionsort.
}

template <class T>
void Insertionsort(T elements[], int nrOfElements)
{
	// Implementera en iterativ insertionsort.
}

template <class T>
int BinarySearch(T elements[], int nrOfElements, T element)
{
	// Implementera en iterativ bin�rs�kning.
	return -11;
}

template <class T>
int LinearSearchRecursive(T elements[], int nrOfElements, T element)
{
	// Implementera en rekursiv linj�rs�kning.
	// Anropa er egna rekursiva funktion h�rifr�n.
	return -11;
}

template <class T>
int BinarySearchRecursive(T elements[], int nrOfElements, T element)
{
	// Implementera en rekursiv bin�rs�kning.
	// Anropa er egna rekursiva funktion h�rifr�n.
	return -11;
}

template <class T>
void BinaryInsertionsort(T elements[], int nrOfElements)
{
	// Implementera en iterativ insertionsort d�r du s�ker efter r�tt plats att l�gga in elementet m.h.a. bin�rs�kning.
}
#endif
