#include <iostream>
#include <string>

using namespace std;

string kopeiki(int cost) {
	switch (cost % 100 >= 10 && cost % 100 <= 20)
	{
	case 1:
	{
		return " kopeek\n";
		break;
	}
	case 0:
	{
		if (cost % 10 == 0) return " kopeek\n";
		if (cost % 10 == 1) return " kopeika\n";
		if (cost % 10 >= 2 && cost % 10 <= 4) return " kopeiki\n";
		if (cost % 10 >= 5 && cost % 10 <= 9) return " kopeek\n";
	}
	}
}

string rubli(int cost) {
	switch (cost / 100 % 100 >= 10 && cost / 100 % 100 <= 20)
	{
	case 1:
	{
		return " rublei ";
		break;
	}
	case 0:
	{
		if (cost / 100 % 10 == 0) return " rublei ";
		if (cost / 100 % 10 == 1) return " rubl ";
		if (cost / 100 % 10 >= 2 && cost / 100 % 10 <= 4) return " rublya ";
		if (cost / 100 % 10 >= 5 && cost / 100 % 10 <= 9) return " rublei ";
	}
	}
}

void print(int cost) {
	cout << cost / 100 << rubli(cost) << cost % 100 << kopeiki(cost);
}

int main()
{
	int cost;
	cin >> cost;
	print(cost);
	main();
}