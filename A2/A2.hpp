#ifndef A2_HPP
#define A2_HPP

#include <algorithm>

template <class T>
void Merge(T* elements, T* left, T* right, int nrOfElements, int leftNrOfElements, int rightNrOfElements)
{
	int i = 0, j = 0, k = 0;

	while (j < leftNrOfElements and k < rightNrOfElements)
	{
		if (left[j] <= right[k])
		{
			elements[i] = left[j];
			++j;
		}
		else
		{
			elements[i] = right[k];
			++k;
		}
		++i;
	}

	while (j < leftNrOfElements)
	{
		elements[i] = left[j];
		++i;
		++j;
	}
	while (k < rightNrOfElements)
	{
		elements[i] = right[k];
		++i;
		++k;
	}
}

template <class T>
void Mergesort(T elements[], int nrOfElements)
{
	if (nrOfElements <= 1) {
		return;
	}

	int leftNrElements = nrOfElements / 2;
	int rightNrElements = nrOfElements - leftNrElements;
	T* left = new T[leftNrElements];
	T* right = new T[rightNrElements];

	for (int i = 0; i < leftNrElements; ++i) {
		left[i] = elements[i];
	}
	for (int i = 0; i < rightNrElements; ++i) {
		right[i] = elements[leftNrElements + i];
	}

	Mergesort(left, leftNrElements);
	Mergesort(right, rightNrElements);
	Merge(elements, left, right, nrOfElements, leftNrElements, rightNrElements);
}

//void Merge(T* elements, int startIndex, int midIndex, int endIndex)
template <class T>
void MergeBook(T elements[], int start, int mid, int end)
{
	int leftNrElements = mid - start + 1;
	int rightNrElements = end - mid;
	T* left = new T[leftNrElements];
	T* right = new T[rightNrElements];
	for (int i = 0; i < leftNrElements; ++i) {
		left[i] = elements[start + i];
	}
	for (int i = 0; i < rightNrElements; ++i) {
		right[i] = elements[mid + i + 1];
	}

	int currentLeftIndex = 0;
	int currentRightIndex = 0;
	int currentResultIndex = start;

	while (currentLeftIndex < leftNrElements && currentRightIndex < rightNrElements) {
		if (left[currentLeftIndex] <= right[currentRightIndex]) {
			elements[currentResultIndex] = left[currentLeftIndex];
			currentLeftIndex += 1;
		}
		else {
			elements[currentResultIndex] = right[currentRightIndex];
			currentRightIndex += 1;
		}
		currentResultIndex += 1;
	}

	while (currentLeftIndex < leftNrElements) {
		elements[currentResultIndex] = left[currentLeftIndex];
		currentLeftIndex += 1;
		currentResultIndex += 1;
	}
	while (currentRightIndex < rightNrElements) {
		elements[currentResultIndex] = right[currentRightIndex];
		currentRightIndex += 1;
		currentResultIndex += 1;
	}
}

template <class T>
void MergeSortBookRecursion(T elements[], int start, int end)
{
	if (start >= end) {
		return;
	}
	int mid = (start + end) / 2;
	MergeSortBookRecursion(elements, start, mid);
	MergeSortBookRecursion(elements, mid + 1, end);
	MergeBook(elements, start, mid, end);
}

template <class T>
void MergesortBook(T elements[], int nrOfElements)
{
	MergeSortBookRecursion(elements, 0, nrOfElements - 1);
}

template <class T>
int PartitionLomuto(T elements[], int start, int end)
{
	T pivot = elements[end];
	int highIndexLeft = start - 1;
	for (int i = start; i < end; ++i) {
		if (elements[i] < pivot) {
			highIndexLeft += 1;
			std::swap(elements[highIndexLeft], elements[i]);
		}
	}
	std::swap(elements[highIndexLeft + 1], elements[end]);

	return highIndexLeft + 1;
}

template <class T>
void QuicksortLomutoRecursive(T elements[], int start, int end)
{
	if (start < end)
	{
		int pivot = PartitionLomuto(elements, start, end);
		QuicksortLomutoRecursive(elements, start, pivot - 1);
		QuicksortLomutoRecursive(elements, pivot + 1, end);
	}
}

template <class T>
void QuicksortLomuto(T elements[], int nrOfElements)
{
	QuicksortLomutoRecursive(elements, 0, nrOfElements - 1);
}

template <class T>
int PartionHoare(T elements[], int start, int end)
{
	T pivot = elements[start];
	int leftCompare = start - 1;
	int rightCompare = end + 1;
	while (true) {
		do {
			leftCompare++;
		} while (elements[leftCompare] < pivot);

		do {
			rightCompare--;
		} while (elements[rightCompare] > pivot);

		if (leftCompare < rightCompare) {
			std::swap(elements[leftCompare], elements[rightCompare]);
		}
		else {
			return rightCompare;
		}
	}
}

template <class T>
void QuicksortHoareRecursive(T elements[], int start, int end)
{
	if (start < end) {
		int pivot = PartionHoare(elements, start, end);
		QuicksortHoareRecursive(elements, start, pivot);
		QuicksortHoareRecursive(elements, pivot + 1, end);
	}
}

template <class T>
void QuicksortHoare(T elements[], int nrOfElements)
{
	QuicksortHoareRecursive(elements, 0, nrOfElements - 1);
}

template <class T>
void QuicksortHoareImproved(T elements[], int nrOfElements)
{

}

template <class T>
int MedianOfThree(T elements[], int start, int end)
{
	int mid = (start + end) / 2;
	if ((elements[start] <= elements[mid] && elements[mid] <= elements[end]) || (elements[start] >= elements[mid] and elements[mid] >= elements[end]))
		return mid;
	if ((elements[mid] <= elements[start] && elements[start] <= elements[end]) || (elements[mid] >= elements[start] and elements[start] >= elements[end]))
		return start;
	return end;
}

template <class T>
void QuicksortHoareImprovedMedian3(T elements[], int nrOfElements)
{

}


template <class T>
void Heapsort(T elements[], int nrOfElements)
{

}

#endif
