// Lab7_Potoki.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include <iostream>
#include <windows.h>
#include "string.h"

DWORD WINAPI myThread(LPVOID lpParameter)
{
	unsigned int counter = 0;
	while (counter < 20)
	{
		Sleep(1000);
		counter++;
		printf("\n Counter = %d", counter);
	}
	return 0;
}

int tmain()
{
	unsigned int myCounter = 0;
	DWORD myThreadID;
	HANDLE myHandle = CreateThread(  // Создает поток для выполнения в виртуальном адресном пространстве вызывающего процесса
		0,           // Если lpThreadAttributes NULL, дескриптор не может быть унаследован
		0,           // Исходный размер стека в байтах умолчанию(1 мегабайт)
		myThread,    // Имя функции, выполняемой потоком
		&myCounter,  // Ссылка на переменную, передающую параметры
		0,           // Поток запускается сразу после создания
		&myThreadID  // Указатель на переменную, которая получает идентификатор потока
	);
	Sleep(5000);
	printf("\n Main Process ....");
	TerminateThread(myHandle, 0); // Завершает поток
	getchar();
	return 0;
}

