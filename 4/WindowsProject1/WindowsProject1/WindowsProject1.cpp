// WindowsProject1.cpp : Определяет точку входа для приложения.
#include "stdafx.h"
#include "WindowsProject1.h"
#include <cstring>
#include <cstdio>
#include "windows.h"
#include <tlhelp32.h>
#include <iostream>

#define IDC_MYICON                      2
#define IDD_WINCW_DIALOG                102
#define IDD_ABOUTBOX                    103
#define IDS_APP_TITLE                   103
#define IDM_ABOUT                       104
#define IDM_EXIT                        105
#define IDS_HELLO                       106
#define IDI_WINCW                       107
#define IDI_SMALL                       108
#define IDC_WINCW                       109
#define IDC_WMCHAR                      110
#define IDR_MAINFRAME                   128
#define IDC_STATIC                      -1

#ifdef APSTUDIO_INVOKED
#ifndef APSTUDIO_READONLY_SYMBOLS
#define _APS_NEXT_RESOURCE_VALUE        129
#define _APS_NEXT_COMMAND_VALUE         32771
#define _APS_NEXT_CONTROL_VALUE         1000
#define _APS_NEXT_SYMED_VALUE           110
#endif
#endif

#define MAX_LOADSTRING 100

HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name
int colmn = 1;

ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK	myF(HWND, UINT, WPARAM, LPARAM);	//объявим диалоговую процедуру в программе:myF

int APIENTRY _tWinMain( //Одной из первых задач функции _tWinMain является вызов метода регистрации оконного класса-MyRegisterClass(hInstance);                                            
	HINSTANCE hInstance,		//дескриптор окна
	HINSTANCE hPrevInstance,	//описываем класс окна
	LPTSTR    lpCmdLine,		//указатель на строку, содержащую аргументы, переданные программе при ее запуске из cmd 
	int       nCmdShow)			//способ отображения окна
{	
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	MSG msg;
	HACCEL hAccelTable;

	//инициализация глобальных строк
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_WINDOWSPROJECT1, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	//выполнить инициализацию приложения
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WINDOWSPROJECT1));

	//основной цикл сообщений
	while (GetMessage(&msg, NULL, 0, 0))//В данном цикле считывается сообщение из очереди сообщений GetMessage.
	{   //Затем вызов TranslateAccelerator осуществляет трансляцию клавиш, нажатых на клавиатуре и отправляет сообщение msg в оконную процедуру 

		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int)msg.wParam;
}

// Назначение: регистрирует класс окна. 
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;	//Задаем стиль окна.
	wcex.lpfnWndProc = WndProc;	//опред.имя оконной процедуры
	wcex.cbClsExtra = 0;	//дп.д-е для класса
	wcex.cbWndExtra = 0;	//доп.д-е для окна
	wcex.hInstance = hInstance;	//заголовок прилож, кот.раб.с окном
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WINDOWSPROJECT1));	//иконка для окна приложения
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);	//устанавл.тип курсора в окне прилож
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);	//кисть для закрски окна
	wcex.lpszMenuName = MAKEINTRESOURCE(IDC_WINDOWSPROJECT1);	//меню окна прилож
	wcex.lpszClassName = szWindowClass;		//указатель на оконный класс
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));//Это описание используется для регистрации оконного класса с помощью 
	                                       //вызова функции RegisterClassEx(&wcex); Вызов этой функции вложен в метод MyRegisterClass(hInstance);

	return RegisterClassEx(&wcex);
}

// Назначение: сохраняет дескриптор экземпляра и создает главное окно 
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)//осуществляет инициализацию приложения и формирует дескриптор приложения hInstance.
{
	HWND hWnd;

	hInst = hInstance; // Store instance handle in our global variable

	hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,//Данная процедура  в свою очередь создает окно приложения путем вызова CreateWindow.
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

	if (!hWnd)
	{
		return FALSE;
	}

	HBRUSH hbrush = CreateSolidBrush(RGB(20, 220, 255)); // ------------ цвет
	SetClassLongPtr(hWnd, -10, (LONG)hbrush);
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	/*
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	*/
	return TRUE;
}

// WM_COMMAND-обработка меню приложения 
// WM_PAINT-раскрасить главное окно 
// WM_DESTROY-сообщение о завершении работы и возврат 
LRESULT CALLBACK WndProc(
			HWND hWnd,		//дескриптор окна
			UINT message,	//сообщение, посылаемое ОС
			WPARAM wParam,	//параметры
			LPARAM lParam	//сообщ, для последующего обращения
		)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;

	TCHAR szHello[MAX_LOADSTRING];
	LoadString(hInst, IDS_HELLO, szHello, MAX_LOADSTRING);

	TCHAR str[] = TEXT("BIG MAG");
	int responce = 0;


	switch (message)
	{
	case WM_COMMAND:
		wmId = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, (LPCTSTR)IDD_ABOUTBOX, hWnd, (DLGPROC)About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;

	case WM_RBUTTONDOWN:
		DialogBox(hInst, (LPCTSTR)IDD_DIALOG1, hWnd, (DLGPROC)myF);
		break;
	case WM_CHAR:
		hdc = GetDC(hWnd);
		TextOut(hdc, 1, colmn, TEXT("   "), 3);
		TextOut(hdc, 1, colmn++, str, 7);
		ReleaseDC(hWnd, hdc);
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

LRESULT CALLBACK myF(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_INITDIALOG:
		return TRUE;
	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			int z = MessageBoxEx(NULL, TEXT("HELLO"), TEXT("DialogWin"), MB_OK, 0x0409);
			EndDialog(hDlg, LOWORD(wParam));
			return TRUE;
		}
		break;
	}
	return FALSE;
}


INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}