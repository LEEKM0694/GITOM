#include<Windows.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
HWND hWndMain;
LPCTSTR lpszClass = TEXT("겜플2B 이경민");

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE
	hPrevInstance, LPSTR lpszCmdParam, int nCmdShow)
{
	HWND hWnd;
	MSG Message;
	WNDCLASS WndClass;
	g_hInst = hInstance;

	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hInstance = hInstance;
	WndClass.lpfnWndProc = WndProc;
	WndClass.lpszClassName = lpszClass;
	WndClass.lpszMenuName = NULL;
	WndClass.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
	RegisterClass(&WndClass);

	hWnd = CreateWindow(lpszClass, lpszClass, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
		CW_USEDEFAULT,
		NULL, (HMENU)NULL, hInstance, NULL);
	ShowWindow(hWnd, nCmdShow);

	while (GetMessage(&Message, NULL, 0, 0)) {
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}
	return Message.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM IParam)
{
	HDC hdc;
	hdc = GetDC(hWnd);
	PAINTSTRUCT ps;
	HBRUSH hBrush, oldBrush;
	POINT MOUSECL;

	static char ARR[750][750] = { 0, };
	static int c = 0;//누른키에 따라 값이 다르게 설정되기위한 변수.
	static int x = 20;//세로줄
	static int y = 20;//가로줄
	static int turn = 2;
	static int XP = 0;
	static int YP = 0;
	static int X = 0;
	static int Y = 0;
	static int n = 0;
	static bool COUNTING = true;
	static int count = 0;
	static int COUNT = 0;
	static int TURN = 0;

	switch (iMessage)
	{
	case WM_PAINT://그리기
		hdc = BeginPaint(hWnd, &ps);
		for (int i = 0; i < 18; i++)
		{
			x += 40;
			MoveToEx(hdc, x, 60, NULL);
			LineTo(hdc, x, 740);
		}
		for (int j = 0; j < 18; j++)
		{
			y += 40;
			MoveToEx(hdc, 60, y, NULL);
			LineTo(hdc, 740, y);
		}
		EndPaint(hWnd, &ps);
		return 0;
		InvalidateRect(hWnd, NULL, FALSE);//세로줄과 가로줄을 겹치기위해 FALSE를 쓴다.
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	switch (iMessage)
	{
	case WM_LBUTTONDOWN:

		MOUSECL.x = LOWORD(IParam);
		MOUSECL.y = HIWORD(IParam);

		XP = MOUSECL.x / 40;
		YP = MOUSECL.y / 40;
		TURN = (turn % 2) + 1;
		COUNT = TRUE;


		hdc = GetDC(hWnd);
		if (turn % 2 == 0)
			hBrush = CreateSolidBrush(RGB(0, 0, 0));
		else
			hBrush = CreateSolidBrush(RGB(255, 255, 255));

		oldBrush = (HBRUSH)SelectObject(hdc, hBrush);

		if ((60 < MOUSECL.x) && (MOUSECL.x < 740) && (60 < MOUSECL.y) && (MOUSECL.y < 740))
		{
			if (ARR[YP][XP] == 0)
			{
				Ellipse(hdc, XP * 40, YP * 40, (XP * 40) + 40, (YP * 40) + 40);
				ARR[YP][XP] = (turn % 2) + 1;
			}
		}
		else
		{
			COUNT = FALSE;
		}
		n = 1;
		count = 0;
		while (n < 6 && COUNTING)
		{
			if ((YP - n < 0) || (YP + n > 22) || (XP - n < -3) || (XP + n > 22))
				break;
			else if (ARR[YP + n][XP] == ((turn % 2) + 1))
				count++;
			else
				break;
			n++;
		};
		n = 1;
		while (n < 6 && COUNTING)
		{
			if ((YP - n < 0) || (YP + n > 22) || (XP - n < -3) || (XP + n > 22))
				break;
			else if (ARR[YP - n][XP] == ((turn % 2) + 1))
				count++;
			else
				break;
			n++;
		}
		if ((count == 4) && (TURN == 1))
		{
			MessageBox(0, L"흑돌 승리", L"결과", MB_OK);
		}
		else if ((count == 4) && (TURN != 1))
		{
			MessageBox(0, L"백돌 승리", L"결과", MB_OK);
		}
		n = 1;
		count = 0;
		while (n < 6 && COUNTING)
		{
			if ((YP - n < 0) || (YP + n > 22) || (XP - n < -3) || (XP + n > 22))
				break;
			else if (ARR[YP][XP + n] == ((turn % 2) + 1))
				count++;
			else
				break;
			n++;
		}
		n = 1;
		while (n < 6 && COUNTING)
		{
			if ((YP - n < 0) || (YP + n > 22) || (XP - n < -3) || (XP + n > 22))
				break;
			else if (ARR[YP][XP - n] == ((turn % 2) + 1))
				count++;
			else
				break;
			n++;
		}
		if ((count == 4) && (TURN == 1))
		{
			MessageBox(0, L"흑돌 승리", L"결과", MB_OK);
		}
		else if ((count == 4) && (TURN != 1))
		{
			MessageBox(0, L"백돌 승리", L"결과", MB_OK);
		}
		n = 1;
		count = 0;
		while (n < 6 && COUNTING)
		{
			if ((YP - n < -3) || (YP + n > 22) || (XP - n < -3) || (XP + n > 22))
				break;
			else if (ARR[YP + n][XP + n] == ((turn % 2) + 1))
				count++;
			else
				break;
			n++;
		}
		n = 1;
		while (n < 6 && COUNTING)
		{
			if ((YP - n < -3) || (YP + n > 22) || (XP - n < -3) || (XP + n > 22))
				break;
			else if (ARR[YP - n][XP - n] == ((turn % 2) + 1))
				count++;
			else
				break;
			n++;
		}
		if ((count == 4) && (TURN == 1))
		{
			MessageBox(0, L"흑돌 승리", L"결과", MB_OK);
		}
		else if ((count == 4) && (TURN != 1))
		{
			MessageBox(0, L"백돌 승리", L"결과", MB_OK);
		}
		n = 1;
		count = 0;
		while (n < 6 && COUNTING)
		{
			if ((YP - n < 0) || (YP + n > 22) || (XP - n < -3) || (XP + n > 22))
				break;
			else if (ARR[YP + n][XP - n] == ((turn % 2) + 1))
				count++;
			else
				break;
			n++;
		}
		n = 1;
		while (n < 6 && COUNTING)
		{
			if ((YP - n < 0) || (YP + n > 22) || (XP - n < -3) || (XP + n > 22))
				break;
			else if (ARR[YP - n][XP + n] == ((turn % 2) + 1))
				count++;
			else
				break;
			n++;
		}
		if ((count == 4) && (TURN == 1))
		{
			MessageBox(0, L"흑돌 승리", L"결과", MB_OK);
		}
		else if ((count == 4) && (TURN != 1))
		{
			MessageBox(0, L"백돌 승리", L"결과", MB_OK);
		}
		if (COUNT == TRUE)
		{
			turn++;
		}
		COUNT = TRUE;

		SelectObject(hdc, oldBrush);
		DeleteObject(hBrush);

		EndPaint(hWnd, &ps);

		return 0;
	}
	return(DefWindowProc(hWnd, iMessage, wParam, IParam));
}