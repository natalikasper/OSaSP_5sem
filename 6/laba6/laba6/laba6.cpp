// laba6.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include <iostream>
#include "windows.h"
#include <tlhelp32.h>
#include "string.h"

using namespace std;

TCHAR buf[] = TEXT("chrome.exe");

void search()
{
	WIN32_FIND_DATA FindFileData;
	HANDLE hFind = INVALID_HANDLE_VALUE;

	TCHAR filesearch[] = TEXT("C:\\Program Files (x86)\\Internet Explorer\\iexplo*.exe");

	hFind = FindFirstFile(filesearch, &FindFileData);
	if (hFind == INVALID_HANDLE_VALUE)
	{
		printf("Invalid file handle. Error is %u. \n", GetLastError());
	}
	else
	{
		std::wcout << "Founded process: " << FindFileData.cFileName << '\n';
		while (FindNextFile(hFind, &FindFileData) != 0) // продолжает поиск файлов из предыдущего вызова функции FindFirstFile
		{
			std::wcout << "Found: " << FindFileData.cFileName << '\n';
		}
		FindClose(hFind); // Закрывает дескриптор поиска файлов, открытый функциями FindFirstFile 
	}
	getchar();
	return;
}

void create()
{
	STARTUPINFO cif;
	ZeroMemory(&cif, sizeof(STARTUPINFO));
	PROCESS_INFORMATION pi; // Содержит информацию о недавно созданном процессе и его основной теме
	TCHAR buf[] = TEXT("D:\\БГТУ\\3 курс\\5 семестр\\ОСиСПр\\4\\WindowsProject1\\Debug\\WindowsProject1.exe");
	TCHAR process[] = TEXT("WindowsProject1.exe");
	if (CreateProcess(
		NULL, buf, NULL, NULL, FALSE, 0, NULL, NULL, &cif, &pi
	))
	{
		std::wcout << "Process " << process << " is running!" << endl;
		std::cout << endl;
	}
	else std::wcout << "Error " << '\n';
	getchar();
	return;
}

void findCreate()
{
	WIN32_FIND_DATA FindFileData;
	HANDLE hFind;
	STARTUPINFO cif;
	ZeroMemory(&cif, sizeof(STARTUPINFO));
	PROCESS_INFORMATION pi;
	TCHAR buf[] = TEXT("D:\\БГТУ\\3 курс\\5 семестр\\ОСиСПр\\6\\laba6\\Debug\\laba6.exe");
	TCHAR process[] = TEXT("laba6.exe");
	hFind = FindFirstFile(buf, &FindFileData);
	std::wcout << "Founded process: " << FindFileData.cFileName << '\n';
	if (CreateProcess(NULL, buf, NULL, NULL, FALSE, 0, NULL, NULL, &cif, &pi))
		std::wcout << "Running with PID:" << pi.dwProcessId << '\n';
	else std::wcout << "Error " << '\n';

	HANDLE hProcess = GetCurrentProcess();

	if (NULL != hProcess)
	{
		cout << "Done, closing in 2 seconds" << endl;
		Sleep(2000);
		BOOL result = TerminateProcess(hProcess, 0);
		CloseHandle(hProcess);
	}
	else
	{
		std::wcout << "Error while terminating " << '\n';
	}
	getchar();
	return;
}

void processList()
{
	//Возвращает дескриптор указанного стандартного устройства(стандартный ввод, стандартный вывод или стандартная ошибка)Возвращает дескриптор указанного стандартного устройства(стандартный ввод, стандартный вывод или стандартная ошибка)
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	//SetConsoleTextAttribute(hStdout, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY | BACKGROUND_GREEN);
	// Делает снимок указанных процессов, а также кучи, модули и потоки, используемые этими процессами
	HANDLE hSnapshot = CreateToolhelp32Snapshot(
		TH32CS_SNAPPROCESS,
		0                   
	);
	if (hSnapshot)
	{
		PROCESSENTRY32 pe32; // Описывает запись из списка процессов, находящихся в системном адресном пространстве при съемке моментального снимка
		pe32.dwSize = sizeof(PROCESSENTRY32); // Размер структуры в байтах
		if (Process32First(hSnapshot, &pe32)) // Получает информацию о первом процессе, обнаруженном в системном снимке
		{
			do
			{
				std::wcout << "Running ProcName: " << pe32.szExeFile << '\n';
			} while (Process32Next(hSnapshot, &pe32)); // Получает информацию о следующем процессе, записанном в системном снимке
		}
		CloseHandle(hSnapshot);
	}
	getchar();
	return;
}

bool AreaEqual(const TCHAR *a, const TCHAR *b)
{
	while (*a == *b)
	{
		if (*a == TEXT('\0'))
			return true;
		a++; b++;
	}
	return false;
}

bool IsProcessRun()
{
	bool RUN;
	TCHAR buf[] = TEXT("chrome.exe");
	HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	PROCESSENTRY32 pe;
	pe.dwSize = sizeof(PROCESSENTRY32);
	Process32First(hSnapshot, &pe);
	if (AreaEqual(pe.szExeFile, buf))
	{
		RUN = true;
		return RUN;
	}
	else
		RUN = false;
	while (Process32Next(hSnapshot, &pe))
	{
		if (AreaEqual(pe.szExeFile, buf))
		{
			RUN = true;
			return RUN;
		}
		else
			RUN = false;
	}
	return RUN;
}

void check()
{
	if (IsProcessRun())
	{
		cout << "Process "; wcout << buf; cout << " is running " << endl;
	}
	else
	{
		cout << "Process "; wcout << buf; cout << " is not running " << endl;
	}
	cout << endl;
	return;
}

int main()
{
	int n;
	while (1)
	{
		cout << "0 - Exit" << endl;
		cout << "1 - Find process" << endl;
		cout << "2 - Create process, PID, complete in 2 sec" << endl;
		cout << "3 - Find & create process" << endl;
		cout << "4 - List of process" << endl;
		cout << "5 - Is process running?" << endl;
		cout << "\tChoose: \n\n";
		cin >> n;

		switch (n)
		{
		case 0: exit(0); break;
		case 1: search(); break;
		case 2: create(); break;
		case 3: findCreate(); break;
		case 4: processList(); break;
		case 5: check(); break;
		}

	}
}

