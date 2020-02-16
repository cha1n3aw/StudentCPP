#include<time.h>
#include <iostream>
using namespace std;
int main()
{
	int i, j;
	int X = 9;
	int Y = 9;
	double* a, * b;
	a = new double[X * Y];
	b = new double[X * Y];
	srand(time(0));
	for (i = 0; i < X; i++)
		for (j = 0; j < Y; j++)
		{
			*(a + i * Y + j) = rand() % 31;
		}
	for (i = 0; i < X; i++)
		for (j = 0; j < Y; j++)
		{
			*(b + i * Y + j) = *(a + i * Y + j);
			if ((i * Y + j) == 10 || (i * Y + j) == 13 || (i * Y + j) == 16 || (i * Y + j) == 37 || (i * Y + j) == 40 || (i * Y + j) == 43 || (i * Y + j) == 64 || (i * Y + j) == 67 || (i * Y + j) == 70)
				* (b + i * Y + j) = *(a + i * Y + j - 10) + *(a + i * Y + j - 9) + *(a + i * Y + j - 8) + +*(a + i * Y + j - 1) + *(a + i * Y + j + 1) + *(a + i * Y + j + 8) + *(a + i * Y + j + 9) + *(a + i * Y + j + 10);
		}
	cout << "Исходная матрица A:\n";
	for (i = 0; i < X; cout << endl, i++)
		for (j = 0; j < Y; j++)
			cout << *(a + i * Y + j) << "\t";
	cout << "\nРезультирующая матрица B:\n";
	for (i = 0; i < X; cout << endl, i++)
		for (j = 0; j < Y; j++)
			cout << *(b + i * Y + j) << "\t";
	delete[]a;
	delete[]b;
	return(0);
}