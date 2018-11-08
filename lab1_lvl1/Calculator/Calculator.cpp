// Calculator.cpp
#include <math.h>
#include "pch.h"
#include <iostream>
using namespace std;
float a, b, result, result2, base;
int dcs;
char dcs2;

void wrong_input()
{
	cout << " Wrong input, please, try again, honey! /n";
	cin.clear();
	cin.ignore(9999999, '\n');
}

float readNum()
{
    float f;
    cin>>f;
    while(cin.fail())
    {
        wrong_input();
        cin>>f;

    }
    cin.ignore(9999999,'\n');
    return f;
}

int main()
{
	do {
	cout << " Hello, honey! What are the numbers? \n First number:";
	a=readNum();
	cout << " Second number:";
	b=readNum();
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
			wrong_input();
			cin >> base;
		}
		result = log(a) / log(base);
		result2 = log(b) / log(base);
	}
	}
	if (dcs > 0 && dcs < 5) cout << " Your result, honey: \n" << result;
	else cout << " First result, honey: " << result << "\n Second result, honey: " << result2 << endl;
	cout << " Do you want to try again, honey? Type Y if yes, N if no \n";
	cin >> dcs2;
	while (dcs2 != 'Y' && dcs2 != 'y' && dcs2 != 'N' && dcs2 != 'n') {
		wrong_input();
		cin >> dcs2;
	}
	}
	while (dcs2!='n' && dcs2!='N' && dcs2=='y' && dcs2=='Y');
	return 0;
}

