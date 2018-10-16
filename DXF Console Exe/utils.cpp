#include "pch.h"
#include "utils.h"
#include <ctime>
using namespace std;

HWND s_hwnd = NULL;

string FormatString(const char *lpcszFormat, ...)
{
	char *pszStr = NULL;
	if (NULL != lpcszFormat)
	{
		va_list marker = NULL;
		va_start(marker, lpcszFormat); //��ʼ����������
		size_t nLength = _vscprintf(lpcszFormat, marker) + 1; //��ȡ��ʽ���ַ�������
		pszStr = new char[nLength];
		memset(pszStr, '\0', nLength);
		_vsnprintf_s(pszStr, nLength, nLength, lpcszFormat, marker);
		va_end(marker); //���ñ�������
	}
	std::string strResult(pszStr);
	delete[]pszStr;
	return strResult;
}

wstring FormatWstring(const wchar_t *lpcwszFormat, ...)
{
	wchar_t *pszStr = NULL;
	if (NULL != lpcwszFormat)
	{
		va_list marker = NULL;
		va_start(marker, lpcwszFormat); //��ʼ����������
		size_t nLength = _vscwprintf(lpcwszFormat, marker) + 1; //��ȡ��ʽ���ַ�������
		pszStr = new wchar_t[nLength];
		memset(pszStr, L'\0', nLength);
		_vsnwprintf_s(pszStr, nLength, nLength, lpcwszFormat, marker);
		va_end(marker); //���ñ�������
	}
	std::wstring strResult(pszStr);
	delete[]pszStr;
	return strResult;
}



bool ɾ������()
{
	VMProtectBeginUltra("ɾ������");
	bool result = true;
	char FileName[MAX_PATH];
	memset(FileName, 0, MAX_PATH);
	//��ȡ�ļ�·��
	GetModuleFileName(NULL, FileName, MAX_PATH);
	char *NewFileName;
	NewFileName = new char[MAX_PATH];
	memset(NewFileName, 0, MAX_PATH);
	//�����ļ�����
	SetFileAttributes(NewFileName, FILE_ATTRIBUTE_NORMAL);
	//����ֱ��ɾ��
	if (DeleteFile(FileName))//��ֱ��ɾ�����
	{
		delete[] NewFileName;
		return false;
	}
	//����APIһ�������ن���
	wsprintf(NewFileName, VMProtectDecryptStringA("C:\\Windows\\%C\0"), FileName[0]);
	CreateDirectory(NewFileName, NULL);
	SetFileAttributes(NewFileName, FILE_ATTRIBUTE_HIDDEN);
	wsprintf(NewFileName, VMProtectDecryptStringA("C:\\Windows ����������\0"), FileName[0], GetTickCount());
	SetFileAttributes(NewFileName, FILE_ATTRIBUTE_NORMAL);
	DeleteFile(NewFileName);
	if (!MoveFileEx(FileName, NewFileName, MOVEFILE_REPLACE_EXISTING))
	{
		delete[] NewFileName;
		//printf("ɾ������ʧ�� Error Code\n");
		return false;//�����˾ͷ���
	}
	MoveFileEx(NewFileName, NULL, MOVEFILE_DELAY_UNTIL_REBOOT);
	SetFileAttributes(NewFileName, FILE_ATTRIBUTE_HIDDEN | FILE_ATTRIBUTE_SYSTEM);
	delete[] NewFileName;
	if (result == false)
	{
		printf(VMProtectDecryptStringA("ɾ������ʧ�� Error Code\n"));
		system("pause");
		exit(0);
	}
	VMProtectEnd();
	return result;
}

void ��ɫ��ӡ(const char *����, ...)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_BLUE);//������ɫ����ɫ���
	va_list argList;
	char buffer[0x1024];
	va_start(argList, ����);
	vsprintf_s(buffer, ����, argList);
	printf("%s\n", buffer);
	va_end(argList);
}

void ��ɫ��ӡ(const char *����, ...)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN);//���ú�ɫ����ɫ���

	va_list argList;
	char buffer[0x1024];
	va_start(argList, ����);
	vsprintf_s(buffer, ����, argList);
	printf("%s\n", buffer);
	va_end(argList);
}

void ��ɫ��ӡ(const char *����, ...)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE);//���ú�ɫ����ɫ���
	va_list argList;
	char buffer[0x1024];
	va_start(argList, ����);
	vsprintf_s(buffer, ����, argList);
	printf("%s\n", buffer);
	va_end(argList);
}

void ��ɫ��ӡ(const char *����, ...)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);//���ú�ɫ
	va_list argList;
	char buffer[0x1024];
	va_start(argList, ����);
	vsprintf_s(buffer, ����, argList);
	printf("%s\n", buffer);
	va_end(argList);
}

void ��ɫ��ӡ(const char *����, ...)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN);//������ɫ
	va_list argList;
	char buffer[0x1024];
	va_start(argList, ����);
	vsprintf_s(buffer, ����, argList);
	printf("%s\n", buffer);
	va_end(argList);
}

void ���ڳ�ʼ��()
{
	RECT rect;
	int cx, cy;
	int width, height;
	cx = GetSystemMetrics(SM_CXFULLSCREEN);
	cy = GetSystemMetrics(SM_CYFULLSCREEN);
	s_hwnd = GetConsoleWindow();
	GetWindowRect(s_hwnd, &rect);
	MoveWindow(s_hwnd, 0, 0, 800, 600, TRUE);
	GetWindowRect(s_hwnd, &rect);
	width = (rect.right - rect.left);
	height = (rect.bottom - rect.top);
	MoveWindow(s_hwnd, cx - width, cy - height, width, height, TRUE);

	SetConsoleTitle("");
	//SetLayeredWindowAttributes(hwnd, 0, 200, 3);//͸��������
}

bool EnableDebugPrivilege(bool bEnable)
{
	VMProtectBeginUltra("EnableDebugPrivilege");
	//Enabling the debug privilege allows the application to see 
	//information about service application
	BOOL fOK = false;     //Assume function fails
	HANDLE hToken;
	//Try to open this process's acess token
	if (OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES, &hToken))
	{
		//Attempt to modify the "Debug" privilege
		TOKEN_PRIVILEGES tp;
		tp.PrivilegeCount = 1;
		LookupPrivilegeValue(NULL, SE_DEBUG_NAME, &tp.Privileges[0].Luid);
		tp.Privileges[0].Attributes = bEnable ? SE_PRIVILEGE_ENABLED : 0;
		AdjustTokenPrivileges(hToken, FALSE, &tp, sizeof(tp), NULL, NULL);
		fOK = (GetLastError() == ERROR_SUCCESS);
		CloseHandle(hToken);
	}
	VMProtectEnd();
	return fOK;
}

int createRandom(int min, int max)
{
	int ����� = 0;
	if (max > min) {
		srand((unsigned)time(NULL));
		����� = (rand() % (min - max + 1) + max);
	}
	else {
		srand((unsigned)time(NULL));
		����� = (rand() % (max - min + 1) + min);
	}
	return �����;
}

char* unicodeToAnsi(const wchar_t * wstr)
{
	if (!wstr)
		return NULL;
	INT strlen = ::WideCharToMultiByte(CP_ACP, NULL, wstr, wcslen(wstr), NULL, 0, NULL, FALSE);
	char* str = new char[strlen + 1];
	::WideCharToMultiByte(CP_ACP, NULL, wstr, wcslen(wstr), str, strlen, NULL, FALSE);
	str[strlen] = '\0';
	return str;
}

// ��ȡʱ���
INT getTime()
{
	DWORD t_start, t_end;
	t_start = GetTickCount();//�Ӳ���ϵͳ������������elapsed���ĺ����������ķ���ֵ��DWORD��
	Sleep(3000);
	t_end = GetTickCount();
	return  t_end - t_start;
}

POINT getMouseCoord()
{
	POINT Coord;
	if (GetCursorPos(&Coord)) {
		printf("getMouseCoord Erro!\n");
	}
	return Coord;
}

BOOL setMouseCoord(INT x, INT y)
{
	BOOL result;
	result = SetCursorPos(x, y);
	if (result == FALSE) {
		printf("setMouseCoord Erro!\n");
	}
	return result;
}

VOID mouseClick(INT s)
{
	mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
	Sleep(s + createRandom(0, 10));
	mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
	Sleep(50 + createRandom(0, 10));
}

VOID mouseDoubleClick(INT s)
{
	mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
	Sleep(s + createRandom(0, 10));
	mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
	Sleep(50 + createRandom(0, 10));
	mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
	Sleep(s + createRandom(0, 10));
	mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
	Sleep(50 + createRandom(0, 10));
}

bool getKeyStatus(INT keyCode)
{
	if (GetKeyState(keyCode) < 0) {
		return TRUE;
	}
	return FALSE;
}

INT getSCan(INT keyCode)
{
	INT sCan = MapVirtualKey(keyCode, 0);
	if (
		keyCode == VK_LEFT ||
		keyCode == VK_RIGHT ||
		keyCode == VK_DOWN ||
		keyCode == VK_UP
		)
	{
		sCan += 0x80;
	}
	return sCan;
}

VOID keyDown(INT keyCode)
{
	if (getKeyStatus(keyCode) == FALSE) {
		keybd_event(keyCode, getSCan(keyCode), 0, 0);
		Sleep(100);
	}
}

VOID keyUp(INT keyCode)
{
	if (getKeyStatus(keyCode) == TRUE) {
		keybd_event(keyCode, getSCan(keyCode), KEYEVENTF_KEYUP, 0);
		Sleep(100);
	}
}

VOID doKeyPress(INT keyCode, INT s)
{
	keyDown(keyCode);
	//Sleep(s + createRandom(200, 300));
	keyUp(keyCode);
}

bool Զ��CALL(int CALL_Address, bool async)
{
	if (async)
	{
		return SendMessage(_Process.hWnd, 10024, CALL_Address, 0);
	}
	else {
		return PostMessage(_Process.hWnd, 10024, CALL_Address, 0);
	}
}

std::string PosToString(Pos pos)
{
	string str;
	str = std::to_string(pos.x) + "," + std::to_string(pos.y) + "," + std::to_string(pos.z);
	return str;
}


int GetTime()
{
	time_t tt = time(NULL);
	return (int)tt;
}

void ��ԭ��״̬()
{
	if (getKeyStatus(VK_NUMPAD1) == true)
	{
		keyUp(VK_NUMPAD1);
	}
	if (getKeyStatus(VK_NUMPAD3) == true)
	{
		keyUp(VK_NUMPAD3);
	}
	if (getKeyStatus(VK_NUMPAD2) == true)
	{
		keyUp(VK_NUMPAD2);
	}
	if (getKeyStatus(VK_NUMPAD5) == true)
	{
		keyUp(VK_NUMPAD5);
	}
}

bool VectorFindString(vector<string> list, string str)
{
	for (size_t i = 0; i < list.size(); i++)
	{
		if (list[i] == str)
		{
			return true;
		}
	}
	return false;
}

// ĨȥPEinfo
void ErasePEInfo()
{
	VMProtectBeginUltra("ErasePEInfo");
	HMODULE        hModule = NULL;
	DWORD        dwMemPro = NULL;
	hModule = GetModuleHandle(NULL);
	VirtualProtect((void*)hModule, 0x1000, PAGE_EXECUTE_READWRITE, &dwMemPro);
	memset((void*)hModule, 0, 0x1000);
	VirtualProtect((void*)hModule, 0x1000, dwMemPro, &dwMemPro);
	VMProtectEnd();
}

void ProtectFile()
{
	VMProtectBeginUltra("ProtectFile");
	char szFileFullPath[MAX_PATH];
	::GetModuleFileNameA(NULL, szFileFullPath, MAX_PATH);
	string s1 = VMProtectDecryptStringA("cacls ");
	string s2 = VMProtectDecryptStringA(szFileFullPath);
	string s3 = VMProtectDecryptStringA(" /e /p everyone:n");
	WinExec((s1 + s2 + s3).c_str(), SW_HIDE);
	//system(VMProtectDecryptStringA("cls"));
	VMProtectEnd();
}

void RestoreProtectFile()
{
	VMProtectBeginUltra("RestoreProtectFile");
	char szFileFullPath[MAX_PATH];
	::GetModuleFileNameA(NULL, szFileFullPath, MAX_PATH);
	string s1 = VMProtectDecryptStringA("cacls ");
	string s2 = VMProtectDecryptStringA(szFileFullPath);
	string s3 = VMProtectDecryptStringA(" /e /p everyone:f");
	WinExec((s1 + s2 + s3).c_str(), SW_HIDE);
	//system(VMProtectDecryptStringA("cls"));
	VMProtectEnd();
}

void ExecCALL(LPCVOID Call, size_t nargs, ...)
{
	VMProtectBeginUltra("ExecCALL");
	// �������
	DWORD *Params = new DWORD[nargs];
	size_t CallSize = 0;
	size_t ParamsSize = nargs * 4;
	int CallAddress = NULL;
	int ParamsAddress = NULL;
	// ����Զ���̲߳���
	if (nargs > 0)
	{
		va_list argList;
		va_start(argList, nargs);
		for (size_t i = 0; i < nargs; i++)
			Params[i] = va_arg(argList, int);
		va_end(argList);
		// �����ڴ�ռ�
		ParamsAddress = (int)_Process.AllocMemory((int)Params, ParamsSize);
		// д�����
		_Process.WriteMemory(ParamsAddress, Params, ParamsSize);
	}
	//printf("Call %x\n", (int)Call);
	// ��ȡԶ��call��С
	while (true) {
		if (
			*(byte*)((DWORD)Call + (CallSize + 0)) == 0xcc &&
			*(byte*)((DWORD)Call + (CallSize + 1)) == 0xcc &&
			*(byte*)((DWORD)Call + (CallSize + 2)) == 0xcc &&
			*(byte*)((DWORD)Call + (CallSize + 3)) == 0xcc &&
			*(byte*)((DWORD)Call + (CallSize + 4)) == 0xcc)
		{
			break;
		}
		CallSize++;
	}
	CallAddress = (int)_Process.AllocMemory((int)Call, CallSize);
	// д�뺯��
	_Process.WriteMemory(CallAddress, Call, CallSize);
	//printf("CallAddress %x,CallSize %d\n", CallAddress,CallSize);
	
	// ����Զ���߳�
	HANDLE hThread = _Process.CreateThread(CallAddress, ParamsAddress);

	//�ȴ��߳̽���
	WaitForSingleObject(hThread, 0xFF);
	// ������
	//VirtualFreeEx(hProcess, CodeAddr, sizeof(Code), MEM_DECOMMIT);
	CloseHandle(hThread);
	delete[]Params;
	VMProtectEnd();
}

std::string Utf8ToGbk(const char* utf8)
{
	int len = MultiByteToWideChar(CP_UTF8, 0, utf8, -1, NULL, 0);
	wchar_t* wstr = new wchar_t[len + 1];
	memset(wstr, 0, len + 1);
	MultiByteToWideChar(CP_UTF8, 0, utf8, -1, wstr, len);
	len = WideCharToMultiByte(CP_ACP, 0, wstr, -1, NULL, 0, NULL, NULL);
	char* str = new char[len + 1];
	memset(str, 0, len + 1);
	WideCharToMultiByte(CP_ACP, 0, wstr, -1, str, len, NULL, NULL);
	if (wstr) delete[] wstr;
	return str;
}

std::string CSringToString(CString ��ת���ı�)
{
	CStringA stra(��ת���ı�.GetBuffer(0));
	��ת���ı�.ReleaseBuffer();
	std::string stdStr = stra.GetBuffer(0);
	stra.ReleaseBuffer();
	return stdStr;
}

std::string IntToHex(int Value, int n)
{
	CString str;
	str.Format(_T("0000000%x"), Value);
	string tmp1 = CSringToString(str);
	tmp1 = tmp1.substr(tmp1.length() - n, n);
	string tmp2;
	for (unsigned int i = 0; i < tmp1.length() / 2; i++)
	{
		tmp2 = tmp2 + tmp1.substr(tmp1.length() - 2 - 2 * i, 2);
	}
	return tmp2;
}

INT ��ԭ��ַ(std::string �ı���ַ)
{
	int ת����ַ = 0;
	char ��ʱ����[256] = { 0 };
	strcpy_s(��ʱ����, �ı���ַ.c_str());
	sscanf_s(��ʱ����, "%x", &ת����ַ);
	return ת����ַ;
}

BYTE* VectorToBYTE(std::vector<int> Asmcode)
{
	byte* ��ʱ���� = new byte[Asmcode.size()];
	int i = 0;
	for (auto it = std::begin(Asmcode); it != std::end(Asmcode); ++it)
	{
		��ʱ����[i++] = *it;
	}
	return ��ʱ����;
}

std::vector<int> IntToBytes(int a, int len)
{
	string s = IntToHex(a, len);
	int ���� = s.length();
	if (���� % 2 != 0)
	{
		���� = ���� + 1;
	}
	vector<int> ���(���� / 2, 0);
	for (int i = 0; i < ���� / 2; i++)
	{
		���[i] = ��ԭ��ַ(s.substr(i * 2, 2));
	}
	return ���;
}

vector<int> BytesToVectorInt(byte * b,size_t len)
{
	vector<int> v;
	for (size_t i = 0; i < len; i++)
	{
		v.insert(v.end(),b[i]);
	}
	return v;
}