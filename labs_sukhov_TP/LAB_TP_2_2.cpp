#include <iostream>
#include<time.h>

using namespace std;

int main()
{
	int chislo;
	int input;
	int tries = 10;
	int win = 0;
	srand(time(0));
	chislo = rand() % 1000 + 1;
	cout << "\nYou should guess a number from 0 to 1000\n";
	do
	{
		cout << "You have " << tries;
		if (tries == 1) cout << " try\n\n";
		else  cout << " tries\n\n";
		cin >> input;
		while (input > 1000 || input < 0)
		{
			cout << "\nChislo ot 0 do 1000!\n";
			cin >> input;
		}
		if (input < chislo)
		{
			cout << "Zagadannoe chislo bolshe\n";
			tries--;
		}
		if (input > chislo)
		{
			cout << "Zagadannoe chislo menshe\n";
			tries--;
		}
		if (tries == 0)
		{
			cout << "\nTi ne ugadal, chislo bilo " << chislo << endl;
			win++;
		}
		if (chislo == input)
		{
			cout << "\nTi ugadal\n";
			win++;
		}
	} 
	while (win != 1);
	cout << "\n----------------------------------------\n";
	main();
}

	
