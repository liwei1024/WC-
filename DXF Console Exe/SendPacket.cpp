#include "pch.h"
#include "SendPacket.h"

#define Asm_����CALL(cdov){\
	__asm {\
		__asm push cdov\
		__asm mov ecx, __������ַ\
		__asm mov ecx, [ecx]\
		__asm mov eax, __����CALL\
		__asm call eax\
	}\
}

#define Asm_�ܰ�CALL(param,len,type){\
	int cdov = 0;\
	if (len == 1)cdov = __�ܰ�CALL;\
	if (len == 2)cdov = __�ܰ�CALL + 0x30;\
	if (len == 3)cdov = __�ܰ�CALL + 0x60;\
	if (len == 4)cdov = __�ܰ�CALL + 0x90;\
	if(type == true){\
		__asm {\
			__asm mov eax, param\
			__asm push dword ptr[eax]\
			__asm mov ecx, __������ַ\
			__asm mov ecx, dword ptr ss : [ecx]\
			__asm mov eax, cdov\
			__asm call eax\
		}\
	}else {\
		__asm {\
			__asm push param\
			__asm mov ecx, __������ַ\
			__asm mov ecx, dword ptr ss : [ecx]\
			__asm mov eax, cdov\
			__asm call eax\
		}\
	}\
}

#define Asm_����CALL(){\
	__asm {\
		__asm mov eax, __����CALL\
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

void __declspec(naked) Asm_���ؽ�ɫ()
{
	Asm_����CALL(0x7);
	Asm_����CALL();
	__asm ret
	__asm int 3
	__asm int 3
	__asm int 3
	__asm int 3
	__asm int 3
}

void __declspec(naked) Asm_ѡ���ɫ(DWORD *params)
{
	Asm_����CALL(4);
	Asm_�ܰ�CALL(params, 3, true);
	Asm_����CALL();
	__asm ret
	__asm int 3
	__asm int 3
	__asm int 3
	__asm int 3
	__asm int 3
}