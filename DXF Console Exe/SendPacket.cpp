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

void __declspec(naked) SP_���ؽ�ɫ()
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

void __declspec(naked) SP_ѡ���ɫ(DWORD params)
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

void __declspec(naked) SP_����(DWORD params)
{
	Asm_����CALL(22);
	Asm_�ܰ�CALL(0, 1, false);
	Asm_�ܰ�CALL(params + 0x0, 2, true);//λ��
	Asm_�ܰ�CALL(params + 0x4, 3, true);//����
	Asm_�ܰ�CALL(2, 3, false);			  
	Asm_�ܰ�CALL(params + 0x8, 3, true);
	Asm_����CALL();
	__asm ret
	__asm int 3
	__asm int 3
	__asm int 3
	__asm int 3
	__asm int 3
}