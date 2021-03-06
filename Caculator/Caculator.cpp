// Caculator.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "Caculator.h"

#define MAX_LOADSTRING 100
#define ID_DISPLAY 55
#define ID_BTN_ONE 1
#define ID_BTN_TWO 2
#define ID_BTN_THREE 3
#define ID_BTN_FOUR 4
#define ID_BTN_FIVE 5
#define ID_BTN_SIX 6
#define ID_BTN_SEVEN 7
#define ID_BTN_EIGHT 8
#define ID_BTN_NINE 9
#define ID_BTN_ZERO 10

#define ID_BTN_ADD 11
#define ID_BTN_SUB 12
#define ID_BTN_MUL 13
#define ID_BTN_DIV 14
#define ID_BTN_EQUAL 15
#define ID_BTN_DOT 16
#define ID_BTN_AC 17

#define ID_BTN_DELETE 30
#define ID_BTN_EXIT 31

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

// Các biến tự định nghĩa
HWND Display;
HWND btnZero, btnOne, btnTwo, btnThree, btnFour, btnFive, btnSix, btnSeven, btnEight, btnNine;
HWND btnAdd, btnSub, btnMul, btnDiv, btnEqual, btnDot, btnAC;
HWND btnExit, btnDelete;

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

//Các phương thức tự định nghĩa. 
void Create(HWND);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_CACULATOR, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_CACULATOR));

    MSG msg;

    // Main message loop:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}


ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_CACULATOR));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_CACULATOR);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      900, 100, 295, 350, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}


LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static TCHAR noidung[12], item[3];
	static int  st1, st2,pheptoan,dodai;
    switch (message)
    {
	case WM_CREATE:
		Create(hWnd);
		break;
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
			if (wmId >= 0 && wmId <= 9)
			{
				GetWindowText(Display, noidung, 30);				
				wsprintf(noidung, L"%s%d", noidung, wmId);
				SetWindowText(Display, noidung);
			}
            switch (wmId)
            {
			case ID_BTN_ADD:
			case ID_BTN_SUB:
			case ID_BTN_MUL:
			case ID_BTN_DIV:
				GetWindowText(Display, noidung, 30);
				st1 = _wtof(noidung);
				SetWindowText(Display, TEXT(""));
				pheptoan = wmId;
				break;
			case ID_BTN_EQUAL:
				GetWindowText(Display, noidung, 30);
				st2 = _wtof(noidung);
				if (pheptoan == ID_BTN_ADD)
					st2 = st1 + st2;
				if (pheptoan == ID_BTN_SUB)
					st2 = st1 - st2;
				wsprintf(noidung, L"%d", st2);
				SetWindowText(Display, noidung);
				break;
			case ID_BTN_DELETE:
				dodai = GetWindowTextLength(Display);
				SendMessage(Display,EM_SETSEL, dodai - 1, dodai);
				SendMessage(Display, WM_CLEAR, 0, 0);
				break;
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: Add any drawing code that uses hdc here...
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

void static Create(HWND hWnd) {
	Display = CreateWindowEx(0, L"EDIT", NULL, WS_CHILD | WS_BORDER | WS_VISIBLE, 20, 20, 240, 50, hWnd, (HMENU)ID_DISPLAY, NULL, NULL);

	btnOne = CreateWindow(L"BUTTON", L"1", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 20, 80, 40, 40, hWnd, (HMENU)1, NULL, NULL);
	btnTwo = CreateWindow(L"BUTTON", L"2", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 70, 80, 40, 40, hWnd, (HMENU)2, NULL, NULL);
	btnThree = CreateWindow(L"BUTTON", L"3", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 120, 80, 40, 40, hWnd, (HMENU)3, NULL, NULL);
	btnFour = CreateWindow(L"BUTTON", L"4", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 20, 130, 40, 40, hWnd, (HMENU)4, NULL, NULL);
	btnFive = CreateWindow(L"BUTTON", L"5", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 70, 130, 40, 40, hWnd, (HMENU)5, NULL, NULL);
	btnSix = CreateWindow(L"BUTTON", L"6", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 120, 130, 40, 40, hWnd, (HMENU)6, NULL, NULL);
	btnSeven = CreateWindow(L"BUTTON", L"7", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 20, 180, 40, 40, hWnd, (HMENU)7, NULL, NULL);
	btnEight = CreateWindow(L"BUTTON", L"8", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 70, 180, 40, 40, hWnd, (HMENU)8, NULL, NULL);
	btnNine = CreateWindow(L"BUTTON", L"9", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 120, 180, 40, 40, hWnd, (HMENU)9, NULL, NULL);
	btnZero = CreateWindow(L"BUTTON", L"0", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 20, 230, 40, 40, hWnd, (HMENU)0, NULL, NULL);

	btnDelete = CreateWindow(L"BUTTON", L"DEL", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 170, 80, 40, 40, hWnd, (HMENU)ID_BTN_DELETE, NULL, NULL);
	btnAC = CreateWindow(L"BUTTON", L"AC", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 220, 80, 40, 40, hWnd, (HMENU)ID_BTN_AC, NULL, NULL);

	btnAdd = CreateWindow(L"BUTTON", L"+", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 170, 130, 40, 40, hWnd, (HMENU)ID_BTN_ADD, NULL, NULL);
	btnSub = CreateWindow(L"BUTTON", L"-", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 220, 130, 40, 40, hWnd, (HMENU)ID_BTN_SUB, NULL, NULL);
	btnMul = CreateWindow(L"BUTTON", L"x", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 170, 180, 40, 40, hWnd, (HMENU)ID_BTN_MUL, NULL, NULL);
	btnDiv = CreateWindow(L"BUTTON", L":", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 220, 180, 40, 40, hWnd, (HMENU)ID_BTN_DIV, NULL, NULL);

	btnDot = CreateWindow(L"BUTTON", L".", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 70, 230, 40, 40, hWnd, (HMENU)ID_BTN_DOT, NULL, NULL);
	btnEqual = CreateWindow(L"BUTTON", L"=", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 120, 230, 140, 40, hWnd, (HMENU)ID_BTN_EQUAL, NULL, NULL);

}
// Message handler for about box.
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
