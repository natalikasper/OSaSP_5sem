// ConsoleApplication1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include <iostream>
#include "DLL.h"
#include <conio.h>
#include <stdlib.h>
#include "string.h"
#include <string>

using namespace std;

int main()
{
	setlocale(NULL, "RUS");
		cout << "1. Записать в файл" << endl;
		WriteFile();
		cout << "2. Запустить процесс" << endl;
		StartProcess();
		cout << "3. Проверить наличие файла" << endl;
		CheckFile();
		_getch();
	return 0;
}