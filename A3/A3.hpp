#ifndef A3_HPP
#define A3_HPP
#include <algorithm>
#include <iostream>
#include <cmath>
#include <string>

template <class T>
void Countingsort(T elements[], int nrOfElements)
{
	T* B = new T[nrOfElements];
	T max = *(std::max_element(elements, elements + nrOfElements));
	int* C = new int[max + 1] {0};

	for (int i = 0; i < nrOfElements; ++i) {
		C[elements[i]]++;
	}

	for (int i = 1; i < max + 1; ++i) {
		C[i] += C[i - 1];
	}

	for (int i = nrOfElements - 1; i > -1; --i) {
		C[elements[i]]--;
		B[C[elements[i]]] = elements[i];
	}

	for (int i = 0; i < nrOfElements; ++i) {
		elements[i] = B[i];
	}

	delete[] B;
	delete[] C;
}

template <class T>
int DigitNr(T element, int divisor, int modulus) {
	return ((element % modulus) / divisor);
}

template <class T>
void InnerCountingSort(T elements[], int nrOfElements, int digit)
{
	T* B = new T[nrOfElements];
	int max = 10;
	int* C = new int[max] {0};
	int modulus = 1;
	int divisor = 1;


	for (int i = 1; i < digit; ++i) {
		divisor *= 10;
	}
	modulus = divisor * 10;

	for (int i = 0; i < nrOfElements; ++i) {
		C[DigitNr(elements[i], divisor, modulus)]++;
	}

	for (int i = 1; i < max; ++i) {
		C[i] += C[i - 1];
	}

	for (int i = nrOfElements - 1; i > -1; --i) {
		C[DigitNr(elements[i], divisor, modulus)]--;
		B[C[DigitNr(elements[i], divisor, modulus)]] = elements[i];
	}

	for (int i = 0; i < nrOfElements; ++i) {
		elements[i] = B[i];
	}

	delete[] B;
	delete[] C;
}

template <class T>
void RadixsortCounting(T elements[], int nrOfElements)
{
	T max = *(std::max_element(elements, elements + nrOfElements));
	int nrDigits = std::to_string(max).length();

	for (int d = 1; d < nrDigits + 1; ++d) {
		InnerCountingSort(elements, nrOfElements, d);
	}
}


template <class T>
void RadixsortBuckets(T elements[], int nrOfElements)
{

}

void RadixsortStrings(std::string elements[], int nrOfElements)
{

}

#endif
