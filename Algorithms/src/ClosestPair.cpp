#include "pch.h"
#if 0
#include <cmath>
#define LOG(prompt, x) std::cout << prompt << x << "\n"
struct Vector2
{
	int x, y;

	void Print()
	{
		std::cout << x << ", " << y << "\n";
	}
};

struct Vec2Pair
{
	Vector2 x;
	Vector2 y;
	float delta;

	void Print()
	{
		std::cout << "Closest Pairs\n";
		x.Print();
		y.Print();
		std::cout << "Delta: " << delta << "\n";
	}
};

float Distance(Vector2 v1, Vector2 v2)
{
	int x = pow((v1.x - v2.x), 2);
	int y = pow((v1.y - v2.y), 2);
	return sqrt(x + y);
}

Vector2* VecMergeSort(Vector2* left, Vector2* right, int len1, int len2, char sortby)
{

	int i = 0, j = 0;
	int leftval, rightval, outputval;

	const int size = len1 + len2;
	Vector2* output = new Vector2[size];
	for (int n = 0; n < size; n++)
	{
		
		if (sortby == 'x')
		{
			leftval = left[i].x;
			rightval = right[j].x;
			outputval = output[n].x;
		}
		else if (sortby == 'y')
		{
			leftval = left[i].y;
			rightval = right[j].y;
			outputval = output[n].y;
		}
		else
		{
			throw("Must be x or y");
			
		}


		if (i == len1 && j == len2)
		{
			output[n] = leftval < rightval ? left[i] : right[i];
			output[n + 1] = outputval == leftval ? right[i] : left[i];

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
		else if (leftval <= rightval)
		{
			output[n] = left[i];
			i++;

		}
		else if (leftval > rightval)		// split inversion
		{
			output[n] = right[j];
			j++;
		}
	}

	return output;
}

Vector2* VecDivide(Vector2* arr, const int size, char sortby)
{
	if (size == 0 || size == 1)
		return arr;

	const int len1 = size / 2;
	const int len2 = size % 2 == 0 ? size / 2 : (size / 2 + 1);

	Vector2* left = new Vector2[len1];
	Vector2* right = new Vector2[len2];


	for (int i = 0; i < len1; i++)
		left[i] = arr[i];

	for (int i = len1; i < size; i++)
		right[i - len1] = arr[i];

	left = VecDivide(left, len1, sortby);			// recursively divide
	right = VecDivide(right, len2, sortby);


	Vector2* res = VecMergeSort(left, right, len1, len2, sortby);		// sort and merge

	delete[] left;
	delete[] right;


	return res;
}

Vec2Pair ClosestSplitPair(Vector2* x_sorted, Vector2* y_sorted, const int size, float delta)
{
	// get median x coordinate
	int split = size % 2 == 0 ? size / 2 : size / 2 + 1;
	Vector2 median = x_sorted[split];


	Vector2 output1 = { NULL, NULL };
	Vector2 output2 = { NULL, NULL };
	float best = delta;


	Vector2* s_y = new Vector2;
	int k = 0;
	for (int i = 0; i < size; i++)
	{
		if (Distance(y_sorted[i], median) < delta)
		{
			s_y[k] = y_sorted[i];
			k++;
		}
	}

	int n = k > 7 ? 7 : k;
	for (int i = 0; i < k - 7; i++)
	{

		for (int j = 0; j < n; j++)
			if (Distance(s_y[i], s_y[i + j]) < delta)
			{
				best = Distance(s_y[i], s_y[i + j]);
				output1 = s_y[i];
				output2 = s_y[i + j];
			}
	}
	delete s_y;
	return { output1, output2, best };
}


Vec2Pair ClosestPair(Vector2* vector, const int size)
{
	Vector2* xSort = VecDivide(vector, size, 'x');
	Vector2* ySort = VecDivide(vector, size, 'y');
	
	float min_x = Distance(xSort[0], xSort[size - 1]);
	float min_y = Distance(ySort[0], ySort[size - 1]);
	

	Vector2 output_x[2];
	Vector2 output_y[2];

	for (int i = 0; i < size - 1; i++)
	{
		float distance_x = Distance(xSort[i], xSort[i + 1]);
		if (distance_x < min_x)
		{
			min_x = distance_x;
			output_x[0] = xSort[i];
			output_x[1] = xSort[i + 1];

		}
	}


	for (int i = 0; i < size - 1; i++)
	{
		float distance_y = Distance(ySort[i], ySort[i + 1]);
		if (distance_y < min_y)
		{
			min_y = distance_y;
			output_y[0] = ySort[i];
			output_y[1] = ySort[i + 1];

		}
	}
	
	
	float delta = min_x <= min_y ? min_x : min_y;
	Vec2Pair pair;

	if (delta == min_x)
	{
		pair = { output_x[0], output_x[1], delta };		
	}
	else
	{
		pair = { output_y[0], output_y[1], delta };
	}


	Vec2Pair splitpair = ClosestSplitPair(xSort, ySort, size, delta);
	

	if (splitpair.delta < delta)
		return splitpair;
	else
		return pair;
	
}



int main()
{
	const int size = 6;
	//Vector2 vectors[size] = { { 10, 2 }, { 2, 14 }, { 3, 4 }, { 9, 10 }, { 6, 7 }, { 4, 11 } };
	Vector2 vectors[size] = { { 1, 1 }, { 2, 10 }, { 22, 44 }, { 10, 15 }, { 6, 7 }, { 4, 11 } };
#if 0
	Vector2* xSort = VecDivide(vectors, size, 'x');
	for (int i = 0; i < size; i++)
		xSort[i].Print();

	std::cout << "-----------------------\n";

	Vector2* ySort = VecDivide(vectors, size, 'y');
	for (int i = 0; i < size; i++)
		ySort[i].Print();

	std::cout << "-----------------------\n";
	auto closestpairs = ClosestPair(vectors, size);
	closestpairs.Print();

	LOG("Delta: ", closestpairs.delta);
	
	LOG("Delta x: ", Distance({ 6, 7 }, { 9, 10 }));
	LOG("Delta y: ", Distance({ 4, 11 }, { 2, 14 }));


	float delta = closestpairs.delta;
	Vec2Pair split = ClosestSplitPair(xSort, ySort, size, delta);
	
	if (split.delta < delta)
		LOG("Min Delta is split delta: ", split.delta);
	else
	{
		LOG("Min Delta: ", closestpairs.delta);
	}
#endif
	Vec2Pair res = ClosestPair(vectors, size);
	res.Print();

	LOG("Distance: ", Distance(res.x, res.y));
	std::cin.get();
};
#endif