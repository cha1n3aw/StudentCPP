#include <math.h>
#include "pch.h"
#include <iostream>
using namespace std;
float a, b, result;
int dcs;
char dcs2;

void wrong_input()
{
	cout << " Wrong input, please, try again, honey! /n";
	cin.clear();
	cin.ignore(9999999, '\n');
}

int main()
{
	cout << " Hello, honey! What are the numbers? \n First number:";
	cin >> a;
	while (cin.fail()) {
		wrong_input();
		cin >> a;
	}
	cout << " Second number:";
	cin >> b;
	while (cin.fail()) {
		wrong_input();
		cin >> b;
	}
	cout << "\n What do you want to do, honey? \n 1. + \n 2. - \n 3. * \n 4. / \n 5. Second degree \n 6. Square root \n 7. Logarithm \n Your choice:";
	cin >> dcs;
	while (cin.fail() || dcs < 1 || dcs>7) {
		wrong_input();
		cin >> dcs;
	}
	switch (dcs) {
	case 1:
		result = a + b;
		break;
	case 2:
		result = a - b;
		break;
	case 3:
		result = a * b;
		break;
	case 4:
		result = a / b;
		break;
	}
	}
	cout << " Your result, honey: " << result;
	cout << " Do you want to try again, honey? Type Y if yes, N if no \n";
	cin >> dcs2;
	while (dcs2 != 'Y' && dcs2 != 'y' && dcs2 != 'N' && dcs2 != 'n') {
		wrong_input();
		cin >> dcs2;
	}
	if (dcs2 == 'Y' || dcs2 == 'y') main();
	else return 0;
}
