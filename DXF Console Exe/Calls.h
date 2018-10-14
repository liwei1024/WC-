#pragma once
class Calls
{
public:
	Calls();
	~Calls();
	void CityPlane(DWORD params);
	void ExecCALL(LPCVOID Call, size_t nargs, ...);
};

