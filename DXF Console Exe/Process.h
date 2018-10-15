#pragma once
struct MemoryStruct
{
	LPVOID Address;
	size_t Size;
};
class Process
{
public:
	HWND hWnd = NULL;
	DWORD ProcessId = NULL;
	HANDLE hProcess = NULL;
	std::map<int, MemoryStruct> MemoryVector;
	Process();
	~Process();
	BOOL Run(LPCSTR lpClass = VMProtectDecryptStringA("地下城与勇士"), LPCSTR lpName = VMProtectDecryptStringA("地下城与勇士"));
	void Clear();
	// 读内存
	BOOL ReadMemory(INT baseAddress, LPVOID lpBuffer, INT nSize);
	// 读字节
	byte ReadByte(INT address);
	// 读短整形
	short ReadShort(INT address);
	// 读整形
	int ReadInteger(INT address);
	// 读长整形
	LONGLONG ReadLong(INT address);
	// 读单浮点型
	float ReadFloat(INT lpBaseAddress);
	// 读双浮点型
	double ReadDouble(INT lpBaseAddress);
	// 读字节数组
	std::vector<byte> ReadBytes(INT lpBaseAddress, INT len);
	// 读字符串
	CHAR * ReadString(INT lpBaseAddress, INT len);
	DWORD ReadOfset(DWORD lpBaseAddress, std::vector<int> Ofsets);
	// 写内存
	BOOL WriteMemory(INT lpBaseAddress, LPCVOID lpBuffer, INT nSize);
	// 写字节
	BOOL WriteByte(INT lpBaseAddress, byte lpBuffer);
	// 写短整形
	BOOL WriteShort(INT lpBaseAddress, short lpBuffer);
	// 写整形
	BOOL WriteInteger(INT lpBaseAddress, int lpBuffer);
	// 写长整形
	BOOL WriteLong(INT lpBaseAddress, LONGLONG lpBuffer);
	// 写单浮点
	BOOL WriteFloat(INT lpBaseAddress, float lpBuffer);
	// 写双浮点
	BOOL WriteDouble(INT lpBaseAddress, double lpBuffer);
	// 写字节数组
	BOOL WriteBytes(INT lpBaseAddress, std::vector<int> bytes);
	// 写字符串
	BOOL WriteString(INT lpBaseAddress, LPCWSTR lpBuffer);
	void UnHookLdrInitializeThunk();
	LPVOID AllocMemory(int index, size_t size);
	void FreeAllMemory();
	HANDLE CreateThread(int StartAddress, int Paramter);
};

