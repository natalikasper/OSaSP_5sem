// Lab7_potoki_5.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include <windows.h>
#include <iostream>
#include "string.h"

int x;

DWORD WINAPI Read(void* lpParameter)
{
	int* counterp = new int();
	counterp = (int*)lpParameter;
	int counter = *counterp;

	printf("\n Counter= %d", counter);

	return 0;
}


DWORD WINAPI myThread(void* lpParameter)
{
	int* counterp = new int();
	counterp = (int*)lpParameter;
	int counter = *counterp;

	while (counter<10)
	{
		Sleep(300);
		counter++;
		x = counter;

		DWORD myThreadID;
		HANDLE myHandle = CreateThread(0, 0, Read, (void*)&x, 0, &myThreadID);
		TerminateThread(Read, 0);
	}

	return 0;
}

int main()
{
	int z = 0;

	unsigned int myCounter = 0;
	DWORD myThreadID;
	HANDLE myHandle = CreateThread(0, 0, myThread, (void*)&z, 0, &myThreadID);
	Sleep(4000);
	printf("\n Main Process ....");
	TerminateThread(myHandle, 0);

	getchar();

	return 0;
}
