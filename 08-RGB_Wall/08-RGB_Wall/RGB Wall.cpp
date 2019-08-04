// declaration of header file Windows.h>
#include<Windows.h>                      
#define MYTIMER 100

// global function declaration (our call-back_function)
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

// our main function i.e. WinMain()
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPreInstance, LPSTR lpszCmdLine, int iCmdShow)
{
	// declaration of local variables

	WNDCLASSEX wndclass; // we initialize our 12 class members in this WNDCLASSEX struct obj wndclass
	HWND hwnd;  // Handle of our window
	MSG msg;  // message_loop varible used for sending/posting of messages to OS
	TCHAR szAppName[] = TEXT("MY APP");

	// messagebox:
	MessageBox(NULL, TEXT("RGB_WALL is arrived...!!!"), TEXT("Message"), MB_OK | MB_ICONINFORMATION | MB_APPLMODAL);
	//code : 

	wndclass.cbSize = sizeof(WNDCLASSEX); // we get total size of WNDCLASSEX using count of byte and sizeof.
	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.cbClsExtra = 0;  // its used to get extra information about class
	wndclass.cbWndExtra = 0;  // its used to get extra info about our Window
	wndclass.lpfnWndProc = WndProc;   // this vari tells OS about our Callback name
	wndclass.hInstance = hInstance;
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndclass.lpszClassName = szAppName;
	wndclass.lpszMenuName = NULL;
	wndclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);


	// Regester above class :

	RegisterClassEx(&wndclass);

	// create window :

	hwnd = CreateWindow(szAppName,
		TEXT("RGB_WALL"),
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


	// message_loop : Heart of GUI_Application

	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);  //from here call goes to WndProc
	}
	return ((int)msg.wParam);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	RECT  rc;
	GetClientRect(hwnd, &rc);

	PAINTSTRUCT ps;
	static int iPaintflag = 0;

	
	switch (iMsg)
	{

	case WM_CREATE:
		SetTimer(hwnd, MYTIMER, 3000, NULL);
		break;

	case WM_TIMER:

		KillTimer(hwnd, MYTIMER);
		iPaintflag++;
		if (iPaintflag > 7)
			iPaintflag = 0;

		SetTimer(hwnd, MYTIMER, 1500, NULL);
		InvalidateRect(hwnd, &rc, FALSE);
		break;


	case WM_PAINT:

		RECT rctemp;
		rctemp.top = rc.top, rctemp.bottom = rc.bottom ;


		HBRUSH hBrush;
		hdc = BeginPaint(hwnd, &ps);

		if (iPaintflag >= 0) {

			rctemp.left = rc.left + (iPaintflag - 1) * (rc.right / 8);
			rctemp.right = (rc.right/8) + (iPaintflag - 1) * (rc.right / 8);
			
		}
		
			switch (iPaintflag)
			{


			case 0:
				hBrush = CreateSolidBrush(RGB(0, 0, 0));
				SelectObject(hdc, hBrush);
				FillRect(hdc, &rctemp, hBrush);
				break;

			case 1:
				hBrush = CreateSolidBrush(RGB(255, 0, 0));
				SelectObject(hdc, hBrush);
				FillRect(hdc, &rctemp, hBrush);
				break;

			case 2:
				hBrush = CreateSolidBrush(RGB(0, 255, 0));
				SelectObject(hdc, hBrush);
				FillRect(hdc, &rctemp, hBrush);
				break;

			case 3:
				hBrush = CreateSolidBrush(RGB(0, 0, 255));
				SelectObject(hdc, hBrush);
				FillRect(hdc, &rctemp, hBrush);
				break;

			case 4:
				hBrush = CreateSolidBrush(RGB(0, 255, 255));
				SelectObject(hdc, hBrush);
				FillRect(hdc, &rctemp, hBrush);
				break;

			case 5:
				hBrush = CreateSolidBrush(RGB(255, 0, 255));
				SelectObject(hdc, hBrush);
				FillRect(hdc, &rctemp, hBrush);
				break;

			case 6:
				hBrush = CreateSolidBrush(RGB(255, 255, 0));
				SelectObject(hdc, hBrush);
				FillRect(hdc, &rctemp, hBrush);
				break;

			case 7:
				hBrush = CreateSolidBrush(RGB(255, 255, 255));
				SelectObject(hdc, hBrush);
				FillRect(hdc, &rctemp, hBrush);
				break;

			}
		

			EndPaint(hwnd, &ps);
			break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;

		}
	
	return DefWindowProc(hwnd, iMsg, wParam, lParam);
}// end of call_back_function


