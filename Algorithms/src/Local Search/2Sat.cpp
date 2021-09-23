#include "pch.h"
#if 1

void TwoSat(int n)	// Papadimitrious Algorithm, 2n^2 * log_2(n) run time
{
	bool c1 = 0, c2 = 0, c3 = 0, c4 = 0;
	bool x1, x2, x3, x4;

	for (int i = 0; i < 2 * log2(n); i++)
	{
		x1 = rand() % 2 == 0 ? 1 : 0, x2 = rand() % 2 == 0 ? 1 : 0, 
		x3 = rand() % 2 == 0 ? 1 : 0, x4 = rand() % 2 == 0 ? 1 : 0;

		for (int j = 0; j < 2 * pow(n, 2.0); j++)
		{
			if (x1 || x2)
				c1 = 1;
			else
				c1 = 0;
			if (!x1 || x3)
				c2 = 1;
			else
				c2 = 0;
			if (x3 || x4)
				c3 = 1;
			else
				c3 = 0;
			if (!x2 || !x4)
				c4 = 1;
			else
				c4 = 0;
			if (c1 && c2 && c3 && c4)
			{
				printf("x1 is %i, x2 is %i, x3 is %i, x4 is %i\n", x1, x2, x3, x4);
				return;
			}
			else
			{
				if (!c1)
				{
					if (rand() % 2 == 0)
						x1 = !x1;
					else
						x2 = !x2;
				}
				else if (!c2)
				{
					if (rand() % 2 == 0)
						x1 = !x1;
					else
						x3 = !x3;
				}
				else if (!c3)
				{
					if (rand() % 2 == 0)
						x3 = !x3;
					else
						x4 = !x4;
				}
				else if (!c4)
				{
					if (rand() % 2 == 0)
						x2 = !x2;
					else
						x4 = !x4;
				}
			}
		}


	}
	printf("Unsatisfiable\n");
	return;
}

int main()
{
	std::srand(time(NULL));

	TwoSat(4);
	std::cin.get();
}
#endif