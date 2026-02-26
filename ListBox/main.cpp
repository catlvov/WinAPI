#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>
#include "Resource.h"
#include <cstdio>

CONST CHAR* VALUES[] = {"this","is","my","frist","List","Box"};

BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM Iparam);
BOOL CALLBACK DlgProcAdd(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM Iparam);
BOOL CALLBACK DlgProcEdit(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM Iparam);

INT WINAPI WinMain(HINSTANCE hInistance, HINSTANCE hPrevInst, LPSTR IpCmdLine, INT nCmdShow)
{
	DialogBoxParam(hInistance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, DlgProc, 0);
	return 0;
}

BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM Iparam)
{
	switch (uMsg)
	{
	case WM_INITDIALOG:
	{
		HWND hListBox = GetDlgItem(hwnd, IDC_LIST);
		for (int i = 0; i < sizeof(VALUES) / sizeof(VALUES[0]) ; ++i)
		{
			SendMessage(hListBox, LB_ADDSTRING, 0, (LPARAM)VALUES[i]);
		}
	}
		break;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDC_LIST:
			if (HIWORD(wParam) == LBN_DBLCLK)
				DialogBoxParam(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_DIALOG_ADD), hwnd, DlgProcEdit, 0);
			break;
		case IDC_BUTTON_ADD:
			DialogBoxParam(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_DIALOG_ADD), hwnd, DlgProcAdd, 0);
			break;
		case IDC_BUTTON_DELETE:
		{
			HWND hListBox = GetDlgItem(hwnd, IDC_LIST);
			INT i = SendMessage(hListBox, LB_GETCURSEL, 0, 0);
			SendMessage(hListBox, LB_DELETESTRING, i, 0);
		}
			break;
		case IDOK:
		{
			CONST INT SIZE = 256;
			CHAR sz_buffer[SIZE] = {};
			HWND hListBox = GetDlgItem(hwnd, IDC_LIST);

			INT i = SendMessage(hListBox, LB_GETCURSEL, 0, 0);
			SendMessage(hListBox, LB_GETTEXT, i, (LPARAM)sz_buffer);
			CHAR sz_message[SIZE] = {};
			sprintf(sz_message, "Вы выбрали пункт №%i со значением \"%s\".", i, sz_buffer);

			if (i != LB_ERR)MessageBox(hwnd, sz_message, "info", MB_OK | MB_ICONINFORMATION);
			else MessageBox(hwnd, "Для начала выберете элемент", "info", MB_OK | MB_ICONERROR);

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

BOOL CALLBACK DlgProcAdd(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM Iparam)
{
	switch(uMsg)
	{
	case WM_INITDIALOG:
		SetFocus(GetDlgItem(hwnd, IDC_EDIT_ADD));
		break;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDOK:
		{
			CONST INT SIZE = 256;
			CHAR sz_buffer[SIZE] = {};
			HWND hEditAdd = GetDlgItem(hwnd, IDC_EDIT_ADD);
			SendMessageA(hEditAdd, WM_GETTEXT, SIZE, (LPARAM)sz_buffer);

			if (strlen(sz_buffer) > 0)
			{
				HWND hParent = GetParent(hwnd); //Получаем родительское окно
				HWND hlistBox = GetDlgItem(hParent, IDC_LIST);
				if (SendMessage(hlistBox, LB_FINDSTRING, 0, (LPARAM)sz_buffer) == LB_ERR)
				{
					SendMessage(hlistBox, LB_ADDSTRING, 0, (LPARAM)sz_buffer);
				}
			}
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


BOOL CALLBACK DlgProcEdit(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM Iparam)
{
	CONST INT SIZE = 256;
	CHAR sz_buffer[SIZE] = {};
	HWND hEdit = GetDlgItem(hwnd, IDC_EDIT_ADD);
	HWND hParent = GetParent(hwnd);
	HWND hListBox = GetDlgItem(hParent, IDC_LIST);
	switch (uMsg)
	{
	case WM_INITDIALOG:
	{
		SendMessage(hwnd, WM_SETTEXT, 0, (LPARAM)"Изменить выбраный элемент");
		INT i = SendMessage(hListBox, LB_GETCURSEL, 0, 0);
		SendMessage(hListBox, LB_GETTEXT, i, (LPARAM)sz_buffer);
		SendMessage(hEdit, WM_SETTEXT, 0, (LPARAM)sz_buffer);
		SetFocus(GetDlgItem(hwnd, IDC_EDIT_ADD));
		SendMessage(hEdit, EM_SETSEL, (WPARAM)0, (LPARAM)GetWindowTextLength(hEdit));
	}
		break;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDOK:
		{
			SendMessage(hEdit, WM_GETTEXT, SIZE, (LPARAM)sz_buffer);
			if (strlen(sz_buffer) > 0 && SendMessage(hListBox, LB_FINDSTRING, 0, (LPARAM)sz_buffer) == LB_ERR)
			{
				INT i = SendMessage(hListBox, LB_GETCURSEL, 0, 0);
				SendMessage(hListBox, LB_DELETESTRING, i, 0);
				SendMessage(hListBox, LB_INSERTSTRING, i, (LPARAM)sz_buffer);
				
			}
		}
		case IDCANCEL: EndDialog(hwnd, 0);
		}
		break;
	case WM_CLOSE: EndDialog(hwnd, 0);
	}
	return FALSE;
}