#include <windows.h>
#include <tchar.h>
#include "resource.h"
#include <vector>
#include <cmath>
#include <math.h>
using namespace std;

#define PI 3.14159265

HWND hEdit;

BOOL CALLBACK DlgProc(HWND, UINT, WPARAM, LPARAM);

void sendNumberToTheEditInt(int number, TCHAR szForEdit[10]);
void sendNumberToTheEditFloat(float number, TCHAR szForEdit[10]);

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
	static float nCalculatedNumber = 0;

	TCHAR szCalculatedNumber[10];

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

		// Если нажимаем цыфры.
		if (LOWORD(wParam) >= IDC_BUTTON_Zero && LOWORD(wParam) <= IDC_BUTTON_9)
		{
			HWND hTemp;
			szButton[0] = 0;

			hTemp = GetDlgItem(hWnd, LOWORD(wParam));
			GetWindowText(hTemp, szButton, 10);
			lstrcat(szForEdit, szButton);

			SetWindowText(hEdit, szForEdit);
		}

		// Если + - * /
		if (LOWORD(wParam) >= IDC_BUTTON_Plus && LOWORD(wParam) <= IDC_BUTTON_Divide)
		{
			// Если есть знак (был нажат).
			if (sign[0] != 0)
			{
				GetWindowText(hEdit, szCalculatedNumber, 10);

				switch (sign[0])
				{
				case '+':
					nCalculatedNumber += _wtoi(szCalculatedNumber);
					break;
				case '-':
					nCalculatedNumber -= _wtoi(szCalculatedNumber);
					break;
				case '*':
					nCalculatedNumber *= _wtoi(szCalculatedNumber);
					break;
				case '/':
					if (_wtoi(szCalculatedNumber) != 0)
					{
						nCalculatedNumber /= _wtoi(szCalculatedNumber);
					}
					else
					{
						// Деление на ноль не возможно.
						nCalculatedNumber = 0;
					}
					break;
				default:
					MessageBeep(1);
					MessageBeep(1);
					break;
				}

				szForEdit[0] = 0;

				// Запоминаю новый знак
				HWND hTemp;

				hTemp = GetDlgItem(hWnd, LOWORD(wParam));
				GetWindowText(hTemp, (LPWSTR)sign, 10);

				szForEdit[0] = 0;

				if (sign[0] == '/')
				{
					sendNumberToTheEditFloat(nCalculatedNumber, szForEdit);
				}
				else
				{
					sendNumberToTheEditInt(nCalculatedNumber, szForEdit);
				}

				szForEdit[0] = 0;
			}
			else
			{
				// Получаем знак
				HWND hTemp;

				hTemp = GetDlgItem(hWnd, LOWORD(wParam));
				GetWindowText(hTemp, (LPWSTR)sign, 10);


				// Получаем число
				GetWindowText(hEdit, szCalculatedNumber, 10);
				nCalculatedNumber = _wtoi(szCalculatedNumber);
				szForEdit[0] = 0;
			}
		}
		// Если выбрали sin или cos
		else if (LOWORD(wParam) >= IDC_BUTTON_Sin && LOWORD(wParam) <= IDC_BUTTON_Cos) {

			GetWindowText(hEdit, szCalculatedNumber, 10);

			// Получаем знак
			HWND hTemp;

			hTemp = GetDlgItem(hWnd, LOWORD(wParam));
			GetWindowText(hTemp, (LPWSTR)sign, 10);

			// Если ввели число.
			if (lstrlen(szCalculatedNumber) > 0)
			{
				switch (sign[0])
				{
				case 's':
					nCalculatedNumber = sin(_wtoi(szCalculatedNumber) * PI / 180);
					break;
				case 'c':
					nCalculatedNumber = cos(_wtoi(szCalculatedNumber) * PI / 180);
					break;
				default:
					MessageBeep(1);
					MessageBeep(1);
					break;
				}

				// Вывести в Edit.
				sendNumberToTheEditFloat(nCalculatedNumber, szForEdit);
			}
		}

		// Если обнуляем данные.
		if (LOWORD(wParam) == IDC_BUTTON_C)
		{
			szForEdit[0] = 0;
			SetWindowText(hEdit, NULL);
			nCalculatedNumber = 0;
		}

		// Если нажимаем "=".
		if (LOWORD(wParam) == IDC_BUTTON_Equally)
		{
			GetWindowText(hEdit, szCalculatedNumber, 10);

			switch (sign[0])
			{
			case '+':
				nCalculatedNumber += _wtoi(szCalculatedNumber);
				break;
			case '-':
				nCalculatedNumber -= _wtoi(szCalculatedNumber);
				break;
			case '*':
				nCalculatedNumber *= _wtoi(szCalculatedNumber);
				break;
			case '/':
				if (_wtoi(szCalculatedNumber) != 0)
				{
					nCalculatedNumber /= _wtoi(szCalculatedNumber);
				}
				else
				{
					// Деление на ноль не возможно.
					nCalculatedNumber = 0;
				}
				break;
			default:
				break;
			}

			// Вывести в Edit.
			if (sign[0] == '/')
			{
				sendNumberToTheEditFloat(nCalculatedNumber, szForEdit);
			}
			else
			{
				sendNumberToTheEditInt(nCalculatedNumber, szForEdit);
			}

			sign[0] = 0;
		}


		return TRUE;

	}
	return FALSE;
}


void sendNumberToTheEditInt(int number, TCHAR szForEdit[10]) {

	_itow(number, szForEdit, 10);
	SetWindowText(hEdit, szForEdit);
}

void sendNumberToTheEditFloat(float number, TCHAR szForEdit[10]) {

	_itow(number, szForEdit, 10);
	lstrcat(szForEdit, L".");
	int i = (number - (int)number) * 10;
	TCHAR szTwo[2];
	_itow(i, szTwo, 10);
	lstrcat(szForEdit, szTwo);
	SetWindowText(hEdit, szForEdit);
}
