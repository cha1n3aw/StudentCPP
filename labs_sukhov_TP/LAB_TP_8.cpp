#include <iostream> 

using namespace std;

int desk[8][8];
void reset(int i, int j)
{
	for (int x = 7; x >= 0; --x)
	{
		--desk[x][j];
		--desk[i][x];
		int k;
		k = j - i + x;
		if (k >= 0 && k < 8)
			--desk[x][k];
		k = j + i - x;
		if (k >= 0 && k < 8)
			--desk[x][k];
	}
	desk[i][j] = 0;
}

void setting(int i, int j)
{
	for (int x = 7; x >= 0; --x)
	{
		++desk[x][j];
		++desk[i][x];
		int k;
		k = j - i + x;
		if (k >= 0 && k < 8)
			++desk[x][k];
		k = j + i - x;
		if (k >= 0 && k < 8)
			++desk[x][k];
	}
	desk[i][j] = -1;
}

bool postan(int i)
{
	bool result = false;
	for (int j = 7; j >= 0; --j)
	{
		if (desk[i][j] == 0)
		{
			setting(i, j);
			if (i == 7)
				result = true;
			else
			{
				if (!(result = postan(i + 1)))
					reset(i, j);
			}
		}
		if (result)
			break;
	}
	return result;
}
int main()
{
	for (int i = 7; i >= 0; --i)
		for (int j = 7; j >= 0; --j)
			desk[i][j] = 0;
	postan(0);
	for (int i = 7; i >= 0; --i)
	{
		for (int j = 7; j >= 0; --j)
		{
			if (desk[i][j] == -1)
				cout << "F ";
			else
				cout << "0 ";
		}
		cout << endl;
	}
}