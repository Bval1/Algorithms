#include "pch.h"

#if 0
class BloomFilter
{
	std::bitset<384> b;					// expected input size (12) * bits per object in set S (32 bit ints)
	int size;							// prime number < bitset size
	std::array<int, 6> coeff; 			// random coeffcients

public:
	BloomFilter(std::bitset<384> _b, int _size)
		:b(_b), size(_size), coeff(std::array<int, 6>())
	{
		for (int& i : coeff)
		{
			std::srand(time(NULL));
			int n = rand();
			i = n;
		}
	}
	
	
	std::bitset<384> ShowBits()
	{
		return b;
	}

	int Hash(int key)
	{
		int res = 0;	
		for (int i : coeff)
			res += (i * key) % size;
		
		return res % size;
	}

	void Insert(int key)
	{
		int hashkey = Hash(key);
		b[hashkey] = 1;
	}

	void Delete(int key)
	{
		int hashkey = Hash(key);
		b[hashkey] = 0;
	}
	bool Lookup(int key)
	{
		int hashkeys = Hash(key);
		
		if (b[hashkeys] == 0)
		{
			std::cout << key << " is not in set\n";
			return false;
		}
		
		std::cout << key << " is already in set\n";
		return true;
	}

	
};

int main()
{

	const int size = 12;
	std::array<int, 12> arr = { 924, 523, 326, 214, 421, 643, 393, 572, 183, 385, 964, 826 };
	std::bitset<384> b;
	std::cout << b << "\n";

	int prime = 383;
	BloomFilter hashset = BloomFilter(b, prime);
	for (int i : arr)
		hashset.Insert(i);

	std::cout << hashset.ShowBits() << "\n";
	hashset.Delete(643);
	for (int i : arr)
		hashset.Lookup(i);

#if 1
	int count = 0;
	for (int i = 0; i < 1000; i++)
	{
		if (hashset.Lookup(i))
		{
			count++;
		}
	}
	std::cout << "False Positives count ~ " << count - arr.size() << "\n";
#endif
	std::cin.get();
}
#endif 