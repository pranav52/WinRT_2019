#include<windows.h>

// global function declarations
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

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
	// initialization of WNDCLASSEX : In our program, their are total 12 members which get initialized 
	
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
	// here it returns string after registering class and 'ATOM' i.e. unmutable_string its return type.
	RegisterClassEx(&wndclass);

	// create window 
	hwnd = CreateWindow(szAppName, TEXT("MY Application"), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hInstance, NULL	);

	ShowWindow(hwnd, iCmdShow);
	UpdateWindow(hwnd);

	// message loop : this is heart of GUI programming and CALL_BACK function call goes from message loop.

	while (GetMessage(&msg, NULL, 0,0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return ((int)msg.wParam);
}

LRESULT CALLBACK WndProc( HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	TCHAR str[255];
	switch (iMsg)
	{
	
	case WM_DESTROY :
		PostQuitMessage(0);
		break; // so much imp break statement

	

	 }
	return (DefWindowProc(hwnd, iMsg, wParam, lParam));
}