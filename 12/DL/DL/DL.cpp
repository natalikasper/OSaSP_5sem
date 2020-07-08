// DL.cpp : Определяет экспортированные функции для приложения DLL.
//
#define WIN32_LEAN_AND_MEAN

#include "stdafx.h"
#include <iostream>
#include "string.h"
#include <string>
#include <fstream>
#include <stdio.h>
#include <ctime>
#include "DLL.h"

using namespace std;

extern "C++" __declspec(dllexport) void WriteFile()
{
	setlocale(NULL, "RUS");
	HANDLE hFile;
	DWORD dwBytesWritten;
	char buf[50];
	cout << "Введите строку для записи в файл:" << endl;
	fgets(buf, sizeof(buf), stdin);
	ofstream out;

	//открываем файл для записи
	out.open("F:\\6 семестр\\ОСиСП\\лабы\\Lab3\\task1.txt");
	if (out.is_open())
	{
		out << buf << std::endl;
	}
}

extern "C++" __declspec(dllexport) void StartProcess()
{
	STARTUPINFO cif;
	ZeroMemory(&cif, sizeof(STARTUPINFO));
	PROCESS_INFORMATION pi;
	TCHAR buf[] = TEXT("calc.exe");
	if (!(CreateProcess(NULL, buf, NULL, NULL, FALSE, 0, NULL, NULL, &cif, &pi)))
		std::wcout << "Error " << '\n';
}

extern "C++" __declspec(dllexport) void CheckFile()
{
	WIN32_FIND_DATA FindFileData;
	HANDLE hFind = INVALID_HANDLE_VALUE;

	TCHAR directorySearch[] = TEXT("F:\\6 семестр\\ОСиСП\\*");
	TCHAR filesearch[] = TEXT("F:\\6 семестр\\ОСиСП\\*.docx");

	hFind = FindFirstFile(filesearch, &FindFileData);

	if (hFind == INVALID_HANDLE_VALUE)
	{
		printf("Invalid file handle. Error is %u.\n", GetLastError());
	}
	else
	{
		std::wcout << "Found: " << FindFileData.cFileName << '\n';

		while (FindNextFile(hFind, &FindFileData) != 0)
		{
			std::wcout << "Found: " << FindFileData.cFileName << '\n';
		}
		FindClose(hFind);
	}
}






