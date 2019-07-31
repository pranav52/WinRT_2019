#include<windows.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow)
{
	
	WNDCLASSEX wndclass;
	HWND hwnd;
	MSG msg;
	TCHAR szAppName[] = TEXT("MyApp");

	MessageBox(NULL, TEXT("MY_APPLICATION window is Started...!"), TEXT("MESSAGE"), MB_OK | MB_ICONINFORMATION);

	
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

	// register above class :
	RegisterClassEx(&wndclass);

	// create window :
	hwnd = CreateWindow(szAppName, TEXT("MY Application"), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hInstance, NULL);

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
	TCHAR str[255];
	switch (iMsg)
	{


	case WM_CREATE:
		wsprintf(str, TEXT("WM_CREATE Window is Arrived..!"));
		MessageBox(hwnd, str, TEXT("Message"), MB_OK | MB_ICONINFORMATION);
		break;

	case WM_KEYDOWN:
		wsprintf(str, TEXT("WM_KEYDOWN Window is Arrived..!"));
		MessageBox(hwnd, str, TEXT("Message"), MB_OK | MB_ICONINFORMATION | MB_APPLMODAL);
		break;

	case WM_LBUTTONDOWN:
		wsprintf(str, TEXT("WM_LBUTTONDOWN Window is Arrived..!"));
		MessageBox(hwnd, str, TEXT("Message"), MB_OK | MB_ICONINFORMATION | MB_SYSTEMMODAL );
		break;


	case WM_DESTROY:
		PostQuitMessage(0);
		break; 

	}
	return (DefWindowProc(hwnd, iMsg, wParam, lParam));
}