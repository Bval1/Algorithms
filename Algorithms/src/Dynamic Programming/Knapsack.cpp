#include "pch.h"
/*
Dynamic programming paradigm:
Optimal solutions must necessarily be composed of optimal solutions to smaller sub-problems.
*/
#if 0

struct Item
{
	const char* name = "";
	int value = 0;
	int weight = 0;
};

// Dynamic programming algorithm #1: for case of small W capacity (assume W and sizes w_i are integers)
Item* Knapsack(Item* items, int n, int w)	// n = number of items, w = capacity   O(nW)
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
	std::cout << "Optimal value is for knapsack capacity: " << A[n][w - 1] << "\n";

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

// Dynamic Algorithm/Heuristic #2 (assume values v_i are ints) running time = O(n^2v_max), where v_max = max item value
template <int N>
int KnapsackRevisted(std::array<Item, N> items, int n, int w, float e)  // e = specified max allowed error/epsilon
{
	auto cmp = [](Item a, Item b) { return a.value > b.value; };
	std::sort(items.begin(), items.end(), cmp);
	int vMax = items[0].value;
	float m = (e * vMax) / n;
	int nvMax = n * vMax;

	int** A = new int* [n + 1];		// takes into account case of 0 items
	for (int i = 0; i < n + 1; i++)
	{
		A[i] = new int[nvMax];
		if (i == 0)
		{
			for (int j = 0; j < nvMax; j++)
			{
				if (j == 0)
					A[i][j] = 0;
				else
					A[i][j] = INT32_MAX;
			}
		}
	}

	for (int i = 1; i < n + 1; i++)
	{
		for (int x = 0; x < nvMax; x++)
		{
			int w_i = items[i - 1].weight;
			int v_i = items[i - 1].value;
			if (v_i <= x)
			{
				A[i][x] = A[i - 1][x - v_i] == INT32_MAX ? A[i - 1][x] :
					std::min(A[i - 1][x], w_i + A[i - 1][x - v_i]);
			}

			else
				A[i][x] = std::min(A[i - 1][x], w_i + 0);
		}
	}

	// scan through largest batch of subproblems and select largest x such that A[n,x] <= W
	for (int x = nvMax - 1; x >= 0; x--)
	{
		if (A[n][x] <= w)
		{
			return x;
		}

	}

}
int main()
{
#define KNAPSACK 2

	Item a = { "A", 3, 4 }, b = { "B", 2, 3 }, c = { "C", 4, 2 }, d = { "D", 4, 3};
	constexpr int n = 4, W = 6;	
	Item items[4] = { a, b, c, d };

	int v1 = 502, v2 = 500, v3 = 500, w1 = 501, w2 = 500, w3 = 500;
	constexpr int n2 = 3, W2 = 1000;
	Item a2 = { "1", v1, w1 }, b2 = { "2", v2, w2 }, c2 = { "3", v3, w3 };
	Item items2[3] = { a2, b2, c2};

#if KNAPSACK == 1
	Item* res = Knapsack(items, n, W);
	//Item* res = Knapsack(items2, n2, W2);  // not accurate for this example
	for (int i = 0; i < n; i++)
	{
		if (res[i].name != "")
			std::cout << res[i].name << ", value: " << res[i].value << " weight: " << res[i].weight << "\n";
	}
#elif KNAPSACK == 2
	float ep = 0.01;
	std::array<Item, n> item_arr = { a, b, c, d };
	std::array<Item, 3> item_arr2 = { a2, b2, c2 };

	int opt_value = KnapsackRevisted(item_arr, n, W, ep);
	//int opt_value = KnapsackRevisted(item_arr2, n2, W2, ep);
	std::cout << "Optimal value is for knapsack capacity: " << opt_value << "\n";
#endif

	std::cin.get();

}
#endif