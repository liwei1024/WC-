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
	// 定义变量
	int *Params = new int[nargs];
	size_t CallSize = 0;
	int CallAddress = 0;
	int ParamsAddress = 0;
	// 生成远程线程参数
	va_list argList;
	va_start(argList, nargs);
	for (size_t i = 0; i < nargs; i++)
		Params[i] = va_arg(argList, int);
	va_end(argList);
	// 获取远程call大小
	while (*(byte*)((DWORD)Call + CallSize) != 0xcc)
		CallSize++;
	// 分配内存空间
	CallAddress = (int)_Process.AllocMemory((int)Call, CallSize);
	ParamsAddress = (int)_Process.AllocMemory((int)Params, nargs);
	// 写入函数和参数
	_Process.WriteMemory(CallAddress, Call, CallSize);
	_Process.WriteMemory(ParamsAddress, Params, nargs);
	// 创建远程线程
	_Process.CreateThread(CallAddress, ParamsAddress);
	delete[]Params;
}