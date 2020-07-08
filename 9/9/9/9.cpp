// 9.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include <iostream>
#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <windows.h>
#pragma warning (disable: 4996)
using namespace std;

HANDLE H = GetStdHandle(STD_OUTPUT_HANDLE);

//1. Создать массив для размещения строк
void  firstTask()
{
	int n;
	cout << "Введите размер массива\n";
	cin >> n;
	char **a = new char*[10];
	*a = (char*)malloc(n * sizeof(string));

	if (!*a) { cout << "Недостаточно памяти"; return; }

	cout << "Введите элементы массива (строки): \n";
	for (int i = 0; i < n; i++)
	{
		a[i] = new char[100];
		cin >> a[i];
	}

	cout << "\n Ваш массив:\n ";
	for (int i = 0; i < n; i++)
		cout << i + 1 << " элемент - " << a[i] << endl;

	free(*a);
}

//2. создать массив для размещения структуры
void secondTask()
{
	int i;
	struct MyStruct
	{
		int a;
		int b;
		char c;
	};
	MyStruct *abc = new MyStruct;
	abc = (struct MyStruct*)malloc(2 * sizeof(int) + sizeof(char));

	cout << "Введите a и b:\n";
	cin >> abc->a;
	cin >> abc->b;
	cout << "Введите c\n";
	cin >> abc->c;

	cout << "\n Структура: " << abc->a << "*" << abc->b << "=" << abc->c;
	free(abc);
}

//3. создать массив для размещения массива структур
void thirdTask()
{
	int i, n;
	struct MyStruct
	{
		int a;
		int b;
		float c;
	};
	cout << "Введите размер массива\n";
	cin >> n;

	MyStruct *abc = new MyStruct[n];
	abc = (struct MyStruct*)malloc(n*sizeof(MyStruct));

	cout << "Введите массив(a,b)\n";
	for (i = 0; i < n; i++)
	{
		cout << "Структура номер " << i + 1 << ":\n";
		cin >> abc[i].a >> abc[i].b;
		abc[i].c = ((float)abc[i].a * (float)abc[i].b);
	}

	cout << "Массив: \n";
	for (i = 0; i < n; i++)
		cout << i + 1 << " Структура " << abc[i].a << "*" << abc[i].b << "=" << abc[i].c << "\n";
	free(abc);
}


int  main()
{
	int i;

	setlocale(LC_ALL, "RUS");

	cout << "\n1. Массив для размещения строк.\n";
	cout << "2. Массив для размещения структуры.\n";
	cout << "3. Массив для размещения массива структур.\n";
	cout << "Choose\n";
	cin >> i;
	switch (i)
	{
	case 1: firstTask(); main(); break;
	case 2: secondTask(); main(); break;
	case 3: thirdTask(); main(); break;
	default: main(); break;
	}
	return 0;
}