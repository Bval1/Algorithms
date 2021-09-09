#include "pch.h"

// Aligns 2 strings in most optimal way
#if 0
std::pair<std::string, std::string> SequenceAlignment(const std::string& a, const std::string& b)
{
	int m = a.length();
	int n = b.length();
	int gp = 1;				// gap penalty
	int** A = new int*[m + 1];
	for (int i = 0; i < m + 1; i++)
		A[i] = new int[n + 1];

	for (int i = 0; i < m + 1; i++)
		A[i][0] = i * gp;
	for (int i = 0; i < n + 1; i++)
		A[0][i] = i * gp;

	int p;
	for (int i = 1; i < m + 1; i++)
	{
		for (int j = 1; j < n + 1; j++)
		{
			p = a[i - 1] == b[j - 1] ? 0 : 2;			// penalty of 2 for mismatched chars
			int res1 = std::min(A[i - 1][j - 1] + p, A[i - 1][j] + gp);
			A[i][j] = std::min(res1, A[i][j - 1] + gp);
		}
	}

	std::cout << "Penalty = " << A[m][n] << "\n";			// penalty of optimal solution

	// Reconstruction
	int i = m, j = n;
	std::string x;
	std::string y;
	int min;
	int temp;

	while (i > 0 || j > 0)
	{
		if (i == 0) 
		{
			x += " ";
			j--;
		}
		else if (j == 0)
		{
			y += " ";
			i--;
		}

		else 
		{
			p = a[i - 1] == b[j - 1] ? 0 : 2;
			temp = std::min(A[i - 1][j - 1] + p, A[i - 1][j] + gp);
			min = std::min(temp, A[i][j - 1] + gp);

			if (min == A[i - 1][j - 1] + p)		// case 1 was used
			{	
				x += a[i - 1];
				y += b[j - 1];
				i--;
				j--;
			}
			else if (min == A[i][j - 1] + gp)	// case 2, match xi with gap
			{
				x += ' ';
				y += b[j - 1];
				j--;
			}
			else if (min == A[i - 1][j] + gp)	// case 3, match yj with gap
			{
				y += ' ';
				x += a[i - 1];
				i--;
			}
		}
	}
	std::reverse(x.begin(), x.end());
	std::reverse(y.begin(), y.end());

	return { x, y };	
}

int main()
{
	/*
		A G G G C T
		A - G G C A
	*/
	//std::string a = "AGGGCT", b = "AGGCA";
	std::string a = "Helo", b = "Hellow";
	//std::string a = "Hero", b = "Hello";
	auto result = SequenceAlignment(a, b);
	std::cout << result.first << "\n";
	std::cout << result.second << "\n";

}
#endif