#include "pch.h"
#include "Hook.h"
#include "utils.h"

Hook::Hook()
{
	
}


Hook::~Hook()
{
}

BOOL Hook::Jmp5(DWORD base,DWORD hook)
{
	BYTE JmpCode[5] = { 0xE8,0x0,0x0,0x0,0x0 };
	*((BYTE*)(JmpCode + 1)) = hook - base - 5;
	return _Process.WriteBytes(base, BytesToVectorInt(JmpCode,5));
}