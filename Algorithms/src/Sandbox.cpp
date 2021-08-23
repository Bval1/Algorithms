#include "pch.h"
#if 1

#include "Sort.h"
#include "Select.h"


struct Timer
{
	std::chrono::steady_clock::time_point start, end;
	std::chrono::duration<float> duration;
	Timer()
	{
		start = std::chrono::high_resolution_clock::now();
	}
	~Timer()
	{
		end = std::chrono::high_resolution_clock::now();
		duration = end - start;
		float ms = duration.count() * 1000.0f;
		std::cout << "Timer took " << ms << " ms" << "\n";
	}
};

int main()
{
	std::srand(time(NULL));

#define EXAMPLE 3

#if EXAMPLE == 1
	const int size = 12;
	int arr[size] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12 };

#elif EXAMPLE == 2
	const int size = 11;
	int arr[size] = { 54, 35, 58, 23, 121, 1000, 32, 5, 12, 15, 3 }; // median = 15

#elif EXAMPLE == 3
	const int size = 6;
	int arr[size] = { 6, 5, 4, 3, 2, 1 };	//inversion count = 15

#elif EXAMPLE == 4
	const int size = 6;
	int arr[size] = { 22, 3, 9, 2, 8, 6 }; // inversion count = 3 // median = 8 or 6

#elif EXAMPLE == 5
	constexpr int size = 100000;
	int arr[size];
	for (int i = 0; i < size; i++) 
		arr[i] = rand();
#endif


#define TEST 1

#if TEST == 1					// MergeSort
	Timer* timer = new Timer;
	int* output = MergeSort(arr, size);
	delete timer;

	for (int i = 0; i < size; i++)
		std::cout << output[i] << " ";

#elif TEST == 2					// QuickSort
	Timer* timer = new Timer;
	int* output = QuickSort(arr, 0, size);
	delete timer;
	for (int i = 0; i < size; i++)
		std::cout << output[i] << " ";

#elif TEST == 3						// Find ith value w/ Random Select
	Timer* timer = new Timer;
	const int position = size / 2 + 1;
	int res = RandomSelect(arr, 0, size, position);
	delete timer;
	for (int i = 0; i < size; i++)
		std::cout << arr[i] << " ";
	const char* index = position % 10 == 1 ? "st" : position % 10 == 2 ? "nd" : position % 10 == 3 ? "rd" : "th";
	std::cout << "\n" << position << index << " value is " << res << "\n";

#elif TEST == 4					// QuickSelect
	int value = 121, i = 0;

	Timer* timer = new Timer;
	int res = QuickSelect(arr, 0, size, value);
	delete timer;

	while (arr[i] != value )
	{
		std::cout << arr[i] << " ";
		i++;
		if (i == size)
			break;
	}
	std::cout << arr[i] << "\n";
	const char* x = res != NULL ? " found\n" : " not found\n";
	std::cout << "\n" << value << x;

#endif
	std::cin.get();
}


#endif 