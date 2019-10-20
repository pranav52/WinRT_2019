#pragma once

class ISum :public IUnknown
{
public:
	// ISum specific method declarations: this is pure virtual function
	virtual HRESULT __stdcall SumOfTwoIntegers(int, int, int *) = 0;
};
class ISubtract :public IUnknown
{
public:
	virtual HRESULT __stdcall SubtractionOfTwoIntegers(int, int, int *) = 0; // pure virtual function

};

// CLSID of SumSubtract : {02335F04-3981-4700-B0AF-8DE9B89B4957}
const CLSID CLSID_SumSubtract =
{ 0x2335f04, 0x3981, 0x4700, { 0xb0, 0xaf, 0x8d, 0xe9, 0xb8, 0x9b, 0x49, 0x57 } };

// IID of ISum :  
const IID IID_ISum =
{ 0x23dfa406, 0x3392, 0x45aa, { 0xb7, 0x1a, 0x4f, 0x16, 0x24, 0x72, 0xf9, 0x39 } };

// IID of ISubtract : 
const IID IID_ISubtract =
{ 0x72dc9949, 0xc5b0, 0x46b0, { 0xbc, 0x32, 0x5f, 0x6, 0x62, 0x90, 0x50, 0x52 } };




