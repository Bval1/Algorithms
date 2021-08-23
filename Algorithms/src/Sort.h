#pragma once

template <typename T>
size_t Partition(T arr[], size_t left, size_t right)
{
	size_t pivot = left + (rand() % (right - left));

	const T p = arr[pivot];		// pivot value
	size_t i = left + 1;			// start pivot index at 2nd element
	size_t temp;

	temp = arr[pivot];
	arr[pivot] = arr[left];
	arr[left] = temp;			// move pivot value to front

	for (size_t j = 1 + left; j < right; j++)
	{
		if (arr[j] < p)
		{
			temp = arr[i];
			arr[i] = arr[j];
			arr[j] = temp;
			i++;
		}
	}

	temp = arr[left];
	arr[left] = arr[i - 1];
	arr[i - 1] = temp;		// move pivot value to its place

	return (i - 1);			// return index of pivot value

}


template<typename T>
T* Merge(T left[], T right[], size_t len1, size_t len2, size_t& count)
{

	size_t i = 0, j = 0;

	size_t size = len1 + len2;
	T* output = new T[size];
	for (size_t n = 0; n < size; n++)
	{
		if (i == len1 && j == len2)
		{
			output[n] = left[i] < right[j] ? left[i] : right[i];
			output[n + 1] = output[n] == left[i] ? right[i] : left[i];

		}
		else if (i >= len1)			// left list exhausted
		{
			output[n] = right[j];
			j++;
		}
		else if (j >= len2)			// right list exhausted
		{
			output[n] = left[i];
			i++;

		}
		else if (left[i] <= right[j])
		{
			output[n] = left[i];
			i++;

		}
		else if (left[i] > right[j])		// split inversion
		{
			output[n] = right[j];
			j++;
			//count += (len1 - i);		// inversion count = # of elem remaining in left array as you're doing a merge from right array
		}
	}
	return output;
}


template<typename T>
T* MergeSort(T arr[], size_t size)			// O(logN)
{
	static const size_t initSize = size;
	static size_t count = 0;

	if (size == 0 || size == 1)
		return arr;

	const size_t len1 = size / 2;
	const size_t len2 = size % 2 == 0 ? size / 2 : (size / 2 + 1);


	T* left = (T*)alloca(sizeof(T) * len1);
	T* right = (T*)alloca(sizeof(T) * len2);
	
	for (size_t i = 0; i < len1; i++)
		left[i] = arr[i];

	for (size_t i = len1; i < size; i++)
		right[i - len1] = arr[i];

	left = MergeSort(left, len1);			// recursively divide
	right = MergeSort(right, len2);


	T* res = Merge<T>(left, right, len1, len2, count);		// sort and merge

	/*if (len1 + len2 == initSize)
		std::cout << count << "\n";*/
	return res;
}


template <typename T>
T* QuickSort(T arr[], size_t left, size_t right)			// O(logN)
{
	if (left == right)
		return arr;

	size_t i = Partition(arr, left, right);
	size_t len1 = i - left;
	size_t len2 = right - i;
	QuickSort(arr, left, i);			// will stop at pivot index
	QuickSort(arr, i + 1, right);		// don't include pivot index 
	
	return arr;
}



