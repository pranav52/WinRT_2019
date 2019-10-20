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

// CLSID FOR MultiplicationDivision class : {DB6DBAD9-0F41-4DF1-9661-8B19EBFF0D74}
const CLSID CLSID_MultiplicationDivision =
{ 0xdb6dbad9, 0xf41, 0x4df1, { 0x96, 0x61, 0x8b, 0x19, 0xeb, 0xff, 0xd, 0x74 } };

// IID for IMultiplication class : {C200F7A5-8216-4D34-8B6E-72FC9C01B14B}
const IID IID_IMultiplication =
{ 0xc200f7a5, 0x8216, 0x4d34, { 0x8b, 0x6e, 0x72, 0xfc, 0x9c, 0x1, 0xb1, 0x4b } };

// IID for IDivision class : {2D2BB4FB-E0F4-4BE1-AC76-3F429F13EB51}
const IID IID_IDivision =
{ 0x2d2bb4fb, 0xe0f4, 0x4be1, { 0xac, 0x76, 0x3f, 0x42, 0x9f, 0x13, 0xeb, 0x51 } };

