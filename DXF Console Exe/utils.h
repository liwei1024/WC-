#pragma once
std::string FormatString(const char *lpcszFormat, ...);

std::wstring FormatWstring(const wchar_t *lpcwszFormat, ...);

bool ɾ������();

void ��ɫ��ӡ(const char *����, ...);

void ��ɫ��ӡ(const char *����, ...);

void ��ɫ��ӡ(const char *����, ...);

void ��ɫ��ӡ(const char *����, ...);

void ��ɫ��ӡ(const char *����, ...);

void ���ڳ�ʼ��();

bool EnableDebugPrivilege(bool bEnable);

int createRandom(int min, int max);
char * unicodeToAnsi(const wchar_t * wstr);
INT getTime();
VOID mouseDoubleClick(INT s = 50);
bool getKeyStatus(INT keyCode);
VOID keyDown(INT keyCode);
VOID keyUp(INT keyCode);
VOID doKeyPress(INT keyCode, INT s = 100);
bool Զ��CALL(int CALL_Address, bool async = true);

std::string PosToString(Pos pos);

int GetTime();

void ��ԭ��״̬();

bool VectorFindString(std::vector<std::string> list, std::string str);

void ErasePEInfo();

void ProtectFile();

void RestoreProtectFile();

std::string Utf8ToGbk(const char * utf8);

std::string CSringToString(CString ��ת���ı�);

std::string IntToHex(int Value, int n);

INT ��ԭ��ַ(std::string �ı���ַ);

BYTE * VectorToBYTE(std::vector<int> Asmcode);

std::vector<int> IntToBytes(int a, int len);

std::vector<int> BytesToVectorInt(byte * b, size_t len);

void ExecCALL(LPCVOID Call, size_t nargs = 0, ...);



