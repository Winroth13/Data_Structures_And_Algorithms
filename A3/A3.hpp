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
void InnerCountingsort(T elements[], int nrOfElements, int digit)
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
		InnerCountingsort(elements, nrOfElements, d);
	}
}

template <class T>
void InnerBucketsort(T elements[], int nrOfElements, int digit)
{
	T* B[10];
	int count[10] = { 0 };
	int modulus = 1;
	int divisor = 1;

	for (int i = 0; i < 10; ++i) {
		B[i] = new T[nrOfElements];
	}

	for (int i = 1; i < digit; ++i) {
		divisor *= 10;
	}
	modulus = divisor * 10;

	for (int i = 0; i < nrOfElements; ++i) {
		B[DigitNr(elements[i], divisor, modulus)][count[DigitNr(elements[i], divisor, modulus)]] = elements[i];
		count[DigitNr(elements[i], divisor, modulus)]++;
	}

	int position = 0;

	for (int i = 0; i < 10; ++i) {
		for (int j = 0; j < count[i]; ++j) {
			elements[position] = B[i][j];
			position++;
		}
	}

	for (int i = 0; i < 10; ++i) {
		delete[] B[i];
	}
}

template <class T>
void RadixsortBuckets(T elements[], int nrOfElements)
{
	T max = *(std::max_element(elements, elements + nrOfElements));
	int nrDigits = std::to_string(max).length();

	for (int d = 1; d < nrDigits + 1; ++d) {
		InnerBucketsort(elements, nrOfElements, d);
	}
}

int LetterIndex(std::string element, int letterNr) {
	if (element.length() < letterNr) {
		return 0;
	}
	else {
		return (int)element[element.length() - letterNr] - 96;
	}
}

void InnerStringBucketsort(std::string elements[], int nrOfElements, int letterNr)
{
	std::string* B[27];
	int count[27] = { 0 };
	int modulus = 1;
	int divisor = 1;

	for (int i = 0; i < 27; ++i) {
		B[i] = new std::string[nrOfElements];
	}

	for (int i = 0; i < nrOfElements; ++i) {
		B[LetterIndex(elements[i], letterNr)][count[LetterIndex(elements[i], letterNr)]] = elements[i];
		count[LetterIndex(elements[i], letterNr)]++;
	}

	int position = 0;

	for (int i = 0; i < 27; ++i) {
		for (int j = 0; j < count[i]; ++j) {
			elements[position] = B[i][j];
			position++;
		}
	}

	for (int i = 0; i < 27; ++i) {
		delete[] B[i];
	}
}

void RadixsortStrings(std::string elements[], int nrOfElements)
{
	std::string max = *(std::max_element(elements, elements + nrOfElements, [](const std::string& i, const std::string& j) {return i.length() < j.length(); }));
	int nrLetters = max.length();

	for (int n = 1; n < nrLetters + 1; ++n) {
		InnerStringBucketsort(elements, nrOfElements, n);
	}
}

#endif