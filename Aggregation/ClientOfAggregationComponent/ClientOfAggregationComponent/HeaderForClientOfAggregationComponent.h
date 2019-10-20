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
class IMultiplication :public IUnknown
{
public:
	virtual HRESULT __stdcall MultiplicationOfTwoInts(int, int, int *) = 0; // pure virtual function
};

class IDivision :public IUnknown
{
public:
	virtual HRESULT __stdcall DivisionOfTwoInts(int, int, int *) = 0; // pure virtual function
};

// CLSID of SumSubtract : {02335F04-3981-4700-B0AF-8DE9B89B4957}
const CLSID CLSID_SumSubtract =
{ 0x2335f04, 0x3981, 0x4700, { 0xb0, 0xaf, 0x8d, 0xe9, 0xb8, 0x9b, 0x49, 0x57 } };

// IID of ISum interface:  
const IID IID_ISum =
{ 0x23dfa406, 0x3392, 0x45aa, { 0xb7, 0x1a, 0x4f, 0x16, 0x24, 0x72, 0xf9, 0x39 } };

// IID of ISubtract interface: 
const IID IID_ISubtract =
{ 0x72dc9949, 0xc5b0, 0x46b0, { 0xbc, 0x32, 0x5f, 0x6, 0x62, 0x90, 0x50, 0x52 } };

// CLSID FOR MultiplicationDivision class : {8F716F6C-B110-4E79-9B1B-7C8B37828B4D}
const CLSID CLSID_MultiplicationDivision =
{ 0x8f716f6c, 0xb110, 0x4e79, { 0x9b, 0x1b, 0x7c, 0x8b, 0x37, 0x82, 0x8b, 0x4d } };


// IID for IMultiplication interface : 
const IID IID_IMultiplication =
{ 0x78d62ec8, 0xb2dc, 0x475e, { 0xa2, 0x32, 0xa8, 0x9, 0x32, 0xd1, 0x4f, 0x95 } };


// IID for IDivision interface : 
const IID IID_IDivision =
{ 0xc938e583, 0xae56, 0x48de, { 0x94, 0x8d, 0x11, 0x71, 0xf7, 0x66, 0xeb, 0x1 } };


