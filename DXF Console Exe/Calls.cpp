#include "pch.h"
#include "Calls.h"


Calls::Calls()
{
}


Calls::~Calls()
{
}

void __declspec(naked)Calls::CityPlane(DWORD params)
{
	__asm {
		mov eax, eax
		mov eax,eax
		ret
	}
}

void Calls::ExecCALL(LPCVOID Call, size_t nargs, ...)
{
	// �������
	int *Params = new int[nargs];
	size_t CallSize = 0;
	int CallAddress = 0;
	int ParamsAddress = 0;
	// ����Զ���̲߳���
	va_list argList;
	va_start(argList, nargs);
	for (size_t i = 0; i < nargs; i++)
		Params[i] = va_arg(argList, int);
	va_end(argList);
	// ��ȡԶ��call��С
	while (*(byte*)((DWORD)Call + CallSize) != 0xcc)
		CallSize++;
	// �����ڴ�ռ�
	CallAddress = (int)_Process.AllocMemory((int)Call, CallSize);
	ParamsAddress = (int)_Process.AllocMemory((int)Params, nargs);
	// д�뺯���Ͳ���
	_Process.WriteMemory(CallAddress, Call, CallSize);
	_Process.WriteMemory(ParamsAddress, Params, nargs);
	// ����Զ���߳�
	_Process.CreateThread(CallAddress, ParamsAddress);
	delete[]Params;
}