// DXF Console Exe.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include "Calls.h"
#include "utils.h"
#include "message.h"

Process _Process;

int main()
{
	VMProtectBeginUltra("main");

	ProtectFile();

	窗口初始化();

	EnableDebugPrivilege(true);

	//ErasePEInfo();

	EnableMenuItem(GetSystemMenu(GetConsoleWindow(), FALSE), SC_CLOSE, MF_GRAYED);

	SetGlobalKeyboardHook();

	_Process.Run();

	MSG msg;//消息指针
	while (GetMessage(&msg, NULL, 0, 0))
	{
		ThreadMessage(msg.message, msg.wParam, msg.lParam);//线程消息处理
		TranslateMessage(&msg);//等待信号
		DispatchMessage(&msg);//处理信号
	}
	VMProtectEnd();
	return 0;
}


