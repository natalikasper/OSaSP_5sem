// lab9_2.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
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
	//LPTSTR slotname = TEXT();
	hslot = CreateMailslot(            // Создает почтовый ящик с указанным именем и возвращает дескриптор, 
									   // который сервер почтового сервера может использовать для выполнения операций с почтовым ящиком.
		L"\\\\.\\mailslot\\demoSlot",  // Имя почтового ящика.
		0,                             // сообщение может быть любого размера
		MAILSLOT_WAIT_FOREVER,         // Всегда ждет сообщения.
		NULL                           // дескриптор не может быть унаследован
	);
	if (hslot == INVALID_HANDLE_VALUE)
	{
		std::cout << "SLOT FAILED" << std::endl;
		std::cout << "PRESS KEY TO FINISH" << std::endl;
		std::cin.get();
		return 0;
	}
	std::cout << "SLOT IS WAITING" << std::endl;
	int i = 0;
	char rbuf[50];
	DWORD rms;
	HANDLE hMS;
	double t1, t2;
	do
	{
		i++;

		if (!ReadFile(     // Считывает данные из указанного файла или устройства ввода / вывода (I / O).
			hslot,         // из MailSlot
			rbuf,          // Указатель на буфер, который принимает данные, считанные из файла или устройства.
			sizeof(rbuf),  // Максимальное количество байтов для чтения.
			&rms,          // Указатель на переменную, которая получает количество байтов, считанных при использовании синхронного параметра hFile .
			NULL           // 
		))
		{
			std::cout << "READING SLOT FAILED" << std::endl;
			CloseHandle(hslot);
			std::cout << "PRESS KEY TO FINISH" << std::endl;
			std::cin.get();
			return 0;
		}
		if (i == 1)
			t1 = clock();

		cout << rbuf << endl;
	} while (true);

	t2 = clock();

	cout << "Время передачи: " << (t2 - t1) / 1000 << " сек." << endl;
	cout << "Количество сообщений: " << i - 1 << endl << endl;

	if (!CloseHandle(hslot))
		throw "Error: CloseHandle";
	return 0;
}
