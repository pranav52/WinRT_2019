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
	virtual HRESULT __stdcall MultiplicationOfTwoInts(int, int, int *) = 0; // pure virtual function
};

class IDivision :public IUnknown
{
	virtual HRESULT __stdcall DivisionOfTwoInts(int, int, int *) = 0; // pure virtual function
};

// CLSID of SumSubtract : {12F3BC0E-DF5C-4F95-A426-FB58758E7D34}
const CLSID CLSID_SumSubtract =
{ 0x12f3bc0e, 0xdf5c, 0x4f95, { 0xa4, 0x26, 0xfb, 0x58, 0x75, 0x8e, 0x7d, 0x34 } };

// IID of ISum :  {B2D76BDA-C125-4044-AF35-768C18525419}
const IID IID_ISum =
{ 0xb2d76bda, 0xc125, 0x4044, { 0xaf, 0x35, 0x76, 0x8c, 0x18, 0x52, 0x54, 0x19 } };

// IID of ISubtract : {69EFF71A-C462-43B6-A8AB-1A9F662D19FF}
const IID IID_ISubtract =
{ 0x69eff71a, 0xc462, 0x43b6, { 0xa8, 0xab, 0x1a, 0x9f, 0x66, 0x2d, 0x19, 0xff } };

// IID for IMultiplication class : {C200F7A5-8216-4D34-8B6E-72FC9C01B14B}
const IID IID_IMultiplication =
{ 0xc200f7a5, 0x8216, 0x4d34, { 0x8b, 0x6e, 0x72, 0xfc, 0x9c, 0x1, 0xb1, 0x4b } };

// IID for IDivision class : {2D2BB4FB-E0F4-4BE1-AC76-3F429F13EB51}
const IID IID_IDivision =
{ 0x2d2bb4fb, 0xe0f4, 0x4be1, { 0xac, 0x76, 0x3f, 0x42, 0x9f, 0x13, 0xeb, 0x51 } };
