#include<Windows.h>
#include"ContainmentInnerComponent.h"

class CMultiplicationDivision:public IMultiplication, IDivision
{
private:
	long m_cRef;

public:

	// methods declarations :
	// constructor method :
	CMultiplicationDivision(void);

	//destructore method :
	~CMultiplicationDivision(void);

	// Inherited methods from IUnknown 
	HRESULT __stdcall QueryInterface(REFIID, void **);
	ULONG __stdcall AddRef(void);
	ULONG __stdcall Release(void);

	// inherited method from IMultiplication class
	HRESULT __stdcall MultiplicationOfTwoInts(int, int, int *);
	
	// inherited method from IDivision class
	HRESULT __stdcall DivisionOfTwoInts(int, int, int *);

};
class CMultiplicationDivisionClassFactory :public IClassFactory
{
private:
	long m_cRef;

public:

	// method declaration of class :
	// constructor method :
	CMultiplicationDivisionClassFactory(void);

	// destructor method :
	~CMultiplicationDivisionClassFactory(void);

	// inherited method from IUknown class :
	HRESULT __stdcall QueryInterface(REFIID, void **);
	ULONG __stdcall AddRef(void);
	ULONG __stdcall Release(void);

	// inherited method from IClassFactory class :

	HRESULT __stdcall CreateInstance(IUnknown *, REFIID, void **);
	HRESULT __stdcall LockServer(BOOL);
};

long glNumberOfActiveComponents = 0;
long glNumberOfServerLocks = 0;

BOOL WINAPI DllMain(HINSTANCE hdll, DWORD dwReason, LPVOID Reserved)
{
	switch (dwReason)
	{
	case DLL_PROCESS_ATTACH:
		break;

	case DLL_PROCESS_DETACH:
		break;
	}
	return (TRUE);
}

CMultiplicationDivision::CMultiplicationDivision(void)
{
	m_cRef = 1;
	InterlockedIncrement(&glNumberOfActiveComponents); // increment global counter
}

CMultiplicationDivision::~CMultiplicationDivision(void)
{
	InterlockedDecrement(&glNumberOfActiveComponents);
}

HRESULT CMultiplicationDivision::QueryInterface(REFIID riid, void **ppv)
{
	if (riid == IID_IUnknown)
		*ppv = static_cast<IMultiplication *>(this);
	else if (riid == IID_IMultiplication)
		*ppv = static_cast<IMultiplication *>(this);
	else if (riid == IID_IDivision)
		*ppv = static_cast<IDivision *>(this);
	else
	{
		*ppv = NULL;
		return(E_NOINTERFACE);
	}
	reinterpret_cast<IUnknown *>(*ppv)->AddRef();
	return (S_OK);
}
ULONG CMultiplicationDivision::AddRef()
{
	InterlockedIncrement(&m_cRef);
	return(m_cRef);
}
ULONG CMultiplicationDivision::Release()
{
	InterlockedDecrement(&m_cRef);
	if (m_cRef==0)
	{
		delete(this);
		return(0);
	}
	return(m_cRef);
}

HRESULT CMultiplicationDivision::MultiplicationOfTwoInts(int num1, int num2, int *pMultiplication)
{
	*pMultiplication =num1*num2;
	return(S_OK);
}
HRESULT CMultiplicationDivision::DivisionOfTwoInts(int num1, int num2, int *pDivision)
{
	*pDivision = num1 / num2;
	return(S_OK);
}

// Implemetation of ClassFactory class:
// constructor method :
CMultiplicationDivisionClassFactory::CMultiplicationDivisionClassFactory(void)
{
	m_cRef = 1;	
}
// destructor method :
CMultiplicationDivisionClassFactory::~CMultiplicationDivisionClassFactory(void)
{
	// keep it blank
}

HRESULT CMultiplicationDivisionClassFactory::QueryInterface(REFIID riid, void **ppv)
{
	if (riid == IID_IUnknown)
		*ppv = static_cast<IClassFactory *>(this);
	else if (riid == IID_IClassFactory)
		*ppv = static_cast<IClassFactory *>(this);
	else
	{
		*ppv = NULL;
		return(E_NOINTERFACE);
	}
	reinterpret_cast<IUnknown *>(*ppv)->AddRef();
	return(S_OK);	
}
ULONG CMultiplicationDivisionClassFactory::AddRef()
{
	InterlockedIncrement(&m_cRef);
	return(m_cRef);
}
ULONG CMultiplicationDivisionClassFactory::Release()
{
	InterlockedDecrement(&m_cRef);
	if (m_cRef==0)
	{
		delete(this);
		return(0);
	}
	return(m_cRef);
}

HRESULT CMultiplicationDivisionClassFactory::CreateInstance(IUnknown *pUnkOuter, REFIID riid, void **ppv)
{
	// reference vari declared..
	CMultiplicationDivision *pCMultiplicationDivision = NULL;
	HRESULT hr;
	MessageBox(NULL, TEXT("In CreateInstance of InnerComponent ..!"), TEXT("SUCESS"), MB_OK);
	if (pUnkOuter != NULL)
	{
		return (CLASS_E_NOAGGREGATION);
	}
	// create instance of CMultiplicationdivision class
	pCMultiplicationDivision = new CMultiplicationDivision;

	

	if (pCMultiplicationDivision == NULL)
		return(E_OUTOFMEMORY);

	hr = pCMultiplicationDivision->QueryInterface(riid, ppv);
	pCMultiplicationDivision->Release();

	MessageBox(NULL, TEXT("hr return Succesfully from CreateInstance of InnerComponent ..!"), TEXT("SUCESS"), MB_OK);
	return(hr);
}

HRESULT CMultiplicationDivisionClassFactory::LockServer(BOOL flock)
{
	if (flock)
		InterlockedIncrement(&glNumberOfServerLocks);
	else
		InterlockedDecrement(&glNumberOfServerLocks);
	return(S_OK);
}
// Implementation of Exportable function from this Dll :
extern "C" HRESULT __stdcall DllGetClassObject(REFCLSID rclsid, REFIID riid, void **ppv)
{
	CMultiplicationDivisionClassFactory *pCMultiplicationDivisionClassFactory = NULL;
	HRESULT hr;

	if (rclsid != CLSID_MultiplicationDivision)
		return(CLASS_E_CLASSNOTAVAILABLE);

	// create class factory instance 
	pCMultiplicationDivisionClassFactory = new CMultiplicationDivisionClassFactory;

	MessageBox(NULL, TEXT("In DllGetClassObject of InnerComponent...!"), TEXT("SUCCESS"), MB_OK);
	if (pCMultiplicationDivisionClassFactory == NULL)
		return(E_OUTOFMEMORY);

	hr = pCMultiplicationDivisionClassFactory->QueryInterface(riid, ppv);
	pCMultiplicationDivisionClassFactory->Release();

	MessageBox(NULL, TEXT("hr succesfully returns from DllGetClassObject of InnerComponent...!"), TEXT("SUCCESS"), MB_OK);
	return(hr);
}

extern "C" HRESULT DllCanUnloadNow(void)
{
	if ((glNumberOfActiveComponents == 0) && (glNumberOfServerLocks == 0))
		return (S_OK);
	else
		return(S_FALSE);
}






