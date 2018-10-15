#pragma once
class Calls
{
public:
	Calls();
	~Calls();
	void static CityPlane(DWORD params);
	void ExecCALL(LPCVOID Call, size_t nargs, ...);
};

