
// Lab8.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include <windows.h>
#include <iostream>
#include "string.h"
#include <stdlib.h>
#include <fstream>
#pragma warning (disable : 4996)

//участок кода, кот.не должен быть 1временно исп-н более чем 1 потоком вып-ния
CRITICAL_SECTION cs;

DWORD WINAPI myThread(void* lpPar)
{
	char info[256];

	TCHAR* b = new TCHAR();
	b = (TCHAR*)lpPar;

	wcstombs(info, b, wcslen(b) + 1);

	std::cout << "WRITING : " << info << "\n";
	std::ofstream file("D:\\БГТУ\\3 курс\\5 семестр\\ОСиСПр\\8\\lab8.txt");

	EnterCriticalSection(&cs);		//вход в критическую секцию

	file << info;
	file.close();

	LeaveCriticalSection(&cs);		//выход из критической секции
	return 0;
}

DWORD WINAPI myThread2(void* lpPar)
{
	EnterCriticalSection(&cs);

	std::ifstream file("D:\\БГТУ\\3 курс\\5 семестр\\ОСиСПр\\8\\lab8.txt");
	char info[256];

	file.getline(info, 256);
	file.close();
	std::cout << "READ : " << info;

	LeaveCriticalSection(&cs);
	return 0;
}

int main()
{
	DWORD myThreadID;
	DWORD myThreadID2;
	TCHAR Buff[256] = TEXT("Natasha Kasper. Lab8");
	TCHAR Buff2[256] = TEXT("start");

	InitializeCriticalSection(&cs);

	HANDLE myHandle = CreateThread(0, 0, myThread, (void*)Buff, CREATE_SUSPENDED, &myThreadID);
	

	BOOL b = SetThreadPriorityBoost(myHandle,
									false);		//сост.форсирования приоритета
								//t - форсаж отключен
								//f - форсаж включен

	if (b)
	{
		SetThreadPriority(myHandle, THREAD_PRIORITY_HIGHEST);
	}

	HANDLE myHandle2 = CreateThread(0, 0, myThread2, (void*)Buff2, CREATE_SUSPENDED, &myThreadID2);

	//уменьш.счет времени приостановки работы потока (счет = 0 -> выполнение продолж)
	ResumeThread(myHandle);
	ResumeThread(myHandle2);

	WaitForSingleObject(myHandle, 10000);
	WaitForSingleObject(myHandle2, 10000);

	printf("\n end");

	TerminateThread(myHandle, 0);
	TerminateThread(myHandle2, 0);

	getchar();
	return 0;
}
