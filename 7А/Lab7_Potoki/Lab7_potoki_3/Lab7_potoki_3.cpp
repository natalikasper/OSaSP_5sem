// Lab7_potoki_3.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include <windows.h>
#include <iostream>
#include "string.h"

DWORD WINAPI myThread(void* lpParameter)
{
	int* counterp = new int();
	counterp = (int*)lpParameter;
	int counter = *counterp;
	while (counter < 20)
	{
		Sleep(1000);
		counter++;
		printf("\n Counter = %d", counter);
	}
	return 0;
}

int main()
{
	int z = 0;
	int z2 = 5;
	unsigned int myCounter = 0;
	DWORD myThreadID;
	HANDLE myHandle = CreateThread(0, 0, myThread, (void*)&z, 0, &myThreadID);
	HANDLE myHandle2 = CreateThread(0, 0, myThread, (void*)&z2, 0, &myThreadID);
	Sleep(5000);
	printf("\n Main Process ....");
	TerminateThread(myHandle, 0);
	TerminateThread(myHandle2, 0);
	getchar();
	return 0;
}