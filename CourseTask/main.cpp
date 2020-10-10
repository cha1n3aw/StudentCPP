#include <iostream>
#include <string.h>
#include <fstream>
using namespace std;
typedef unsigned uint;


struct Book
{
	char* author;
	char* name;
	char* year;
	int count;

	Book(char* authorPar, char* namePar, char* yearPar, unsigned countPar = 1)
	{
		author = new char[strlen(authorPar)+1];
		strcpy(author, authorPar);

		name = new char[strlen(namePar)+1];
		strcpy(name, namePar);

		year = new char[strlen(yearPar)+1];
		strcpy(year, yearPar);

		count = countPar;
	}

	Book(){}
};

class CollectionElem
{
public:
	char* key;
	Book value;

	CollectionElem(char* author, char* name, char* year, unsigned count = 1)
	{
		value = Book(author, name, year, count);
		key = new char[strlen(author)+1];
		strcpy(key, author);
	}

	CollectionElem(){}

	void IncreaseCount()
	{
		value.count++;
	}

	void DecreaseCount()
	{
		value.count--;
	}

	void Print()
	{
		cout << value.author << ", \"" << value.name << "\", " << value.year << ", " << value.count << endl;
	}
};

class Library
{
private:
	CollectionElem* array;
	int size;

public:
	Library()
	{
		size = 0;
		array = new CollectionElem();
	}

	void IncreaseArraySize()
	{
		CollectionElem* newArray = new CollectionElem[size+1];
		for (int i = 0; i < size; i++)
			newArray[i] = array[i];
		array = newArray;
	}

	void DecreaseArraySize()
	{
		CollectionElem* newArray = new CollectionElem[size-1];
		for (int i = 0; i < size-1; i++)
			newArray[i] = array[i];
		array = newArray;
	}

	CollectionElem* Copy()
	{
		CollectionElem* newArray = new CollectionElem[size];
		for (int i = 0; i < size; i++)
			newArray[i] = array[i];

		return newArray;
	}

	void Swap(int firstIndex, int secondIndex)
	{
		CollectionElem temp = array[firstIndex];
		array[firstIndex] = array[secondIndex];
		array[secondIndex] = temp;
	}

	void Swap(CollectionElem* collection, int firstIndex, int secondIndex)
	{
		CollectionElem temp = collection[firstIndex];
		collection[firstIndex] = collection[secondIndex];
		collection[secondIndex] = temp;
	}

	void Add(char* author, char* name, char* year, unsigned count = 1)
	{
		int index = Find(author, name, year); 
		if(index != -1)
		{
			array[index].IncreaseCount();
		}
		else
		{
			IncreaseArraySize();
			array[size] = CollectionElem(author, name, year, count);
			size++;
		}
	}

	void DeleteEdition(char* author, char* name, char* year)
	{
		int index = Find(author, name, year); 
		if(index != -1)
		{
			array[index].DecreaseCount();
			if(array[index].value.count <= 0)
			{
				Swap(index, size-1);
				DecreaseArraySize();
				size--;
			}
		}
	}

	int Find(char* author, char* name, char* year)
	{
		for(int i = 0; i < size; i++)
		{
			if(strcmp(author, array[i].value.author) == 0)
				if(strcmp(name, array[i].value.name) == 0)
					if(strcmp(year, array[i].value.year) == 0)
						return i;
		}
		return -1;
	}

	void PrintSortedByAuthor()
	{
		CollectionElem* newArray = Copy();

		for(int i = 0; i < size-1; i++)
			for(int j = 0; j < size-i-1; j++)
				if(strcmp(newArray[j].key, newArray[j+1].key) > 0)
					Swap(newArray, j, j+1);

		Print(newArray);
	}

	void PrintSortedByYear()
	{
		CollectionElem* newArray = Copy();

		for(int i = 0; i < size-1; i++)
			for(int j = 0; j < size-i-1; j++)
				if(strcmp(newArray[j].value.year, newArray[j+1].value.year) > 0)
					Swap(newArray, j, j+1);

		Print(newArray);
	}

	void Print()
	{
		for(int i = 0; i < size; i++)
		{
			cout << i+1 << ". ";
			array[i].Print();
		}
	}

	void Print(CollectionElem* collection)
	{
		for(int i = 0; i < sizeof(collection)-1; i++)
		{
			cout << i+1 << ". ";
			collection[i].Print();
		}
	}

	void Clear()
	{
		size = 0;
		array = new CollectionElem();
	}

	void Save()
	{
		ofstream fout("data.txt");

		for(int i = 0; i < size; i ++)
			fout << array[i].value.author << ";" << array[i].value.name << ";" << array[i].value.year << ";" << array[i].value.count <<endl;
	}

	int Load()
	{
		Clear();
		// �������� �������� �� ������������� �����
		ifstream fin("data.txt");
		if (fin.is_open())
		{
			char buffer[256] = "";
			int flag = 0; // 0 - ������ ������, 1 - ������ ��������, 2 - ������ ��� �������, 3 - ������ ���-�� �������
			while(!fin.eof())
			{
				fin.getline(buffer, 256);

				char* author; char* name; char* year; char* count;
				// ��� ������ temp
				if(strcmp(buffer, "") != 0)
				{
					char temp[80];
					int tempIndex = 0;
					
					for(int i = 0; i < sizeof(buffer); i++)
					{
						if (buffer[i] != ';')
						{
							temp[tempIndex] = buffer[i];
							tempIndex++;
						}
						else
						{
							temp[tempIndex] = '\0';
							if (flag == 0)
							{
								author = new char[strlen(temp)+1];
								strcpy(author, temp);
								flag = 1;
								tempIndex = 0;
								continue;
							}
							if (flag == 1)
							{
								name = new char[strlen(temp)+1];
								strcpy(name, temp);
								flag = 2;
								tempIndex = 0;
								continue;
							}
							if(flag == 2)
							{
								year = new char[strlen(temp)+1];
								strcpy(year, temp);
								flag = 3;
								tempIndex = 0;
								continue;
							}
							if(flag == 3)
							{
								count = new char[strlen(temp)+1];
								strcpy(count, temp);
								Add(author, name, year, atoi(count));
								tempIndex = 0;
								flag = 0;
								break;
							}
						}

						if (buffer[i] == '\0')
						{
							count = new char[strlen(temp)+1];
							strcpy(count, temp);
							Add(author, name, year, atoi(count));
							tempIndex = 0;
							flag = 0;
							break;
						}
					}

				}
				author = ""; name = "";	year = ""; count = "";
			}
			return 1;
		}
		else
			cout << "���� � ������� �� ������. ������ �� ��������� ������? 0 - ���, 1 - ��" << endl;

		return 0;
	}
};


void main()
{
	setlocale(LC_ALL, "rus");

	Library* libraryPtr = new Library();
	Library library = *libraryPtr;
	
	int result = library.Load();

	if (!result)
	{
		cout << "���� �� ������. �������� ����� �������� ������.\n�������� ����� ���� �������� ������\n";
		library.Save();
	}

	uint k = 0;
	do
	{
		char author[80]; char name[80]; char year[80];

		cout
			<< "1	- ������� ����������\n"
			<< "2	- �������� ������\n"
			<< "3 	- ������� ������\n"
			<< "4	- ������������� �� ������\n"
			<< "5	- ������������� �� ����\n"
			<< "0	- ��������� � �����\n";

		cin >> k;
		switch (k)
		{
			case 1:
			{
				 cout << "���������� ��������" << endl; 
				 library.Print();
				 break;
			}
			case 2:
			{
				cout << "������� ������: ";
				scanf("%s",author);
				cout << "������� ��������: ";
				scanf("%s",name);  
				cout << "������� ���: ";
				scanf("%s",year); 

				library.Add(author, name, year); 
				break;
			}
			case 3:
			{
					library.Print();
					cout << endl;
					 cout << "������� �������, ������ ������ �������" << endl; 
					char temp[256];
					cin >> temp;
					int i = atoi(temp);
					library.DeleteEdition(author, name, year);
					cout << endl;
					library.Print();
					break;
			}
		
		case 4:
		{
			cout << "�������� �������" << endl; 
			library.Print();
			cout << endl;
			 cout << "�������������� �� ������" << endl; 
			library.PrintSortedByAuthor();
					break;
		}
		case 5:
		{
			cout << "�������� �������" << endl;
			library.Print();
			cout << endl;
			cout << "�������������� �� ����" << endl;
			library.PrintSortedByYear();
			break;
		}
		case 0:
		{
			cout << "���� ��������, ������� ������� Enter ��� ������" << endl;
			library.Save();
		}
		}
	}
	while (k != 0);
		
	cout << endl;
	system("pause");
}