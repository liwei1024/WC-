#pragma once
class Hook
{
public:
	Hook();
	~Hook();
	BOOL Jmp5(DWORD base, DWORD hook);
};

