// Lab14.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include <Windows.h>
#include <iostream>

using namespace std;

int main()
{
	setlocale(NULL, "RUS");
	int array[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	int size = sizeof(array);

	//1.создать динам.кучу с размером = нач.рамеру массива целых чисел
	//доступ дб не синхронизованный
	cout << "Задание 1." << endl;
	HANDLE h = HeapCreate(HEAP_NO_SERIALIZE, size, size);
	if (!h)
	{
		puts("Куча не была создана");
		return -1;
	}
	int* arr = NULL;
	//выделить память куче
	arr = (int*)HeapAlloc(h, NULL, size);//размер выделяемой памяти
	for (int i = 0; i < size / sizeof(int); ++i)
	{
		arr[i] = array[i];
		cout << arr[i] << endl;
	}


	//2.добавить справа новый массив, т.е.динам.расшир.рамер массива на 1 + использовать метод HeapReAlloc
	cout << "\nЗадание 2." << endl;
	int changesize;
	//изменить размер блока памяти
	arr = (int*)HeapReAlloc(h, NULL, arr, size += 4);
	for (int i = 0; i < 1; i++)
	{
		arr[(size - i * 4) / sizeof(int)] = 11;
	}
	cout << "arr[size] = " << arr[size / sizeof(int)] << endl;

	
	//3.удалить из массива правый элемент
	cout << "\nЗадание 3." << endl;
	cout << "Введите размер: " << endl;
	cin >> changesize;
	arr = (int*)HeapReAlloc(h, NULL, arr, size -= 4 * changesize);
	cout << "arr[size] = " << arr[(size / sizeof(int)) - 1] << endl;


	//4.Вставить новый эл-т в массив внутрь со сдвигом на 1 эл-т вправо
	cout << "\nЗадание 4." << endl;
	int index;
	cout << "Введите индекс для вставки элемента: " << endl;
	cin >> index;
	cout << "Введите значение элемента для вставки: " << endl;
	int value;
	cin >> value;
	arr = (int*)HeapReAlloc(h, NULL, arr, size + 4);
	for (int i = size / sizeof(int); i >= index; --i)
	{
		arr[i + 1] = arr[i];
	}
	arr[index] = value;
	for (int i = 0; i < (size / sizeof(int)) + 1; ++i)
		cout << "d - " << arr[i] << endl;


	//5.позвол.удалить из массива 1 эл-т внутри со сдивом правой части влево
	cout << "\nЗадание 5." << endl;
	int idx;
	cout << "Введите индекс для удаления: " << endl;
	cin >> idx;
	arr = (int*)HeapReAlloc(h, NULL, arr, size);
	for (int i = idx; i < size / sizeof(int); ++i)
	{
		arr[i] = arr[i + 1];
	}
	for (int i = 0; i < (size / sizeof(int)); ++i)
		cout << "d - " << arr[i] << endl;

	system("pause");
	return 0;
}

