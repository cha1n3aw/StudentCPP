// lab1_lvl0_2.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include <iostream>
#include <string>

int main()
{
	char dot;
	int day, mnth, year, age, tday, tmnth, tyear;
	char name[30] = "";
	dot == '.';
    std::cout << " Hello, stranger! What's your name? \n ";
	std::cin >> name;
	std::cout << " What's your date of birth? \n ";
	std::cin >> day >> dot >> mnth >> dot >> year;
	std::cout << " What's the date today? \n ";
	std::cin >> tday >> dot >> tmnth >> dot >> tyear;
	age = tyear - year;
	if ((tmnth-1)*12+tday < (mnth - 1) * 12 + day) age--;
	std::cout << " Hello, " << name <<  ". You're " << age << " years old.";
}

