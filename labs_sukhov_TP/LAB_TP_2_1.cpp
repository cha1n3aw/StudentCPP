#include <iostream>
using namespace std;
int main()
{
	int chislo; //vhodnoe chislo
	int n = 0; //chislo itteraciy
    int divider = 2; //delitel
	cin >> chislo;
	cout << chislo << " = ";
	while (chislo > 1)
	{
		while (chislo % divider == 0)
		{
			if (n > 0) cout << " * ";
			cout << divider;
			chislo = chislo / divider;
			n++; 
		}
		divider++;
	}
	cout << "\n";
	main();
}