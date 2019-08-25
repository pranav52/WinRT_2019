#include<windows.h>
#include<stdio.h>


// global function declarations
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
DWORD WINAPI ThreadProcOne (LPVOID);
DWORD WINAPI ThreadProcTwo (LPVOID);

// WinMain()   ....(this is entry point function for th GUI programming)
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow)
{
	/* variable declarations
		WNDCLASSEX, HWND, MSG are the Structure.
		TCHAR is used for unicode purpose.
	*/
	WNDCLASSEX wndclass;
	HWND hwnd;
	MSG msg;
	TCHAR szAppName[] = TEXT("MyApp");


	// code :
	
	wndclass.cbSize = sizeof(WNDCLASSEX);  // cb means count of bytes
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

	// register above class 
	RegisterClassEx(&wndclass);

	// create window 
	hwnd = CreateWindow(szAppName, TEXT("MY Application"), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hInstance, NULL);

	ShowWindow(hwnd, iCmdShow);
	UpdateWindow(hwnd);

	
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return ((int)msg.wParam);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	HANDLE hThread1 = NULL;
	HANDLE hThread2 = NULL;
	TCHAR str[255];

	switch (iMsg)
	{
	case WM_CREATE :

		hThread1 = CreateThread (NULL, 0, (LPTHREAD_START_ROUTINE)ThreadProcOne, (LPVOID)hwnd, 0, NULL);
		hThread2 = CreateThread (NULL, 0, (LPTHREAD_START_ROUTINE)ThreadProcTwo, (LPVOID)hwnd, 0, NULL);
		break;

	case WM_LBUTTONDOWN :

		MessageBox(NULL, TEXT("Multithreading Application is arrived..!"), TEXT("Message"), MB_OK |MB_ICONINFORMATION);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break; 
	}
	return (DefWindowProc(hwnd, iMsg, wParam, lParam));
}

DWORD WINAPI ThreadProcOne (LPVOID param)
{
	HDC hdc;
	long int  i;
	TCHAR str[255];

	hdc = GetDC ((HWND)param);
	SetTextColor (hdc, RGB(0,255,0));
	SetBkColor (hdc, RGB(0,0,0));

	for (i =0; i<4294967295; i++)
	{
		wsprintf( str, TEXT("Thread_1 -> Increasing order : %ld"),i);
		TextOut (hdc, 5, 25, str, lstrlen(str));
	}
	ReleaseDC ((HWND)param, hdc);
	return 0;
}

DWORD WINAPI ThreadProcTwo (LPVOID param)
{
	HDC hdc;
	long int  j;
	TCHAR str[255];

	hdc = GetDC((HWND)param);
	SetTextColor(hdc, RGB(255 ,0, 0));
	SetBkColor(hdc, RGB(0, 0, 0));

	for (j=94967295; j>=0; j--)
	{
		wsprintf(str, TEXT("Thread_2 -> Decreasing order : %ld"), j);
		TextOut(hdc, 5, 45, str, lstrlen(str));
	}
	ReleaseDC((HWND)param, hdc);
	return 0;
}



