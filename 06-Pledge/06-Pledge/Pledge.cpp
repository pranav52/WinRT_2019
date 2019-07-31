//include headers
#include <Windows.h>

//declare window procedure
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

//Our GUI Main function :
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE prevInstance, LPSTR lpszCmdLine, int iCmdShow)
{
	//local variable
	WNDCLASSEX wndclass;
	HWND hwnd;
	MSG msg;
	TCHAR szAppName[] = TEXT("IndiaPledge");

	//code
	wndclass.cbSize = sizeof(WNDCLASSEX);
	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.cbWndExtra = 0;
	wndclass.cbClsExtra = 0;
	wndclass.lpfnWndProc = WndProc;
	wndclass.hInstance = hInstance;
	wndclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.lpszClassName = szAppName;
	wndclass.lpszMenuName = NULL;


	//Register above class
	RegisterClassEx(&wndclass);

	//create window in memory
	hwnd = CreateWindow(szAppName,
		TEXT("India Pledge"),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		NULL,
		NULL,
		hInstance,
		NULL
	);

	//show window
	ShowWindow(hwnd, iCmdShow);
	UpdateWindow(hwnd);

	//messsage loop
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}


	return ((int)msg.wParam);
}



//Defination of window procedure
LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;
	int X = 50, Y = 35, Z = 15;

	switch (iMsg)
	{

	case WM_CREATE:


		MessageBox(NULL, TEXT("WM_CREATE is arrived..!"), TEXT("MESSAGE"), MB_OK | MB_ICONINFORMATION);
		break;

	case WM_PAINT:

		//call specialist
		hdc = BeginPaint(hwnd, &ps);


		//set backgroud color
		SetBkColor(hdc, RGB(0, 0, 0));

		//Orange
		SetTextColor(hdc, RGB(255, 125, 0));

		TextOut(hdc, X, Y += Z, TEXT("India is my country."), strlen("India is my country."));
		TextOut(hdc, X, Y += Z, TEXT("All Indians are my brothers and sisters."), strlen("all Indians are my brothers and sisters."));
		TextOut(hdc, X, Y += Z, TEXT("I love my country, and"), strlen("I love my country, and"));
		TextOut(hdc, X, Y += Z, TEXT("I am proud of its rich and varied heritage."), strlen("I am proud of its rich and varied heritage."));

		//White
		SetTextColor(hdc, RGB(255, 255, 255));
		TextOut(hdc, X, Y += Z, TEXT("I shall always strive to be worthy of it."), strlen("I shall always strive to be worthy of it."));
		TextOut(hdc, X, Y += Z, TEXT("I shall give my parents,"), strlen("I shall give my parents,"));
		TextOut(hdc, X, Y += Z, TEXT("teachers and all elders respect"), strlen("teachers and all elders respect"));
		TextOut(hdc, X, Y += Z, TEXT("and treat everyone with courtesy."), strlen("and treat everyone with courtesy."));

		//Green
		SetTextColor(hdc, RGB(0, 255, 0));

		TextOut(hdc, X, Y += Z, TEXT("To my country and my people,"), strlen("To my country and my people,"));
		TextOut(hdc, X, Y += Z, TEXT("I pledge my devotion."), strlen("I pledge my devotion."));
		TextOut(hdc, X, Y += Z, TEXT("In their well being and"), strlen("In their well being and"));
		TextOut(hdc, X, Y += Z, TEXT("prosperity lies my happiness."), strlen("prosperity lies my happiness."));

		//sent back the specialist
		EndPaint(hwnd, &ps);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}

	return (DefWindowProc(hwnd, iMsg, wParam, lParam));
}


