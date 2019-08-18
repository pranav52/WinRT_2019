#include<Windows.h>

BOOL WINAPI DllMain(HINSTANCE hDll, DWORD dwReason, LPVOID )
{
	switch (dwReason)
	{
	case DLL_PROCESS_ATTACH :
		
		break;

	case DLL_THREAD_ATTACH :

		break;

	case DLL_THREAD_DETACH :

		break;

	case DLL_PROCESS_DETACH :

		break;
	}

	return (TRUE);

}// end of DllMain

// __declspec indicates this function is exportable
extern "C" __declspec (dllexport) int MakeSquare(int Num) 
{
	return (Num*Num);
}

extern "C" BOOL IsNumberNegative(int Num)
{
	if (Num > 0)
		return (TRUE);
	else
		return (FALSE);
}


