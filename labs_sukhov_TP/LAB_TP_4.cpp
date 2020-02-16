#include <iostream>
using namespace std;
double sum;
double n;
double summ(double n)
{
	if (n>0) sum = summ(n - 1) + 1 / n;
	return sum;
}
int main()
{
	cin >> n;
	cout << summ(n) << endl;
	sum = 0;
	main();
}