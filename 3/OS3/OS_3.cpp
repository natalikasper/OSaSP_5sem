#include "windows.h"
#include <iostream>
#include <tlhelp32.h>
#include "string.h"


void PrintLine(int x, int y, const char* line, int color = 0)
{

	HANDLE consoleOutput;
	COORD cursorPos;
	consoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);

	int len = 19;
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(consoleOutput, &csbi);
	SetConsoleTextAttribute(consoleOutput, 15); // первая цифра - фон, вторая - цвет текста

	cursorPos.X = x;
	cursorPos.Y = y - 1;
	SetConsoleCursorPosition(consoleOutput, cursorPos);
	std::cout << "|-------------------|" << std::endl;

	cursorPos.X = x;
	cursorPos.Y = y;
	SetConsoleCursorPosition(consoleOutput, cursorPos);
	std::cout << "|";

	for (int i = 0; i < len; i++)
	{
		if (line[i] == '\0')
		{
			std::cout << " ";
		}
		else
		{
			std::cout << line[i];
		}
	}
	std::cout << "|" << std::endl;
	cursorPos.X = x;
	cursorPos.Y = y + 1;
	SetConsoleCursorPosition(consoleOutput, cursorPos);
	std::cout << "|-------------------|" << std::endl;
}

int main()
{
	const char* line = "				";
	const char* symbol = " ";

	char names[20][10] = { "SURNAME", "", "KASPER" };
	char groups[20][10] = { "GROUP", "", "5" };

	int i = 0;

	for (i = 0; i < 3; i += 2)
	{
		PrintLine(5, 1 + i, names[i]);
		PrintLine(25, 1 + i, groups[i]);
	}

	system("pause");
	return 0;
}

