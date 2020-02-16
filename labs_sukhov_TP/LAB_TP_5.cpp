#include <iostream>
#include <ctime>

using namespace std;

void arrayOut(int* array1, int count) {
	for (int i = 0; i < count; i++)
		cout << array1[i] << ' ';
}

void bubbleSort(int* array1, int count) {
	clock_t start, stop;
	start = clock();
	int temp = 0;
	for (int i = 0; i < count; i++) {
		for (int j = 0; j < count - i - 1; j++) {
			if (array1[j] > array1[j + 1]) {
				temp = array1[j];
				array1[j] = array1[j + 1];
				array1[j + 1] = temp;
			}
		}
	}
	stop = clock();
	cout << (stop - start) / CLK_TCK;
}

void insertionSort(int* array1, int count) {
	clock_t start, stop;
	start = clock();
	int temp = 0;
	for (int i = 0, j; i < count; i++) {
		j = i - 1;
		temp = array1[i];
		while (array1[j] > temp && j >= 0) {
			array1[j + 1] = array1[j];
			j--;
			array1[j + 1] = temp;
		}
	}
	stop = clock();
	cout << (stop - start) / CLK_TCK;
}

int* arrCopy(int* array1, int count) {
	int* arr2 = new int[count];
	for (int i = 0; i < count; i++) {
		arr2[i] = array1[i];
	}
	return arr2;
}

int main()
{
	srand(time(NULL));
	int n = 100000;
	int* arr = new int[n];
	for (int i = 0; i < n; i++) arr[i] = rand() % 10;
	int* arr2 = arrCopy(arr, n);
	cout << "Sortirivka vstavkami: ";
	insertionSort(arr, n);
	cout << "\nBubble Sort: ";
	bubbleSort(arr2, n);
}