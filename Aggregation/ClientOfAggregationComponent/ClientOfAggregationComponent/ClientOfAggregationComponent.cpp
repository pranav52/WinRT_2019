#include<Windows.h>
#include"HeaderForClientOfAggregationComponent.h"


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
	IUnknown *pIUnknown = NULL;
	ISum *pISum = NULL;
	ISubtract *pISubtract = NULL;
	IMultiplication *pIMultiplication = NULL;
	IDivision *pIDivision = NULL;

	HRESULT hr;
	int iNum1;
	int iNum2;
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
		iNum1 = 50;
		iNum2 = 50;

// Usecase 1: calling any Outer function :

		pISum->SumOfTwoIntegers(iNum1, iNum2, &iSum);
		// display result :
		wsprintf(str, TEXT("Sum of %d and %d = %d"), iNum1, iNum2, iSum);
		MessageBox(hwnd, str, TEXT("RESULT"), MB_OK);

// Usecase 2: calling another outer function from existing outer function :
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
		iNum1 = 100;
		iNum2 = 150;

		pISubtract->SubtractionOfTwoIntegers(iNum1, iNum2, &iSubtraction);
		//display result :
		wsprintf(str, TEXT("Subtraction of %d and %d = %d"), iNum1, iNum2, iSubtraction);
		MessageBox(hwnd, str, TEXT("RESULT"), MB_OK);

// Usecase 3: calling inner function on outer function :
		hr = pISubtract->QueryInterface(IID_IMultiplication, (void **)&pIMultiplication);
		if (FAILED(hr))
		{
			MessageBox(hwnd, TEXT("IMultiplication Interface Can Not be Obtained"), TEXT("Error"), MB_OK);
			DestroyWindow(hwnd);
		}
		// initialize variable :
		iNum1 = 25;
		iNum2 = 25;

		pIMultiplication->MultiplicationOfTwoInts(iNum1, iNum2, &iMultiplication);
		// disply result :
		wsprintf(str, TEXT("Multiplication of %d and %d = %d"), iNum1, iNum2, iMultiplication);
		MessageBox(hwnd, str, TEXT("RESULT"), MB_OK);

// Usecase 4: calling another inner fucntion from existing inner function :
		hr = pIMultiplication->QueryInterface(IID_IDivision, (void **)&pIDivision);
		if (FAILED(hr))
		{
			MessageBox(hwnd, TEXT("IDivision Interface Can Not be Obtained"), TEXT("Error"), MB_OK);
			DestroyWindow(hwnd);
		}

		pIMultiplication->Release();
		pIMultiplication = NULL;

		// initialize variable :
		iNum1 = 10;
		iNum2 = 10;

		pIDivision->DivisionOfTwoInts(iNum1, iNum2, &iDivision);
		// display result :
		wsprintf(str, TEXT("Division of %d and %d = %d"), iNum1, iNum2, iDivision);
		MessageBox(hwnd, str, TEXT("RESULT"), MB_OK);

// Usecase 5: calling outer function on inner function :
		hr = pIDivision->QueryInterface(IID_ISubtract, (void **)&pISubtract);
		if (FAILED(hr))
		{
			MessageBox(hwnd, TEXT("ISubtract Interface Can Not be Obtained"), TEXT("Error"), MB_OK);
			DestroyWindow(hwnd);
		}

		iNum1 = 510;
		iNum2 = -100;

		pISubtract->SubtractionOfTwoIntegers(iNum1, iNum2, &iSubtraction);
		// display result :
		wsprintf(str, TEXT("Subtraction of %d and %d = %d"), iNum1, iNum2, iSubtraction);
		MessageBox(hwnd, str, TEXT("RESULT"), MB_OK);

/*
// Usecase : cheaking IDENTITY() Outer's IUnknown == Inner's IUnknown
		hr = pIDivision->QueryInterface(IID_IUnknown, (void **)&pIUnknown);
		if (FAILED(hr))
		{
			MessageBox(hwnd, TEXT("ISubtract Interface Can Not be Obtained"), TEXT("Error"), MB_OK);
			DestroyWindow(hwnd);
		}

		hr = pISubtract->QueryInterface(IID_IUnknown, (void **)&pIUnknown);
		if (FAILED(hr))
		{
			MessageBox(hwnd, TEXT("ISubtract Interface Can Not be Obtained"), TEXT("Error"), MB_OK);
			DestroyWindow(hwnd);
		}
		if( CheckIdentity(pIDivision, pISubtract)==TRUE )
		{
			wsprintf(str, TEXT("Subtraction of %d and %d = %d"), iNum1, iNum2, iSubtraction);
			MessageBox(hwnd, str, TEXT("RESULT"), MB_OK);
		}

*/

	// releasing pISubtract :
		pISubtract->Release();
		pISubtract = NULL;

	// releasing pIDivision :
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









