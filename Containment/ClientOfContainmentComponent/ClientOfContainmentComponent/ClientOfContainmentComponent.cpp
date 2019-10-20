#include<Windows.h>
#include"HeaderForClientOfContainment.h"


LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
//WinMain :
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPreveInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// variable declaration :

	WNDCLASSEX wndclass;
	HWND hwnd;
	MSG msg;
	TCHAR AppName[] = TEXT("ComClient");
	HRESULT hr;

	hr = CoInitialize(NULL);
	if (FAILED(hr))
	{
		MessageBox(NULL, TEXT("COM Library Can Not Be Initialized. \nProgram Will Now Exit."), TEXT("Program Error"), MB_OK);
		exit(0);
	}

	//WNDCLASSEX initialization

	wndclass.cbSize = sizeof(wndclass);
	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.lpfnWndProc = WndProc;
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndclass.hInstance = hInstance;
	wndclass.lpszClassName = AppName;
	wndclass.lpszMenuName = NULL;
	wndclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	//register window class
	RegisterClassEx(&wndclass);

	//create window
	hwnd = CreateWindow(AppName,
		TEXT("Client Of COM DLL SERVER"),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		NULL,
		NULL,
		hInstance,
		NULL);

	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);

	//message loop :
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	// COM Un-initialize
	CoUninitialize();
	return((int)msg.wParam);
}
// window procedure
LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	// local declaration of reference pointers...
	ISum *pISum = NULL;
	ISubtract *pISubtract = NULL;
	IMultiplication *pIMultiplication = NULL;
	IDivision *pIDivision = NULL;

	HRESULT hr;
	int iNum1 = 100;
	int iNum2 = 5; 
	int iSum, iSubtraction, iMultiplication, iDivision;
	TCHAR str[255];

	switch (iMsg)
	{
	case WM_CREATE:
		hr = CoCreateInstance(CLSID_SumSubtract, NULL, CLSCTX_INPROC_SERVER, IID_ISum, (void **)&pISum);

		if (FAILED(hr))
		{
			MessageBox(hwnd, TEXT("ISum Interface Can Not be Obtained"), TEXT("ERROR"), MB_OK);
			DestroyWindow(hwnd);
		}

		// initialize the varible	
		//iNum1 = 50;
		//iNum2 = 50;

		// call SumOfTwoIntegers() of ISum to get the sum
		pISum->SumOfTwoIntegers(iNum1, iNum2, &iSum);
		// display result :
		wsprintf(str, TEXT("Sum of %d and %d = %d"), iNum1, iNum2, iSum);
		MessageBox(hwnd, str, TEXT("RESULT"), MB_OK);

		hr = pISum->QueryInterface(IID_ISubtract, (void **)&pISubtract);
		if (FAILED(hr))
		{
			MessageBox(hwnd, TEXT("ISubtract Interface Can Not be Obtained"), TEXT("Error"), MB_OK);
			DestroyWindow(hwnd);
		}
		// releasing pISum :
		pISum->Release();
		pISum = NULL;

		// again initialize argrument iNum1, iNum2
		//iNum1 = 200;
		//iNum2 = 150;

		// call to SubtractionOfTwoIntegers() of class ISubtract
		pISubtract->SubtractionOfTwoIntegers(iNum1, iNum2, &iSubtraction);
		//display result :
		wsprintf(str, TEXT("Subtraction of %d and %d = %d"), iNum1, iNum2, iSubtraction);
		MessageBox(hwnd, str, TEXT("RESULT"), MB_OK);

		hr = pISubtract->QueryInterface(IID_IMultiplication, (void **) &pIMultiplication);
		if (FAILED(hr))
		{
			MessageBox(hwnd, TEXT("IMultiplication Interface Can Not be Obtained"), TEXT("Error"), MB_OK);
			DestroyWindow(hwnd);
		}
		// releasing pISubtract :
		pISubtract->Release();
		pISubtract = NULL;

		pIMultiplication->MultiplicationOfTwoInts(iNum1, iNum2, &iMultiplication);
		// disply result :
		wsprintf(str, TEXT("Multiplication of %d and %d = %d"), iNum1, iNum2, iMultiplication);
		MessageBox(hwnd, str, TEXT("RESULT"), MB_OK);

		hr = pIMultiplication->QueryInterface(IID_IDivision,(void **)&pIDivision);
		if (FAILED(hr))
		{
			MessageBox(hwnd, TEXT("IDivision Interface Can Not be Obtained"), TEXT("Error"), MB_OK);
			DestroyWindow(hwnd);
		}

		pIMultiplication->Release();
		pIMultiplication = NULL;

		pIDivision->DivisionOfTwoInts(iNum1, iNum2, &iDivision);
		// display result :
		wsprintf(str, TEXT("Division of %d and %d = %d"), iNum1, iNum2, iDivision);
		MessageBox(hwnd, str, TEXT("RESULT"), MB_OK);

		pIDivision->Release();
		pIDivision = NULL;

	

		DestroyWindow(hwnd);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	}
	return (DefWindowProc(hwnd, iMsg, wParam, lParam));
}









