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
	BOOL Run(LPCSTR lpClass = VMProtectDecryptStringA("���³�����ʿ"), LPCSTR lpName = VMProtectDecryptStringA("���³�����ʿ"));
	void Clear();
	// ���ڴ�
	BOOL ReadMemory(INT baseAddress, LPVOID lpBuffer, INT nSize);
	// ���ֽ�
	byte ReadByte(INT address);
	// ��������
	short ReadShort(INT address);
	// ������
	int ReadInteger(INT address);
	// ��������
	LONGLONG ReadLong(INT address);
	// ����������
	float ReadFloat(INT lpBaseAddress);
	// ��˫������
	double ReadDouble(INT lpBaseAddress);
	// ���ֽ�����
	std::vector<byte> ReadBytes(INT lpBaseAddress, INT len);
	// ���ַ���
	CHAR * ReadString(INT lpBaseAddress, INT len);
	DWORD ReadOfset(DWORD lpBaseAddress, std::vector<int> Ofsets);
	// д�ڴ�
	BOOL WriteMemory(INT lpBaseAddress, LPCVOID lpBuffer, INT nSize);
	// д�ֽ�
	BOOL WriteByte(INT lpBaseAddress, byte lpBuffer);
	// д������
	BOOL WriteShort(INT lpBaseAddress, short lpBuffer);
	// д����
	BOOL WriteInteger(INT lpBaseAddress, int lpBuffer);
	// д������
	BOOL WriteLong(INT lpBaseAddress, LONGLONG lpBuffer);
	// д������
	BOOL WriteFloat(INT lpBaseAddress, float lpBuffer);
	// д˫����
	BOOL WriteDouble(INT lpBaseAddress, double lpBuffer);
	// д�ֽ�����
	BOOL WriteBytes(INT lpBaseAddress, std::vector<int> bytes);
	// д�ַ���
	BOOL WriteString(INT lpBaseAddress, LPCWSTR lpBuffer);
	void UnHookLdrInitializeThunk();
	LPVOID AllocMemory(int index, size_t size);
	void FreeAllMemory();
	HANDLE CreateThread(int StartAddress, int Paramter);
};

