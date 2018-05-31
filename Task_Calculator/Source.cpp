#include <windows.h>
#include <tchar.h>
#include "resource.h"
#include <vector>
using namespace std;

HWND hEdit;

BOOL CALLBACK DlgProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrev, LPSTR lpszCmdLine, int nCmdShow)
{

	MSG msg;
	HWND hDialog = CreateDialog(hInst, MAKEINTRESOURCE(IDD_DIALOG_Main), NULL, DlgProc);
	ShowWindow(hDialog, nCmdShow);


	while (GetMessage(&msg, 0, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}



BOOL CALLBACK DlgProc(HWND hWnd, UINT uMessage, WPARAM wParam, LPARAM lParam)
{
	static TCHAR szForEdit[10];
	static TCHAR szButton[10];

	switch (uMessage)
	{
	case WM_CLOSE:
		DestroyWindow(hWnd);
		PostQuitMessage(0);
		return TRUE;

	case WM_INITDIALOG:

		hEdit = GetDlgItem(hWnd, IDC_EDIT);

		return TRUE;

	case WM_COMMAND:

		if (LOWORD(wParam) >= IDC_BUTTON_Zero && LOWORD(wParam) <= IDC_BUTTON_9)
		{
			HWND hTemp;
			szButton[0] = 0;

			hTemp = GetDlgItem(hWnd, LOWORD(wParam));
			GetWindowText(hTemp, szButton, 10);
			lstrcat(szForEdit, szButton);

			SetWindowText(hEdit, szForEdit);
		}

		if (LOWORD(wParam) == IDC_BUTTON_C)
		{
			szForEdit[0] = 0;
			SetWindowText(hEdit, NULL);
		}

		return TRUE;

	}
	return FALSE;
}