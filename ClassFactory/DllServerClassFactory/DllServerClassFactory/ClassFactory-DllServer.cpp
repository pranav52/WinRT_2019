#include<Windows.h>
#include "ClassFactoryDllServer.h"

class CSumSubtract :public ISum, ISubtract
{
private:
	long m_cRef ;

public:
	//Constructor method:
	CSumSubtract(void);

	//destructor method:
	~CSumSubtract(void);

	HRESULT __stdcall QueryInterface(REFIID, void **);
	ULONG __stdcall AddRef(void);
	ULONG __stdcall Release(void);

	// ISum method declaration : (inherited methods)
	HRESULT __stdcall SumOfTwoIntegers(int, int, int *);

	//ISubtract method declaraion : (inherited method)
	HRESULT __stdcall SubtractionOfTwoIntegers(int, int, int *);
};

class CSumSubtractClassFactory :public IClassFactory
{
private:
	long m_cRef ; 
	// why it is long...?  => becoz return type of InterlockedIncrement() and InterlockedDecrement() is long.

public:

	// constructor method :
	CSumSubtractClassFactory(void);

	// destructor method :
	~CSumSubtractClassFactory(void);
	
	// IUnkown method :
	HRESULT __stdcall QueryInterface(REFIID, void **);
	ULONG __stdcall AddRef(void);
	ULONG __stdcall Release(void);

	// IClassFactory method :
	HRESULT __stdcall CreateInstance(IUnknown *, REFIID, void **);
	HRESULT __stdcall LockServer(BOOL);
};

// global varible declarations..
long glNumberOfActiveComponents = 0; // no of active components
long glNumberOfServerLocks = 0; // no of locks on this dll

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

// Implementation of all methods of class CSsumSubtract :
// constructor method :
CSumSubtract::CSumSubtract(void)
{
	m_cRef = 1; //why m_cRef=1 ? => to avoid failure of  QueryInterface()
	InterlockedIncrement(&glNumberOfActiveComponents);// increment global counter
}
// destructor method :
CSumSubtract::~CSumSubtract(void)
{
	InterlockedDecrement(&glNumberOfActiveComponents); // decrement global counter
}
// QueryInterface() method :
HRESULT CSumSubtract::QueryInterface(REFIID riid,void  **ppv)
{
	if (riid == IID_IUnknown)
		*ppv = static_cast<ISum *>(this);
	else if (riid == IID_ISum)
		*ppv = static_cast<ISum *>(this);
	else if (riid == IID_ISubtract)
		*ppv = static_cast<ISubtract *>(this);
	else
	{
		*ppv = NULL;
		return(E_NOINTERFACE);
	}
	reinterpret_cast<IUnknown *>(*ppv)->AddRef();
	return(S_OK);
}
// AddRef() method:
ULONG CSumSubtract::AddRef()
{
	InterlockedIncrement(&m_cRef);
	return(m_cRef);
}
// Release() method:
ULONG CSumSubtract::Release()
{
	InterlockedDecrement(&m_cRef);
	if (m_cRef == 0)
	{
		delete(this);
		return(0);
	}
	return (m_cRef);
}
// ISum class method : SumOfTwoIntegers(..)
HRESULT CSumSubtract::SumOfTwoIntegers(int num1, int num2, int *pSum)
{
	*pSum = num1 + num2;
	return (S_OK);
}
// ISubtract class method : SubtractOfTwoInteger(...)
HRESULT CSumSubtract::SubtractionOfTwoIntegers(int num1, int num2, int *pSubtract)
{
	*pSubtract = num1 - num2;
	return(S_OK);
}

// Implementation of class CSumSubtractClassFactory's methods :
//construct method :
CSumSubtractClassFactory::CSumSubtractClassFactory()
{
	m_cRef = 1; // initilize to 1 for avoiding failure of QueryInterface
}

// destructor method :
CSumSubtractClassFactory::~CSumSubtractClassFactory()
{
	// keep it blank
}

// QI method :
HRESULT CSumSubtractClassFactory::QueryInterface(REFIID riid, void **ppv)
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

// AddRef() method:
ULONG CSumSubtractClassFactory::AddRef()
{
	InterlockedIncrement(&m_cRef);
	return(m_cRef);
}
// Release() method:
ULONG CSumSubtractClassFactory::Release()
{
	InterlockedDecrement(&m_cRef);
	if (m_cRef == 0)
	{
		delete(this);
		return(0);
	}
	return (m_cRef);
}

// Implementating CreateInstance method:
HRESULT CSumSubtractClassFactory::CreateInstance(IUnknown *pUnkouter, REFIID riid, void **ppv)
{
	CSumSubtract *pSumSubtract = NULL;
	HRESULT hr;

	if (pUnkouter != NULL)
		return(CLASS_E_NOAGGREGATION);
	// create instance of CSumSubtract class :
	pSumSubtract = new CSumSubtract;
	if (pSumSubtract == NULL)
		return (E_OUTOFMEMORY);

	//MessageBox(NULL, TEXT("In create-Instance !"), TEXT("ERROR"), MB_OK); // error cheaking

	hr = pSumSubtract->QueryInterface(riid, ppv);
	pSumSubtract->Release();

	//MessageBox(NULL, TEXT("hr Succefully returned...!"), TEXT("ERROR"), MB_OK);
	return(hr);
}
HRESULT CSumSubtractClassFactory::LockServer(BOOL fLock)
{
	if (fLock)
		InterlockedIncrement(&glNumberOfServerLocks);
	else
		InterlockedDecrement(&glNumberOfActiveComponents);
	return(S_OK);
}

extern "C" HRESULT __stdcall DllGetClassObject(REFCLSID rclsid, REFIID riid, void **ppv)
{
	CSumSubtractClassFactory *pSumSubtractClassFactory = NULL;
	HRESULT hr;

	if (rclsid != CLSID_SumSubtract)
		return(CLASS_E_CLASSNOTAVAILABLE);

	// create instance of classfactory class:
	pSumSubtractClassFactory = new CSumSubtractClassFactory;
	if (pSumSubtractClassFactory == NULL)
		return(E_OUTOFMEMORY);

	hr = pSumSubtractClassFactory->QueryInterface(riid, ppv);
	pSumSubtractClassFactory->Release();
	return(hr);
}
extern "C" HRESULT __stdcall DllCanUnloadNow(void)
{
	if ((glNumberOfActiveComponents == 0) && (glNumberOfServerLocks == 0))
		return(S_OK);
	else
		return(S_FALSE);
}






