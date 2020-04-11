#include <iostream>
#include <map>

using namespace std;

struct indices
{
	int low;
	int high;
};


int main(void)
{
	cout << "Enter N" << endl;
	int N;
	cin >> N;
	int* input = new int[N];
	for (int i = 0; i < N; ++i)
	{
		cin >> input[i];
	}

	cout << "Enter n" << endl;
	int n;
	cin >> n;


	map<int,int> hashTable;
	struct indices result{-1,-1};
	for (int sum =0,i = 0; i < N; ++i)
	{
		sum += input[i];

		if (sum == n)
		{
			result.low=0;
			result.high=i;
		}
		else
		{

			if (hashTable.find(sum) == hashTable.end())
			{
				hashTable[sum]=i;
			}

			if (hashTable.find(sum-n) != hashTable.end())
			{
				result.low=(hashTable.find(sum-n))->second+1;
				result.high=i;
			}
		}

	}

	if (result.high == -1)
	{
		cout << "Not Found" << endl;
	}
	else
	{
		printf("Length of longest subarray is %d\n",result.high - result.low + 1);
		printf("Index from %d to %d.\n",result.low,result.high);
	}

	return 0;
}