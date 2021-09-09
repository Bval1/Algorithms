#pragma once
#include "Sort.h"

// Returns ith smallest in unsorted array (1 being the smallest, size of arr the biggest)
template <typename T>
T RandomSelect(T arr[], size_t left, size_t right, size_t position)	// O(N), 1 recursion call instead of 2 like sorting
{

	size_t n = right - left;
	if (n == 0)
		return arr[0];

	size_t i = Partition(arr, left, right);

	if (i == position - 1)
		return arr[i];
	else if (i > position - 1)
		return RandomSelect(arr, left, i, position);		// take 1st part
	else if (i < position - 1)
		return RandomSelect(arr, i + 1, right, position);	// take 2nd part
}



// For unsorted array, returns value if found, NULL if not found
template <typename T>
T QuickSelect(T arr[], size_t left, size_t right, T value)	// O(N), 1 recursion call instead of 2 like in sorting
{

	size_t n = right - left;
	if (n == 0)
	{
		if (arr[0] == value)
			return arr[0];
		else
		{
			std::cout << value << " not found!\n";
			return NULL;
		}
	}

	size_t i = Partition(arr, left, right);

	if (arr[i] == value)
		return arr[i];
	else if (arr[i] > value)
		return QuickSelect(arr, left, i, value);		// take 1st part
	else if (arr[i] < value)
		return QuickSelect(arr, i + 1, right, value);	// take 2nd part
}
