#include<Windows.h>
#include"ContainmentInnerComponent.h"
#include"OuterFuction.h"

class CSumSubtract :public ISum, ISubtract, IMultiplication, IDivision
{
private:
	long m_cRef;
	IMultiplication *m_pIMultiplication;
	IDivision *m_pIDivision;

public:
	//Constructor method:
	CSumSubtract(void);

	//destructor method:
	~CSumSubtract(void);

	HRESULT __stdcall QueryInterface(REFIID, void **);
	ULONG __stdcall AddRef(void);
	ULONG __stdcall Release(void);

	// ISum class method declaration : (inherited methods)
	HRESULT __stdcall SumOfTwoIntegers(int, int, int *);

	//ISubtract class method declaraion : (inherited method)
	HRESULT __stdcall SubtractionOfTwoIntegers(int, int, int *);

	//IMultiplication class method declaration : inherited method
	HRESULT __stdcall MultiplicationOfTwoInts(int, int, int *);

	//IDivision class method declaration : inherited method
	HRESULT __stdcall DivisionOfTwoInts(int, int, int *);

	//custom method for inner component reaction :
	HRESULT __stdcall InitializeInnerComponent(void);

};

class CSumSubtractClassFactory :public IClassFactory
{
private:
	long m_cRef;
	
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
	 // reference variables for accessing innercomponent dll functions...
	m_pIMultiplication = NULL;
	m_pIDivision = NULL;

	m_cRef = 1; //why m_cRef=1 ? => to avoid failure of  QueryInterface()
	InterlockedIncrement(&glNumberOfActiveComponents);// increment global counter
}
// destructor method :
CSumSubtract::~CSumSubtract(void)
{
	InterlockedDecrement(&glNumberOfActiveComponents); // decrement global counter
	if (m_pIMultiplication)
	{
		m_pIMultiplication->Release();
		m_pIMultiplication = NULL;
	}

	if (m_pIDivision)
	{
		m_pIDivision->Release();
		m_pIDivision = NULL;
	}
}
// QueryInterface() method :
HRESULT CSumSubtract::QueryInterface(REFIID riid, void  **ppv)
{
	if (riid == IID_IUnknown)
		*ppv = static_cast<ISum *>(this);
	else if (riid == IID_ISum)
		*ppv = static_cast<ISum *>(this);
	else if (riid == IID_ISubtract)
		*ppv = static_cast<ISubtract *>(this);
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
// IMultiplication class method : MultiplicationOfTwoInts(...)
HRESULT CSumSubtract::MultiplicationOfTwoInts(int num1, int num2, int *pMultiplication)
{
	// this is called as delegation....
	m_pIMultiplication->MultiplicationOfTwoInts(num1, num2, pMultiplication);
	return(S_OK);
}
// IDivision class method : DivisionOfTwoInts(...)
HRESULT CSumSubtract::DivisionOfTwoInts(int num1, int num2, int *pDivision)
{
	m_pIDivision->DivisionOfTwoInts(num1, num2, pDivision);
	return(S_OK);
}

// method to call functions from InnerComponent.dll
HRESULT CSumSubtract::InitializeInnerComponent(void)
{
	HRESULT hr;
	hr = CoCreateInstance(CLSID_MultiplicationDivision, NULL, CLSCTX_INPROC_SERVER, IID_IMultiplication, (void **) &m_pIMultiplication);
	if (FAILED(hr))
	{
		MessageBox(NULL, TEXT("IMUltiplication Interface cannot obtained !!"), TEXT("ERROR"), MB_OK);
		return(E_FAIL);
	}

	hr = m_pIMultiplication->QueryInterface(IID_IDivision, (void **)&m_pIDivision);
	if (FAILED(hr))
	{
		MessageBox(NULL, TEXT("IDivision Interface is not Obtained !!"), TEXT("ERROR"), MB_OK);
		return(E_FAIL);
	}

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

	MessageBox(NULL, TEXT("In create-Instance of OuterComponent!"), TEXT("SUCCESS"), MB_OK); // error cheaking

	hr = pSumSubtract->InitializeInnerComponent();
	if (FAILED(hr))
	{
		MessageBox(NULL, TEXT("Failed to initiate InnerComponent"), TEXT("ERROR"), MB_OK);
		pSumSubtract->Release();
		return(hr);
	}
	hr = pSumSubtract->QueryInterface(riid, ppv);
	pSumSubtract->Release();

	MessageBox(NULL, TEXT("hr Succefully returned from OuterComponent's CreateInstance to CLIENT...!"), TEXT("SUCCESS"), MB_OK);
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

	// create instance of classfactory class :
	pSumSubtractClassFactory = new CSumSubtractClassFactory;
	MessageBox(NULL, TEXT("In DllGetClassObject of OuterComponent...!"), TEXT("SUCCESS"), MB_OK);
	if (pSumSubtractClassFactory == NULL)
		return(E_OUTOFMEMORY);

	hr = pSumSubtractClassFactory->QueryInterface(riid, ppv);
	pSumSubtractClassFactory->Release();

	MessageBox(NULL, TEXT("hr Succefully returned from OuterComponent's DllGetClassObject...!"), TEXT("SUCCESS"), MB_OK);
	return(hr);
}
extern "C" HRESULT __stdcall DllCanUnloadNow(void)
{
	if ((glNumberOfActiveComponents == 0) && (glNumberOfServerLocks == 0))
		return(S_OK);
	else
		return(S_FALSE);
}






