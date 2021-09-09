#include "pch.h"

#if 0
struct Item
{
	const char* name = "";
	int value = 0;
	int weight = 0;
};

Item* Knapsack(Item* items, int n, int w)	// n = number of items, w = capacity
{
	int** A = new int* [n + 1];		// takes into account case of 0 items, its values = 0
	for (int i = 0; i < n + 1; i++)
	{
		A[i] = new int[w];
		if (i == 0)
		{
			for (int j = 0; j < w; j++)
				A[i][j] = 0;
		}
	}

	int w_i, v_i;
	for (int i = 1; i < n + 1; i++)
	{
		for (int x = 0; x < w; x++)
		{
			w_i = items[i - 1].weight;
			v_i = items[i - 1].value;
			
			if (w_i > x)				
				A[i][x] = A[i - 1][x];	// current item exceeds residual weight, take previous item only
			else
				A[i][x] = std::max(A[i - 1][x], (A[i - 1][x - w_i]) + v_i); 
		}
	}
	std::cout << "Optimal value is: " << A[n][w - 1] << "\n";

	// Reconstruct items taken by A
	int i = n, j = w, k = 0;		// i = item index (0 to n), j = weight index (0 to w-1)
	Item* res = new Item[n];

	while (i > 0)
	{
		if (A[i][j - 1] == 0)		// value = 0, ignore item
			i--;
		else if (A[i][j - 1] > A[i - 1][j - 1])		// A took this item, 2nd case won
		{
			res[k] = items[i - 1];
			k++;
			i--;
			j -= items[i - 1].weight;  // subtract weight of this items from rows
		}
		else
		{							// A didn't take this item, but took previous item
			res[k] = items[i - 2];
			k++;
			i -= 2;
		}
	}
	
	return res;
}
int main()
{
	Item a = { "A", 3, 4 }, b = { "B", 2, 3 }, c = { "C", 4, 2 }, d = { "D", 4, 3};
	constexpr int n = 4, w = 6;		

	Item items[4] = { a, b, c, d };

	Item* res = Knapsack(items, n, w);
	for (int i = 0; i < n; i++)
	{
		if (res[i].name != "")
			std::cout << res[i].name << ", value: " << res[i].value << " weight: " << res[i].weight << "\n";
	}

	std::cin.get();
}
#endif