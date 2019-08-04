//header file
#include <Windows.h>
#include "MyResource.h"


//declare window proceduer
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

//WinMain()
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE prevInstance, LPSTR iCmdLine, int iCmdShow)
{
	//local variables
	WNDCLASSEX wndclass;
	HWND hwnd;
	MSG msg;
	TCHAR szAppName[] = TEXT("MySplashScreen");

	MessageBox(NULL, TEXT("MY_Application is arrived..!!"), TEXT("Message"), MB_OK | MB_ICONINFORMATION);

	//code

	//initialize wndclass
	wndclass.cbSize = sizeof(WNDCLASSEX);
	wndclass.style = CS_VREDRAW | CS_HREDRAW;
	wndclass.lpfnWndProc = WndProc;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.lpszClassName = szAppName;
	wndclass.hIcon = LoadIcon(NULL, MAKEINTRESOURCE(MYICON));
	wndclass.hIconSm = LoadIcon(NULL, MAKEINTRESOURCE(MYICON)); //MAKEINTRESOURCE : it use to convert int value to resource
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hInstance = hInstance;
	wndclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndclass.lpszMenuName = NULL;

	//create window in memory
	hwnd = CreateWindow(szAppName,				//call goes to WM_CREATE
		TEXT("MyScreen"),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		NULL,
		NULL,
		hInstance,
		NULL);

	//Show window
	ShowWindow(hwnd, iCmdShow);
	UpdateWindow(hwnd);

	//message loop
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return ((int)msg.wParam);
}



//define window procedure
LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	static HBITMAP hBitmap;
	HDC hdc, hdcMem;
	PAINTSTRUCT ps;
	RECT rc;
	BITMAP bitmap;

	switch (iMsg)
	{
	case WM_CREATE:
		//we have to load bitmap in the memory first.
		hBitmap = LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(MYBITMAP));
		break;

	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);	//call the specialist

		GetClientRect(hwnd, &rc);
		hdcMem = CreateCompatibleDC(NULL);	//create memory device context for the bitmap 
		SelectObject(hdcMem, hBitmap);
		GetObject(hBitmap, sizeof(BITMAP), (PSTR)&bitmap); // to get info about graphics objects

		// StretchBlt() : this fun is use for compressing/streching the our graphical object from SourceImage to Desti.Image
		StretchBlt(hdc, 0, 0, rc.right, rc.bottom,
			hdcMem, 0, 0, bitmap.bmWidth, bitmap.bmHeight, SRCCOPY);

		DeleteObject(hBitmap);
		DeleteDC(hdcMem);
		EndPaint(hwnd, &ps);

	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	}

	return (DefWindowProc(hwnd, iMsg, wParam, lParam));
}



