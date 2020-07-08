// cl2.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include <windows.h>
#include <iostream>
#include "time.h"

using namespace std;

int main()
{
	setlocale(LC_ALL, "RUS");
	system("cls");
	HANDLE hslot;

	//LPTSTR slotname = TEXT("\\\\.\\mailslot\\demoslot");
	hslot = CreateFile(L"\\\\.\\mailslot\\demoSlot", GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, NULL, NULL);
	if (hslot == INVALID_HANDLE_VALUE)
	{

		std::cout << "SLOT WRITING FAILED" << std::endl;
		std::cout << "PRESS KEY TO FINISH" << std::endl;
		std::cin.get();
		return 0;

	}
	char wbuf[50] = "v lesu rodilas elo4ka ";
	std::cout << "SLOT IS WAITING" << std::endl;
	int nData;
	int n = 10;
	DWORD dwBytesWrite;
	double t1, t2;

	t1 = clock();

	for (int i = 0; i < 5; i++)
	{
		char q[6];
		sprintf_s(q, "%d", i + 1);
		char buf[sizeof(wbuf) + sizeof(q)];
		strcpy_s(buf, wbuf);
		strcat_s(buf, q);

		if (!WriteFile(hslot, buf, sizeof(wbuf), &dwBytesWrite, NULL))
		{
			std::cout << "WRITE FAILED" << std::endl;
			CloseHandle(hslot);
			std::cout << "PRESS KEY TO FINISH" << std::endl;
			std::cin.get();
		}

		cout << "Message " << i + 1 << endl;
	}

	t2 = clock();

	if (!WriteFile(hslot, " ", sizeof(" "), &dwBytesWrite, NULL))
	{
		std::cout << "WRITE FAILED" << std::endl;
		CloseHandle(hslot);
		std::cout << "PRESS KEY TO FINISH" << std::endl;
		std::cin.get();
	}

	if (!CloseHandle(hslot))
		throw "Error: CloseHandle";

	cout << endl << "Время передачи: " << (t2 - t1) / 1000 << " сек." << endl << endl;

	/*if (!WriteFile(hslot, &n, sizeof(n), &dwBytesWrite, NULL))
	{
	std::cout << "WRITE FAILED" << std::endl;
	CloseHandle(hslot);
	std::cout << "PRESS KEY TO FINISH" << std::endl;
	std::cin.get();
	return 0;
	}*/

	//std::cout << "Data WRITTEN TO BOX: " << n << std::endl;
	std::cout << "PRESS KEY TO FINISH" << std::endl;
	CloseHandle(hslot);
	std::cin.get();
	return 0;


	return 0;
}