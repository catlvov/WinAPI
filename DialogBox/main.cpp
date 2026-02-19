#include <Windows.h>
#include "resource.h"

BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, INT nCmdShow)
{
    DialogBoxParam(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, DlgProc, 0);
    return 0;
}

BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    static HWND hEditLogin;

    switch (uMsg)
    {
    case WM_INITDIALOG:
    {
        HICON hIcon = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ICON1));
        SendMessage(hwnd, WM_SETICON, ICON_SMALL, (LPARAM)hIcon);
        SendMessage(hwnd, WM_SETICON, ICON_BIG, (LPARAM)hIcon);
        hEditLogin = GetDlgItem(hwnd, IDC_EDIT_LOGIN);

        SetWindowText(hEditLogin, "Введите имя пользователя");

        SetWindowLongPtr(hEditLogin, GWLP_USERDATA, (LONG_PTR)1); 
    }
    break;

    case WM_COMMAND:
    {
        switch (LOWORD(wParam))
        {
        case IDC_BUTTON_COPY:
        {
            CONST INT SIZE = 256;
            CHAR sz_buffer[SIZE] = {};
            HWND hEditLogin = GetDlgItem(hwnd, IDC_EDIT_LOGIN);
            HWND hEditPassword = GetDlgItem(hwnd, IDC_EDIT_PASSWORD);

            SendMessage(hEditLogin, WM_GETTEXT, SIZE, (LPARAM)sz_buffer);
            SendMessage(hEditPassword, WM_SETTEXT, 0, (LPARAM)sz_buffer);
        }
        break;

        case IDOK:
            MessageBox(hwnd, "Была нажата кнопка OK", "Info", MB_OK | MB_ICONINFORMATION);
            break;

        case IDCANCEL:
            EndDialog(hwnd, 0);
            break;
        }
    }
    break;

    case WM_CLOSE:
        EndDialog(hwnd, 0);
        break;

    case WM_SETFOCUS:
        break;

    case WM_COMMAND:
        break;

    default:

        break;
    }

    switch (uMsg)
    {
    case WM_COMMAND:
    {
        HWND hFocus = (HWND)wParam;
        if (hFocus == hEditLogin)
        {
            switch (HIWORD(wParam))
            {
            case EN_SETFOCUS:
            {
                CHAR szText[256];
                GetWindowText(hEditLogin, szText, 256);
                if (strcmp(szText, "Введите имя пользователя") == 0)
                {
                    // Удаляем приглашение
                    SetWindowText(hEditLogin, "");
                    SetWindowLongPtr(hEditLogin, GWLP_USERDATA, (LONG_PTR)0);
                }
            }
            break;

            case EN_KILLFOCUS:
            {
                CHAR szText[256];
                GetWindowText(hEditLogin, szText, 256);
                if (strlen(szText) == 0)
                {
                    SetWindowText(hEditLogin, "Введите имя пользователя");
                    SetWindowLongPtr(hEditLogin, GWLP_USERDATA, (LONG_PTR)1);
                }
            }
            break;

            case EN_CHANGE:
            {
            }
            break;
            }
        }
    }
    break;
    }

    return FALSE;
}