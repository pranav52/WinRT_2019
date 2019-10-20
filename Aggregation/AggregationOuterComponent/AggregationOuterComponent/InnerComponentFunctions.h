#pragma once

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

// CLSID FOR MultiplicationDivision class : {8F716F6C-B110-4E79-9B1B-7C8B37828B4D}
const CLSID CLSID_MultiplicationDivision =
{ 0x8f716f6c, 0xb110, 0x4e79, { 0x9b, 0x1b, 0x7c, 0x8b, 0x37, 0x82, 0x8b, 0x4d } };


// IID for IMultiplication interface : 
const IID IID_IMultiplication =
{ 0x78d62ec8, 0xb2dc, 0x475e, { 0xa2, 0x32, 0xa8, 0x9, 0x32, 0xd1, 0x4f, 0x95 } };


// IID for IDivision interface : 
const IID IID_IDivision =
{ 0xc938e583, 0xae56, 0x48de, { 0x94, 0x8d, 0x11, 0x71, 0xf7, 0x66, 0xeb, 0x1 } };

