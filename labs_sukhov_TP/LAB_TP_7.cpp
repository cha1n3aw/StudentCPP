#include <iostream>

using namespace std;

void copeiki_out(int copeiki) {
	int check;
	if (copeiki / 10 == 1) check = 3;
	else if ((copeiki % 10) == 1)
		check = 1;
	else if (((copeiki % 10) > 1) && ((copeiki % 10) < 5))
		check = 2;
	else check = 3;
	switch (check)
	{
	case 1:
		cout << copeiki << " Kopeika" << endl;
		break;
	case 2:
		cout << copeiki << " Kopeiki" << endl;
		break;
	case 3:
		cout << copeiki << " Kopeek" << endl;
		break;
	}
}

void rubli_out(int rubli) {
	int check2;
	if (((rubli % 100) / 10) == 1) check2 = 3;
	else if ((rubli % 10) == 1)
		check2 = 1;
	else if (((rubli % 10) > 1) && ((rubli % 10) < 5))
		check2 = 2;
	else check2 = 3;
	switch (check2)
	{
	case 1:
		cout << rubli << " Rubl ";
		break;
	case 2:
		cout << rubli << " Rublya ";
		break;
	case 3:
		cout << rubli << " Rubley ";
		break;
	}
}

struct recipt {
	string name;
	int copeiki;
	int rubli;
	int alltogether;
};

void Print_itog(recipt itog) {
	recipt a;
	a.alltogether = itog.alltogether;
	a.alltogether /= 100;
	itog.alltogether %= 100;
	cout << "Itog: ";
	rubli_out(a.alltogether);
	copeiki_out(itog.alltogether);
}

void output(recipt pokypka[], recipt total) {
	for (int i = 0; i < 5; i++) {
		cout << pokypka[i].name << ": ";
		rubli_out(pokypka[i].rubli);
		copeiki_out(pokypka[i].copeiki);
	}
	Print_itog(total);
}




int main()
{
	recipt* purchase = new recipt[5];
	recipt itog;
	itog.alltogether = 0;
	for (int i = 0; i < 5; i++) {
		cout << "Vvedite nazvanie i tsenu " << i + 1 << " predmeta: ";
		cin >> purchase[i].name >> purchase[i].copeiki;
		itog.alltogether += purchase[i].copeiki;
		purchase[i].rubli = purchase[i].copeiki / 100;
		purchase[i].copeiki = purchase[i].copeiki % 100;
	}
	output(purchase, itog);
	delete[] purchase;
	main();
}