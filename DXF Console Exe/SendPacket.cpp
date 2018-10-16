#include "pch.h"
#include "SendPacket.h"

#define Asm_缓冲CALL(cdov){\
	__asm {\
		__asm push cdov\
		__asm mov ecx, __发包基址\
		__asm mov ecx, [ecx]\
		__asm mov eax, __缓冲CALL\
		__asm call eax\
	}\
}

#define Asm_密包CALL(param,len,type){\
	int cdov = 0;\
	if (len == 1)cdov = __密包CALL;\
	if (len == 2)cdov = __密包CALL + 0x30;\
	if (len == 3)cdov = __密包CALL + 0x60;\
	if (len == 4)cdov = __密包CALL + 0x90;\
	if(type == true){\
		__asm {\
			__asm mov eax, param\
			__asm push dword ptr[eax]\
			__asm mov ecx, __发包基址\
			__asm mov ecx, dword ptr ss : [ecx]\
			__asm mov eax, cdov\
			__asm call eax\
		}\
	}else {\
		__asm {\
			__asm push param\
			__asm mov ecx, __发包基址\
			__asm mov ecx, dword ptr ss : [ecx]\
			__asm mov eax, cdov\
			__asm call eax\
		}\
	}\
}

#define Asm_发包CALL(){\
	__asm {\
		__asm mov eax, __发包CALL\
		__asm call eax\
	}\
}


//SendPacket::SendPacket()
//{
//}
//
//
//SendPacket::~SendPacket()
//{
//}

void __declspec(naked) SP_返回角色()
{
	Asm_缓冲CALL(0x7);
	Asm_发包CALL();
	__asm ret
	__asm int 3
	__asm int 3
	__asm int 3
	__asm int 3
	__asm int 3
}

void __declspec(naked) SP_选择角色(DWORD params)
{
	Asm_缓冲CALL(4);
	Asm_密包CALL(params, 3, true);
	Asm_发包CALL();
	__asm ret
	__asm int 3
	__asm int 3
	__asm int 3
	__asm int 3
	__asm int 3
}

void __declspec(naked) SP_卖物(DWORD params)
{
	Asm_缓冲CALL(22);
	Asm_密包CALL(0, 1, false);
	Asm_密包CALL(params + 0x0, 2, true);//位置
	Asm_密包CALL(params + 0x4, 3, true);//数量
	Asm_密包CALL(2, 3, false);			  
	Asm_密包CALL(params + 0x8, 3, true);
	Asm_发包CALL();
	__asm ret
	__asm int 3
	__asm int 3
	__asm int 3
	__asm int 3
	__asm int 3
}