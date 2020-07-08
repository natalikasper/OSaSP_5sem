// сд1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
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
	hslot = CreateFile(                     // Создает или открывает файл или устройство ввода / вывода. 
		L"\\\\.\\mailslot\\demoSlot",       // Имя файла или устройства, которое будет создано или открыто. 
		GENERIC_WRITE,                      // запись
		FILE_SHARE_READ | FILE_SHARE_WRITE, // для совместного чтения
		NULL,                               // защита по умолчанию
		OPEN_EXISTING,                      // только существующий файл
		NULL,                               // 
		NULL                                // атрибутов шаблона нет
	);
	if (hslot == INVALID_HANDLE_VALUE)
	{
		std::cout << "SLOT WRITING FAILED" << std::endl;
		std::cout << "PRESS KEY TO FINISH" << std::endl;
		std::cin.get();
		return 0;

	}
	char wbuf[50] = "v lesu rodilas elo4ka 11 ";
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

	if (!WriteFile(    // Записывает данные в указанный файл или устройство ввода / вывода (I / O).
		hslot,         // устройству ввода-вывода 
		" ",           // Указатель на буфер, содержащий данные, которые должны быть записаны в файл или устройство.
		sizeof(" "),   // Количество байтов, которые должны быть записаны в файл или устройство.
		&dwBytesWrite, // Указатель на переменную, которая получает количество байтов, записанных при использовании синхронного параметра hFile . 
		NULL           // Указатель на структуру OVERLAPPED неасинхронно
	))
	{
		std::cout << "WRITE FAILED" << std::endl;
		CloseHandle(hslot);
		std::cout << "PRESS KEY TO FINISH" << std::endl;
		std::cin.get();
	}

	if (!CloseHandle(hslot))
		throw "Error: CloseHandle";

	cout << endl << "Время передачи: " << (t2 - t1) / 1000 << " сек." << endl << endl;
	std::cout << "PRESS KEY TO FINISH" << std::endl;
	CloseHandle(hslot);
	std::cin.get();
	return 0;
}