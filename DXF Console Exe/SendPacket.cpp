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


SendPacket::SendPacket()
{
}


SendPacket::~SendPacket()
{
}
