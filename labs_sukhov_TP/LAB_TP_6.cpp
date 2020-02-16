#include <iostream>

using namespace std;

void merge(char line1[255], char line2 [255], int offset)
{
	for (int j = offset; j - offset < strlen(line2); j++)
		line1[j - 1] = line2[j - offset]; //j-1 dlya togo chto bi schitat s 1 a ne s 0
}

int main()
{
	int offset;
	char line1[100];
	char line2[100];
	cin >> line1;
	cin >> line2;
	cin >> offset;
	merge(line1, line2, offset);
	cout << "Result=" << line1 << endl;
	main();
}

