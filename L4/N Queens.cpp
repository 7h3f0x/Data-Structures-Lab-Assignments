#include <iostream>

using namespace std;

int count;

bool isSafeSpot(bool** chessboard,int n,int row,int column)
{
	for (int i = 0; i < column; ++i)
	{
		if (chessboard[row][i] != false)
		{
			return false;
		}
	}

	for (int i = row,j = column; j>=0 && i < n; ++i,--j)
	{
		if (chessboard[i][j] != false)
		{
			return false;
		}
	}

	for (int i = row,j = column; i >=0 && j >=0; --i,--j)
	{
		if (chessboard[i][j] != false)
		{
			return false;
		}
	}

	return true;
}

bool NQueens(bool** chessboard,int n,int column)
{
	if (column == n)
	{
		count++;
		cout << endl;

		printf("Combination %d:\n",count);
		for (int i = 0; i < n; ++i)
		{
			for (int j = 0; j < n; ++j)
			{
				cout << (int)chessboard[i][j] << " ";
			}
			cout << endl;
		}

		cout << endl;

		return true;
	}

	bool result = false;

	for (int i = 0; i < n; ++i)
	{
		if (isSafeSpot(chessboard,n,i,column))
		{
			chessboard[i][column] = true;

			result = NQueens(chessboard,n,column+1) || result;

			chessboard[i][column] = false;
		}
	}

	return result;

}


void NQueensHandler(bool** chessboard,int n)
{
	if (NQueens(chessboard,n,0) == false)
	{
		cout << "No Such Combination can be found for given N" << endl;
	}
	else
	{
		printf("Total number of combinations: %d\n", count);
	}
}



int main(void)
{
	cout << "Enter N" << endl;
	int N;
	cin >> N;

	bool** chessboard = new bool*[N];
	for (int i = 0; i < N; ++i)
	{
		chessboard[i] = new bool[N];
		for (int j = 0; j < N; ++j)
		{
			chessboard[i][j] = false;
		}
	}

	count = 0;

	NQueensHandler(chessboard,N);

	return 0;
}