#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>
#include <iostream>
#include "resource.h"

CONST CHAR* ITEMS[] = {"This","is", "my", "first", "Combo", "box", };



BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, INT nCmdShow)
{
	DialogBoxParam(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, DlgProc, 0);
	return 0;
}

BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM IParam)
{
	switch (uMsg)
	{
	case WM_INITDIALOG:
	{
		HWND hCombo = GetDlgItem(hwnd, IDC_COMBO);
		HICON hIcon = LoadIcon(GetModuleHandleA(NULL), MAKEINTRESOURCE(IDI_ICON1));
		SendMessage(hwnd, WM_SETICON, 0, (LPARAM)hIcon);
			
		//AllocConsole();
		//freopen("CONOUT$", "w", stdout);
		for (int i = 0; i < sizeof(ITEMS)/sizeof(ITEMS[0]); ++i)
		{
			//std::cout << ITEMS[i] << std::endl;
			SendMessage(hCombo, CB_ADDSTRING, 0, (LPARAM)ITEMS[i]);
		}
	}
		break;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDOK:
		{
			CONST INT SIZE = 256;
			CHAR sz_buffer[SIZE] = {};
			HWND hCombo = GetDlgItem(hwnd, IDC_COMBO);

			INT i = SendMessage(hCombo, CB_GETCURSEL, 0, 0);
			SendMessage(hCombo, CB_GETLBTEXT, i, (LPARAM)sz_buffer);

			CHAR sz_massege[SIZE] = {};
			sprintf(sz_massege, "Вы выбрали пункт #%i, со значением \"%s\".", i,sz_buffer);
			MessageBox(hwnd, sz_massege, "info", MB_OK | MB_ICONINFORMATION);

		}
			break;
		case IDCANCEL: EndDialog(hwnd, 0);
		}
		break;
	case WM_CLOSE:
		EndDialog(hwnd, 0);
	}
	return FALSE;
}