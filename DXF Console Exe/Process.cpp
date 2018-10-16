#include "pch.h"
#include "Process.h"
#include "Utils.h"


using namespace std;

//ProcessInfo _ProcessInfo;

Process::Process()
{

}


Process::~Process()
{


}

BOOL Process::Run(LPCSTR lpClass, LPCSTR lpName)
{
	VMProtectBeginUltra(" Process::Run");
	this->hWnd = FindWindow(VMProtectDecryptStringA(lpClass), VMProtectDecryptStringA(lpName));
	if (this->hWnd == NULL)
	{
		红色打印(VMProtectDecryptStringA("GetWindowHandle Fail! Error Code - < %d >"), GetLastError());
		return false;
	}
	GetWindowThreadProcessId(hWnd, &this->ProcessId);
	if (this->ProcessId == NULL)
	{
		红色打印(VMProtectDecryptStringA("GetProcessId Fail! Error Code - < %d >"), GetLastError());
		return false;
	}
	this->hProcess = OpenProcess(PROCESS_ALL_ACCESS, false, this->ProcessId);
	if (this->hProcess == NULL)
	{
		红色打印(VMProtectDecryptStringA("OpenProcess Fail! Error Code - < %d >"), GetLastError());
		return false;
	}
	this->UnHookLdrInitializeThunk();
	绿色打印(VMProtectDecryptStringA("hWnd			< %d >"), this->hWnd);
	红色打印(VMProtectDecryptStringA("hProcess		< %d >"), this->hProcess);
	黄色打印(VMProtectDecryptStringA("ProcessId		< %d >"), this->ProcessId);
	return true;
	VMProtectEnd();
}

void Process::Clear()
{
	FreeAllMemory();
	::CloseHandle(hProcess);
	//OutputDebugString("123456789");
}

//=====================================读======================================//
BOOL Process::ReadMemory(INT baseAddress, LPVOID lpBuffer, INT nSize)
{
	VMProtectBeginUltra("ReadMemory");
	SIZE_T lpNumberOfBytesRead;
	if (ReadProcessMemory(hProcess, (LPCVOID)baseAddress, lpBuffer, (SIZE_T)nSize, &lpNumberOfBytesRead) == FALSE) {
		return false;
	}
	if (lpNumberOfBytesRead != nSize) {
		return false;
	}
	return true;
	VMProtectEnd();
}

byte Process::ReadByte(INT address)
{
	byte lpBuffer;
	ReadMemory(address, &lpBuffer, sizeof(lpBuffer));
	return lpBuffer;
}

short Process::ReadShort(INT address)
{
	short lpBuffer;
	ReadMemory(address, &lpBuffer, sizeof(lpBuffer));
	return lpBuffer;
}

int Process::ReadInteger(INT address)
{
	int lpBuffer;
	ReadMemory(address, &lpBuffer, sizeof(lpBuffer));
	return lpBuffer;
}

LONGLONG Process::ReadLong(INT address)
{
	LONGLONG lpBuffer;
	ReadMemory(address, &lpBuffer, sizeof(lpBuffer));
	return lpBuffer;
}

float Process::ReadFloat(INT lpBaseAddress)
{
	float lpBuffer;
	ReadMemory(lpBaseAddress, &lpBuffer, sizeof(lpBuffer));
	return lpBuffer;
}

double Process::ReadDouble(INT lpBaseAddress)
{
	double lpBuffer;
	ReadMemory(lpBaseAddress, &lpBuffer, sizeof(lpBuffer));
	return lpBuffer;
}

vector<byte> Process::ReadBytes(INT lpBaseAddress, INT len)
{
	byte * lpBuffer;
	lpBuffer = new byte[len];
	memset(lpBuffer, 0, len);
	ReadMemory(lpBaseAddress, lpBuffer, len);
	vector<byte>  result;
	result.resize(len);
	for (INT i = 0; i < len; i++)
	{
		result[i] = lpBuffer[i];
	}
	delete[]lpBuffer;
	return result;
}

CHAR* Process::ReadString(INT lpBaseAddress, INT len)
{
	TCHAR *lpBuffer;
	len = len * 2 + 2;
	lpBuffer = new TCHAR[len];
	ReadMemory(lpBaseAddress, lpBuffer, len);
	CHAR * str = unicodeToAnsi((const wchar_t *)lpBuffer);
	return str;
}

DWORD Process::ReadOfset(DWORD lpBaseAddress, vector<int> Ofsets)
{
	DWORD OfsetAddress = ReadInteger(lpBaseAddress);
	for (size_t i = 0; i < Ofsets.size(); i++)
	{
		OfsetAddress = ReadInteger(OfsetAddress + Ofsets[i]);
	}
	return OfsetAddress;
}

//=====================================写======================================//

BOOL Process::WriteMemory(INT lpBaseAddress, LPCVOID lpBuffer, INT nSize)
{
	VMProtectBeginUltra("WriteMemory");
	SIZE_T lpNumberOfBytesRead;
	if (WriteProcessMemory(hProcess, (LPVOID)lpBaseAddress, lpBuffer, (SIZE_T)(nSize), &lpNumberOfBytesRead) == false) {
		printf(VMProtectDecryptStringA("写入 %x 内存时失败！\n"), lpBaseAddress);
		system("pause");
		return false;
	}
	if (lpNumberOfBytesRead != nSize) {
		printf(VMProtectDecryptStringA("写入 %x 内存时实际写入的长度与要写入的长度不一致！\n"), lpBaseAddress);
		system("pause");
		return false;
	}
	return true;
	VMProtectEnd();
}

BOOL Process::WriteByte(INT lpBaseAddress, byte lpBuffer)
{
	return WriteMemory(lpBaseAddress, &lpBuffer, sizeof(lpBuffer));
}

BOOL Process::WriteShort(INT lpBaseAddress, short lpBuffer)
{
	return WriteMemory(lpBaseAddress, &lpBuffer, sizeof(lpBuffer));
}

BOOL Process::WriteInteger(INT lpBaseAddress, int lpBuffer)
{
	return WriteMemory(lpBaseAddress, &lpBuffer, sizeof(lpBuffer));
}

BOOL Process::WriteLong(INT lpBaseAddress, LONGLONG lpBuffer)
{
	return WriteMemory(lpBaseAddress, &lpBuffer, sizeof(lpBuffer));
}

BOOL Process::WriteFloat(INT lpBaseAddress, float lpBuffer)
{
	return WriteMemory(lpBaseAddress, &lpBuffer, sizeof(lpBuffer));
}

BOOL Process::WriteDouble(INT lpBaseAddress, double lpBuffer)
{
	return WriteMemory(lpBaseAddress, &lpBuffer, sizeof(lpBuffer));
}

BOOL Process::WriteBytes(INT lpBaseAddress, vector<int> bytes)
{
	INT size = bytes.size();
	byte *lpBuffer = new byte[size];
	for (INT i = 0; i < size; i++)
	{
		lpBuffer[i] = bytes[i];
	}
	bool result = WriteMemory(lpBaseAddress, lpBuffer, size);
	delete[]lpBuffer;
	return result;
}

BOOL Process::WriteString(INT lpBaseAddress, LPCWSTR lpBuffer)
{
	INT len = wcslen(lpBuffer) * 2 + 2;
	return WriteMemory(lpBaseAddress, (LPCVOID)lpBuffer, len);
}

void Process::UnHookLdrInitializeThunk()
{
	this->WriteBytes((int)GetProcAddress(GetModuleHandleA(VMProtectDecryptStringA("ntdll.dll")), VMProtectDecryptStringA("LdrInitializeThunk")), { 0x8b, 0xff, 0x55, 0x8b, 0xec });
}

// 申请内存空间
LPVOID Process::AllocMemory(int index,size_t size)
{
	VMProtectBeginUltra("AllocMemory");
	MemoryStruct _MemoryStruct;
	_MemoryStruct = this->MemoryVector[index];
	int TempBuffer;
	if (
		(int)_MemoryStruct.Address > 0 &&
		this->ReadMemory((INT)_MemoryStruct.Address,&TempBuffer,sizeof(TempBuffer)) == TRUE &&
		_MemoryStruct.Size == size
	)
	{
		return _MemoryStruct.Address;
	}
	_MemoryStruct.Address = VirtualAllocEx(hProcess, NULL, size, MEM_COMMIT, PAGE_EXECUTE_READWRITE);
	_MemoryStruct.Size = size;

	if (_MemoryStruct.Address == 0)
	{
		红色打印(VMProtectDecryptStringA("申请内存失败"));
		system("pause");

	}
	this->MemoryVector[index] = _MemoryStruct;
	VMProtectEnd();
	return _MemoryStruct.Address;
}

// 释放所有申请的内存
void Process::FreeAllMemory()
{
	VMProtectBeginUltra("FreeAllMemory");
	map<int, MemoryStruct>::iterator it;
	it = this->MemoryVector.begin();
	while (it != this->MemoryVector.end())
	{
		if (VirtualFreeEx(hProcess, it->second.Address, 0, MEM_RELEASE) == false)
			红色打印(VMProtectDecryptStringA("释放 %x 失败"), (int)it->second.Address);
		it++;
	}
	VMProtectEnd();
}

HANDLE Process::CreateThread(int StartAddress,int Paramter)
{
	VMProtectBeginUltra("CreateThread");
	return CreateRemoteThread(hProcess, NULL,0, (LPTHREAD_START_ROUTINE)StartAddress, (LPVOID)Paramter, 0, 0);
	VMProtectEnd();
}