#include <iostream>
#include <list>

using namespace std;

struct triplet
{
	int num[3];
};

int **dparr;
int *inarr;

int calcxor(int i, int j)
{
	if (dparr[i][j-i] != -1)
	{
		return dparr[i][j-i];
	}
	else 
	{
		if (j == i)
		{
			dparr[i][j-i] = inarr[i];
			return dparr[i][j-i];
		}
		else
		{
			dparr[i][j-i] = calcxor(i,j-1) ^ inarr[j];
			return dparr[i][j-i];
		}
	}

}

int main(void)
{
	int n = 0;
	cin >> n;

	inarr = new int[n];
	for (int i = 0; i < n; ++i)
	{
		cin >> inarr[i];
	}

	dparr = new int*[n];
	for (int i = 0; i < n; ++i)
	{
		dparr[i] = new int[n-i];
		for (int j = 0; j < n-i; ++j)
		{
			dparr[i][j] = -1;
		}
	}

	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < n-i; ++j)
		{
			calcxor(i,j+i);
		}
	}

	int count=0;
	list<struct triplet> tripletList;
	for (int i = 0; i < n-1; ++i)
	{
		for (int j = i+1; j < n; ++j)
		{
			for (int k = j; k < n; ++k)
			{
				if (calcxor(i,j-1) == calcxor(j,k))
				{
					count++;
					struct triplet temp;
					temp.num[0]=i+1;
					temp.num[1]=j+1;
					temp.num[2]=k+1;
					tripletList.push_back(temp);
				}
			}
		}
	}

	cout << count << endl;

	list<struct triplet> :: iterator it;
	for(it = tripletList.begin(); it != tripletList.end(); ++it)
	{
		printf("(%d %d %d)\n",it->num[0],it->num[1],it->num[2]);
	}	

}