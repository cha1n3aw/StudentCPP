// Calculator.cpp
#include <math.h>
#include "pch.h"
#include <iostream>
using namespace std;
float a, b, result, result2, base;
int dcs;
char dcs2;
int main()
{
	cout << " Hello, honey! What are the numbers? \n First number:";
	cin >> a;
	while (cin.fail()) {
		cout << " Wrong input, please, try again, honey \n First number:";
		cin.clear();
		cin.ignore(9999999, '\n');
		cin >> a;
	}
	cout << " Second number:";
	cin >> b;
	while (cin.fail()) {
		cout << " Wrong input, please, try again, honey \n Second number:";
		cin.clear();
		cin.ignore(9999999, '\n');
		cin >> b;
	}
	cout << "\n What do you want to do, honey? \n 1. + \n 2. - \n 3. * \n 4. / \n 5. Second degree \n 6. Square root \n 7. Logarithm \n Your choice:";
	cin >> dcs;
	while (cin.fail() || dcs < 1 || dcs>7) {
		cout << " Wrong input, please, try again, honey \n Your choice:";
		cin.clear();
		cin.ignore(9999999, '\n');
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
	case 5: {
		result = a * a;
		result2 = b * b;
	}
			break;
	case 6: {
		result = sqrt(a);
		result2 = sqrt(b);
	}
			break;
	case 7: {
		cout << "Please, type the base of the logarithm, honey:";
		cin >> base;
		while (cin.fail() || a <= 0) {
			cout << "Wrong input, please, try again, honey \n Logarithm base:";
			cin.clear();
			cin.ignore(999999, '\n');
			cin >> base;
		}
		result = log(a) / log(base);
		result2 = log(b) / log(base);
	}
	}
	if (dcs > 0 && dcs < 5) cout << " Your result, honey: " << result;
	else cout << " First result, honey: " << result << "\n Second result, honey: " << result2 << endl;
	cout << " Do you want to try again, honey? Type Y if yes, N if no \n";
	cin >> dcs2;
	while (dcs2 != 'Y' && dcs2 != 'y' && dcs2 != 'N' && dcs2 != 'n') {
		cout << " Wrong input, please, try again, honey /n Type Y for yes, N for no";
		cin.clear();
		cin.ignore(9999999, '\n');
		cin >> dcs2;
	}
	if (dcs2 == 'Y' || dcs2 == 'y') main();
	else return 0;
}
