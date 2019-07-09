#include <iostream>
#include <stack>
#include <string>

using namespace std;

struct multiple_buffers { double* digitbuffer; char* opbuffer; int digitstacksize; int opstacksize; }; //структура для возвращения буферов чисел и операторов
string stringremover(string expression); //прототип функции чистки строки от пробелов
void string_parsing(string); //прототип функции парсинга стринга
double stacktobuffer(); //прототип функции вычислений
double calculation(double* digitbuffer, char* opbuffer, int digitstacksize, int opstacksize); //прототип функции для вычисления
double brackets(double* digitbuffer, char* opbuffer, int digitstacksize, int opstacksize); //прототип функции для выделения выражения внутри скобок
stack <double> digitstack; //стек чисел
stack <char> opstack; //стек операторов

string stringremover(string expression)
{
	for (int i = 0; i < expression.length(); i++)
	{
		if (expression[i] == ' ')
		{
			for (int c = i; c < expression.length(); c++)
			{
				expression[c] = expression[c + 1];
			}
			expression.resize(expression.length() - 1);
			i--;
		}
	}
	return expression;
}

double brackets(double* digitbuffer, char* opbuffer, int digitstacksize, int opstacksize)
{
	int i = 0;
	int c = 0;
	int opening = 0;
	int closing = 0;
	int optempsize = 0;
	double* digittemp = new double[digitstacksize];
	char* optemp = new char[opstacksize];

	for (i = 0; i < opstacksize; i++)
	{
		if (opbuffer[i] == '(')
		{
			for (c = opstacksize - 1; c >= i; c--)
			{
				if (opbuffer[c] == ')')
				{
					closing = c;
					break;
				}
			}
			opening = i + 1;
			break;
		}
	}
	optempsize = closing - opening;
	c = 0;
	for (i = opening; i < closing; i++)
	{
		optemp[c] = opbuffer[i];
		c++;
	}
	c = 0;
	for (i = opening; i <= closing; i++)
	{
		digittemp[c] = digitbuffer[i];
		c++;
	}
	digitbuffer[opening - 1] = calculation(digittemp, optemp, optempsize + 1, optempsize);
	for (i = opening; i < opstacksize - optempsize; i++)
	{
		digitbuffer[i] = digitbuffer[i + optempsize + 2];
	}
	for (i = opening - 1; i < opstacksize - optempsize; i++)
	{
		opbuffer[i] = opbuffer[i + optempsize + 2];
	}
	return calculation(digitbuffer, opbuffer, digitstacksize, opstacksize);
}

double calculation(double* digitbuffer, char* opbuffer, int digitstacksize, int opstacksize)
{
	int i, c;

	for (i = 0; i < opstacksize; i++)
	{
		if (opbuffer[i] == '^')
		{
			digitbuffer[i] = pow(digitbuffer[i], digitbuffer[i + 1]);
			for (c = i; c < opstacksize - 1; c++)
			{
				digitbuffer[c + 1] = digitbuffer[c + 2];
				opbuffer[c] = opbuffer[c + 1];
			}
			digitstacksize--;
			opstacksize--;
			i--;
			continue;
		}
		if (opbuffer[i] == 'r')
		{
			digitbuffer[i] = pow(digitbuffer[i], 1 / digitbuffer[i + 1]);
			for (c = i; c < opstacksize - 1; c++)
			{
				digitbuffer[c + 1] = digitbuffer[c + 2];
				opbuffer[c] = opbuffer[c + 1];
			}
			digitstacksize--;
			opstacksize--;
			i--;
			continue;
		}
	}

	for (i = 0; i < opstacksize; i++)
	{
		if (opbuffer[i] == '*')
		{
			digitbuffer[i] = digitbuffer[i] * digitbuffer[i + 1];
			for (c = i; c < opstacksize - 1; c++)
			{
				digitbuffer[c + 1] = digitbuffer[c + 2];
				opbuffer[c] = opbuffer[c + 1];
			}
			digitstacksize--;
			opstacksize--;
			i--;
			continue;
		}
		if (opbuffer[i] == '/')
		{
			digitbuffer[i] = digitbuffer[i] / digitbuffer[i + 1];
			for (c = i; c < opstacksize - 1; c++)
			{
				digitbuffer[c + 1] = digitbuffer[c + 2];
				opbuffer[c] = opbuffer[c + 1];
			}
			digitstacksize--;
			opstacksize--;
			i--;
			continue;
		}
	}

	for (i = 0; i < opstacksize; i++)
	{
		if (opbuffer[i] == '+')
		{
			digitbuffer[i] = digitbuffer[i] + digitbuffer[i + 1];
			for (c = i; c < opstacksize - 1; c++)
			{
				digitbuffer[c + 1] = digitbuffer[c + 2];
				opbuffer[c] = opbuffer[c + 1];
			}
			digitstacksize--;
			opstacksize--;
			i--;
			continue;
		}
		if (opbuffer[i] == '-')
		{
			digitbuffer[i] = digitbuffer[i] - digitbuffer[i + 1];
			for (c = i; c < opstacksize - 1; c++)
			{
				digitbuffer[c + 1] = digitbuffer[c + 2];
				opbuffer[c] = opbuffer[c + 1];
			}
			digitstacksize--;
			opstacksize--;
			i--;
			continue;
		}
	}
	return (digitbuffer[0]);
}

void string_parsing(string expression)
{
	unsigned int i = 0; //переменная для счетчика
	double number = 0; //число которое записывается в стек
	char* a = new char[1]; //костыльный массив char для использования atoi
	double fraction = 1; //счетчик десятичной дроби в числе
	if (expression[0] == '-') //на случай если первое число будет отрицательным, то есть перед ним будет -
	{
		expression.resize(expression.length() + 1);
		for (i = expression.length(); i > 0; i--)
		{
			expression[i] = expression[i - 1]; //стринг увеличивается и сдвигается на 1 позицию
		}
		expression[0] = '0'; //а в нулевую записывается 0
	}

	for (i = 0; i < expression.length(); i++)
	{
		if (isdigit(expression[i]))
		{
			//костыль для использования atoi, i элемент из string пишется на нулевую позицию char массива
			a[0] = expression[i];
			//если показатель десятичной части числа равен единице то мы проводим обычное добавление к числу
			if (fraction == 1) number = (number * 10) + atoi(a);
			//если показатель десятичной части числа не равен дефолтной единице 
			//то мы делим на показатель и добавляем к числу
			else
			{
				number = number + (atoi(a) / fraction);
				fraction *= 10; //и увеличиваем показатель для следующего деления
			}
		}
		else
		{
			if (expression[i] == '(' || expression[i] == ')')
			{
				digitstack.push(0);
				opstack.push(expression[i]);
				fraction = 1;
				continue;
			}

			if (expression[i] == 'r' || (expression[i] != '.' && !isalpha(expression[i])))
			{
				opstack.push(expression[i]);
				fraction = 1;
				continue;
			}
			if (isalpha(expression[i]))
			{
				switch (expression[i])
				{
				case 'e':
				{
					digitstack.push(exp(1));
					break;
				}
				case 'p':
				{
					digitstack.push(atan(1.0) * 4);
					break;
				}
				}
				continue;
			}
		}
		if (expression[i] == '.') fraction *= 10;

		if (expression[i + 1] == '.') continue;

		if (!isdigit(expression[i + 1]))
		{
			digitstack.push(number);
			number = 0;
		}
	}
}

double stacktobuffer()
{
	int i = 0;
	int c = 0;
	int digitstacksize = digitstack.size();
	int opstacksize = opstack.size();
	double* digitbuffer = new double[digitstacksize];
	char* opbuffer = new char[opstacksize];

	for (i = digitstacksize - 1; i >= 0; i--)
	{
		digitbuffer[i] = digitstack.top();
		digitstack.pop();
	}

	for (i = opstacksize - 1; i >= 0; i--)
	{
		opbuffer[i] = opstack.top();
		opstack.pop();
	}

	for (i = 0; i < opstacksize; i++)
	{
		if (opbuffer[i] == '(')
		{
			c = -1;
			return brackets(digitbuffer, opbuffer, digitstacksize, opstacksize);
			break;
		}
	}
	if (c != -1) return calculation(digitbuffer, opbuffer, digitstacksize, opstacksize);
}

int main()
{
	string expression;
	getline(cin, expression);
	expression = stringremover(expression);
	string_parsing(expression);
	cout << "Result = " << stacktobuffer();
}