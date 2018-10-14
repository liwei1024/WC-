#pragma once
std::string FormatString(const char *lpcszFormat, ...);

std::wstring FormatWstring(const wchar_t *lpcwszFormat, ...);

bool 删除自身();

void 青色打印(const char *内容, ...);

void 黄色打印(const char *内容, ...);

void 粉色打印(const char *内容, ...);

void 红色打印(const char *内容, ...);

void 绿色打印(const char *内容, ...);

void 窗口初始化();

bool EnableDebugPrivilege(bool bEnable);

int createRandom(int min, int max);
char * unicodeToAnsi(const wchar_t * wstr);
INT getTime();
VOID mouseDoubleClick(INT s = 50);
bool getKeyStatus(INT keyCode);
VOID keyDown(INT keyCode);
VOID keyUp(INT keyCode);
VOID doKeyPress(INT keyCode, INT s = 100);
bool 远程CALL(int CALL_Address, bool async = true);

std::string PosToString(Pos pos);

int GetTime();

void 还原键状态();

bool VectorFindString(std::vector<std::string> list, std::string str);

