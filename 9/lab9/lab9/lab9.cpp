// lab9.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include <stdio.h>
#include <conio.h>
#include <iostream>
#include <string.h>
#include <windows.h>
#pragma warning (disable: 4996)
using namespace std;

HANDLE H = GetStdHandle(STD_OUTPUT_HANDLE);

//1.	Создать массив для размещения строк
int firstTask()
{
	int i, n;
	cout << "Введите размер массива\n";
	cin >> n;
	char **a = new char*[10];
	for (int i = 0; i < 10; i++)
	{
		a[i] = new char[100];
	}
	cout << "Введите (строковый) массив, нажимая ENTER после каждого элемента\n";
	for (i = 0; i < n; i++)
		cin >> a[i];
	cout << "\n massiv\n";
	for (i = 0; i < n; i++)
		cout << i + 1 << " element - " << a[i] << endl; //вывод массива
	for (int i = 0; i < 10; i++)
	{
		delete[] a[i];
	}
	delete[] a;
	cout << "\nУдалено\n\n";
	system("pause");
	return 1;

}

int secondTask()
{
	int i;
	struct MyStruct
	{
		int a;
		int b;
		char c;
	};
	MyStruct *abc = new MyStruct;
	cout << "Введите a и b:\n";
	cin >> abc->a;
	cin >> abc->b;
	cout << "Введите c\n";
	cin >> abc->c;

	cout << "\n ENTER\n";
	cout << "Struct " << abc->a << "*" << abc->b << "=" << abc->c << endl;
	delete abc;
	cout << "\nУдалено\n\n";
	system("pause");
	return 1;
}

int thirdTask()
{
	int i, n;
	cout << "Введите размер массива\n";
	cin >> n;
	struct MyStruct
	{
		int a;
		int b;
		float c;
	};
	MyStruct *abc = new MyStruct[n];
	cout << "Введите массив(a,b)\n";
	for (i = 0; i < n; i++)
	{
		cout << "Структура номер " << i + 1 << ":\n";
		cin >> abc[i].a;
		cin >> abc[i].b;
		abc[i].c = ((float)abc[i].a * (float)abc[i].b);
	}
	cout << "\n massiv\n";
	for (i = 0; i < n; i++)
		cout << i + 1 << " Struct " << abc[i].a << "*" << abc[i].b << "=" << abc[i].c << endl; //вывод массива
	delete[] abc;
	cout << "\nУдалено\n\n";
	system("pause");
	return 1;

}

int  main()
{
	int i;
	system("title String");
	setlocale(LC_ALL, "RUS");
	//system("cls");		//очищаем экран консоли

	char p[256] = { "\n\n1. Создать массив для размещения строк.\n2. Создать массив для размещения структуры.\n3. Создать массив для размещения массива структур.\n" };
	cout << p << "Введите задание\n";
	cin >> i;
	switch (i)
	{
	case 1:if (firstTask() == 1) main();
		break;
	case 2:if (secondTask() == 1) main();
		break;
	case 3: if (thirdTask() == 1) main();
		break;
	default: main();
		break;
	}
	return 0;
}