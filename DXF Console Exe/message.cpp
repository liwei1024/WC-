#include "pch.h"
#include "message.h"
#include "utils.h"
#include "Game.h"
#include "Map.h"
#include "SendPacket.h"


HHOOK g_hHook;
DWORD g_dwMainThreadId;

VOID ThreadMessage(
	UINT message,
	WPARAM wParam,
	LPARAM lParam
)
{
	青色打印("message %d", message);
	青色打印("wParam %d", wParam);
	青色打印("lParam %d", lParam);
}

void test()
{
	/*Map _Map;
	_Map.OutputMapObjectsInfo();*/

	ExecCALL(Asm_选择角色,1,1);



	//_Game.OutputTaskInfo(0);
}

LRESULT CALLBACK Keypress(int nCode, WPARAM wParam, LPARAM lParam)
{
	CWPSTRUCT* p = (CWPSTRUCT*)lParam;
	if (nCode == HC_ACTION)
	{
		switch (wParam) //wParam中是消息ID
		{
			// 键盘消息
			case WM_KEYDOWN:
			{
				switch (p->lParam)
				{
				case VK_HOME:
					//PostThreadMessage(g_dwMainThreadId, 10024, 0, 0);
					//CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)test, (LPVOID)this, NULL, NULL);
					//Game().OutputMapObjectsInfo();
					//CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)test, NULL, NULL, NULL);
					//青色打印("当前游戏状态 %d", _Process.ReadInteger(__游戏状态));
					//AfxBeginThread();
					_beginthreadex(NULL, NULL, (_beginthreadex_proc_type)test, NULL, NULL, NULL);
					//ErasePEInfo();
					break;
				case VK_END:
					ProcessExit();//进程退出
					break;
				default:
					break;
				}
			}
		}
	}
	return CallNextHookEx(g_hHook, nCode, wParam, lParam);
}

BOOL WINAPI ConsoleCtrlhandler(DWORD dwCtrlType)
{
	if (dwCtrlType == CTRL_CLOSE_EVENT)//退出事件
	{
		//OutputDebugString("111111111111233333333333333");
		//UnhookWindowsHookEx(g_hHook);
		//_Process.Clear();
		//还原保护();
		//PostThreadMessage(g_dwMainThreadId, WM_QUIT, 0, 0);
	}
	return TRUE;
}

VOID SetGlobalKeyboardHook()
{
	g_dwMainThreadId = GetCurrentThreadId();
	//SetConsoleCtrlHandler((PHANDLER_ROUTINE)ConsoleCtrlhandler, TRUE);
	g_hHook = SetWindowsHookEx(WH_KEYBOARD_LL, Keypress, GetModuleHandle(NULL), NULL);
	if (g_hHook == NULL)
		红色打印("hook failure!");
}

VOID UnsetGlobalKeyboardHook()
{
	//SetConsoleCtrlHandler(ConsoleCtrlhandler, FALSE);
}

void ProcessExit()
{
	//OutputDebugString("111111111111233333333333333");
	RestoreProtectFile();
	_Process.Clear();
	UnhookWindowsHookEx(g_hHook);
	exit(0);
}