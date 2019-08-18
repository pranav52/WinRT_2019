#include <Windows.h>
#include "MyMath.h"

//CALL BACK FUNCTION :
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

//WINMAIN :
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow)
{
	// declaration and initialization :

	WNDCLASSEX wndclass;
	HWND hwnd;
	MSG msg;
	TCHAR szAppName[] = TEXT("MY APP");

	wndclass.cbSize = sizeof(WNDCLASSEX);
	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.lpfnWndProc = WndProc;
	wndclass.hInstance = hInstance;
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndclass.lpszClassName = szAppName;
	wndclass.lpszMenuName = NULL;
	wndclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	RegisterClassEx(&wndclass);

	//create Window :
	hwnd = CreateWindow(szAppName,
		TEXT("MY APPLICATION"),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		NULL,
		NULL,
		hInstance,
		NULL);

	ShowWindow(hwnd, iCmdShow);
	UpdateWindow(hwnd);

	// message loop :

	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return ((int)msg.wParam);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	int num, numSquare ;
	num = 70;
	HINSTANCE hdll= NULL;
	typedef  int(*SquareFun) (int);
	SquareFun sqfun = NULL;
	TCHAR str[255];

	switch (iMsg)
	{

	case WM_CREATE:

		hdll = LoadLibrary(TEXT( "02-dll_Def.dll"));
		sqfun = (SquareFun)GetProcAddress(hdll, "MakeSquare");
		numSquare = sqfun(num);
		wsprintf(str, TEXT("Square of %d = %d"), num, numSquare);
		MessageBox(hwnd, str, TEXT("Message"), MB_OK | MB_ICONINFORMATION);
		FreeLibrary(hdll);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return (DefWindowProc(hwnd, iMsg, wParam, lParam));
}

