// DXF Console Exe.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include "Calls.h"

Process _Process;

size_t GetCallLength(LPCVOID lpcFirstAddress)
{
	printf("lpcFirstAddress %x\n", (DWORD)(lpcFirstAddress));
	size_t siLength = 0;
	while (*(byte*)((DWORD)lpcFirstAddress + siLength) != 0xcc)
		siLength++;
	return siLength;
}

void test(LPCVOID Call,size_t nargs,...)
{
	va_list argList;
	printf("%x\n", (int)Call);
	//char buffer[0x1024];
	va_start(argList, nargs);
	//vsprintf_s(buffer, Call, argList);
	//printf("%s\n", buffer);
	/*printf("%d\n", (int)argList);*/
	int value = 0;
	for (size_t i = 0; i < nargs; i++)
	{
		value = va_arg(argList, int);
		printf("value%d=%d\n", i + 1, value);
		//printf("%d\n", argList[i]);
	}
	va_end(argList);
}

int main()
{
	/*HANDLE hPrcess = 0;
	size_t len = GetCallLength(Calls::CityPlane);
	printf("CallLenght %d\n", len);
	len = GetCallLength(Calls::CityPlane2);
	printf("CallLenght %d\n", len);*/
	test((LPVOID)0x400500,5,1000,2,3,4,5,6);
	system("pause");
}


