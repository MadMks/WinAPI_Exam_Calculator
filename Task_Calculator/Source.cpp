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
	static TCHAR sign[1];
	static int nCalculatedNumber = 0;

	switch (uMessage)
	{
	case WM_CLOSE:
		DestroyWindow(hWnd);
		PostQuitMessage(0);
		return TRUE;

	case WM_INITDIALOG:

		sign[0] = 0;

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

		if (LOWORD(wParam) >= IDC_BUTTON_Plus && LOWORD(wParam) <= IDC_BUTTON_Cos)
		{
			/*if (sign != NULL)*/
			if (sign[0] != 0)
			{
				TCHAR szCalculatedNumber[10];

				switch (sign[0])
				{
				case '+':
					//MessageBeep(1);
					// прибавл€ю к nCalculatedNumber += 
					GetWindowText(hEdit, szCalculatedNumber, 10);
					nCalculatedNumber += _wtoi(szCalculatedNumber);
					break;
				case '-':

					break;
				case '*':

					break;
				case '/':

					break;
				case 's':

					break;
				case 'c':

					break;
				default:
					MessageBeep(1);
					MessageBeep(1);
					break;
				}

				szForEdit[0] = 0;

				// «апоминаю новый знак
				HWND hTemp;

				hTemp = GetDlgItem(hWnd, LOWORD(wParam));
				GetWindowText(hTemp, (LPWSTR)sign, 10);
			}
			else
			{
				HWND hTemp;

				hTemp = GetDlgItem(hWnd, LOWORD(wParam));
				GetWindowText(hTemp, (LPWSTR)sign, 10);

				//SetWindowText(hWnd, (LPWSTR)sign);

				TCHAR szCalculatedNumber[10];
				GetWindowText(hEdit, szCalculatedNumber, 10);
				nCalculatedNumber = _wtoi(szCalculatedNumber);
				szForEdit[0] = 0;
			}
		}

		if (LOWORD(wParam) == IDC_BUTTON_C)
		{
			szForEdit[0] = 0;
			SetWindowText(hEdit, NULL);
			nCalculatedNumber = 0;
		}

		if (LOWORD(wParam) == IDC_BUTTON_Equally)
		{
			TCHAR szCalculatedNumber[10];

			switch (sign[0])
			{
			case '+':
				//MessageBeep(1);
				// прибавл€ю к nCalculatedNumber += 
				GetWindowText(hEdit, szCalculatedNumber, 10);
				nCalculatedNumber += _wtoi(szCalculatedNumber);
				break;
			case '-':

				break;
			case '*':

				break;
			case '/':

				break;
			case 's':

				break;
			case 'c':

				break;
			default:
				MessageBeep(1);
				MessageBeep(1);
				break;
			}

			// вывести в edit
			_itow(nCalculatedNumber, szForEdit, 10);
			SetWindowText(hEdit, szForEdit);
		}


		return TRUE;

	}
	return FALSE;
}