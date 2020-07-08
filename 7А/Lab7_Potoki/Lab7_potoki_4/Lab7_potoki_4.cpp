// Lab7_potoki_4.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include <windows.h>
#include <iostream>
#include "string.h"


DWORD WINAPI myThread2(void* lpParameter)
{
	HANDLE* h = new HANDLE();
	h = (HANDLE*)lpParameter;
	HANDLE hh = *h;
	printf("\n Thread 2 tries to suspend thread1");
	SuspendThread(hh); // приостановка
	printf("\n Thread1 is suspended for 3 seconds");
	Sleep(3000);
	ResumeThread(hh);  // возобновление
	printf("\n Thread is resumed");
	return 0;
}



DWORD WINAPI myThread(void* lpParameter)
{
	int* counterp = new int();
	counterp = (int*)lpParameter;
	int counter = *counterp;

	while (counter < 30)
	{
		Sleep(500);
		counter++;
		printf("\n Counter= %d", counter);
	}

	return 0;
}

int main()
{
	int z = 5;

	unsigned int myCounter = 0;
	DWORD myThreadID;
	HANDLE myHandle = CreateThread(0, 0, myThread, (void*)&z, 0, &myThreadID);
	Sleep(5000);
	DWORD myThreadID2;
	HANDLE myHandle2 = CreateThread(0, 0, myThread2, (void*)&myHandle, 0, &myThreadID2);

	Sleep(15000);
	printf("\n Main Process ....");
	TerminateThread(myHandle2, 0);
	TerminateThread(myHandle, 0);

	getchar();

	return 0;
}
