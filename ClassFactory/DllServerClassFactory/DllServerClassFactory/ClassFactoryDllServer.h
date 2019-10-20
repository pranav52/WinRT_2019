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
	virtual HRESULT __stdcall SubtractionOfTwoIntegers(int, int, int *)= 0; // pure virtual function

};
// CLSID of SumSubtract : {3F47B079-CC58-459F-B2EC-5063C8EE8041}
const CLSID CLSID_SumSubtract=
{ 0x3f47b079, 0xcc58, 0x459f, { 0xb2, 0xec, 0x50, 0x63, 0xc8, 0xee, 0x80, 0x41 } };

// IID of ISum :  {6FEBD769-DCC3-40BD-9E51-3ACBA073029F}
const IID IID_ISum=
{ 0x6febd769, 0xdcc3, 0x40bd, { 0x9e, 0x51, 0x3a, 0xcb, 0xa0, 0x73, 0x2, 0x9f } };

// IID of ISubtract : {0F6F3587-B543-4FC5-8851-E0B76F629E47}
const IID IID_ISubtract=
{ 0xf6f3587, 0xb543, 0x4fc5, { 0x88, 0x51, 0xe0, 0xb7, 0x6f, 0x62, 0x9e, 0x47 } };




