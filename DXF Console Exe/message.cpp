#include "pch.h"
#include "message.h"
#include "utils.h"


HHOOK g_hHook;
DWORD g_dwMainThreadId;

VOID ThreadMessage(
	UINT message,
	WPARAM wParam,
	LPARAM lParam
)
{
	��ɫ��ӡ("message %d", message);
	��ɫ��ӡ("wParam %d", wParam);
	��ɫ��ӡ("lParam %d", lParam);
}

LRESULT CALLBACK Keypress(int nCode, WPARAM wParam, LPARAM lParam)
{
	CWPSTRUCT* p = (CWPSTRUCT*)lParam;
	if (nCode == HC_ACTION)
	{
		switch (wParam) //wParam������ϢID
		{
			// ������Ϣ
		case WM_KEYDOWN:
		{
			switch (p->lParam)
			{
			case VK_HOME:
				PostThreadMessage(g_dwMainThreadId, 10024, 0, 0);
				//CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)Thread, (LPVOID)this, NULL, NULL);
				break;
			case VK_END:
				ProcessExit();//�����˳�
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
	if (dwCtrlType == CTRL_CLOSE_EVENT)//�˳��¼�
	{
		//OutputDebugString("111111111111233333333333333");
		//UnhookWindowsHookEx(g_hHook);
		//_Process.Clear();
		//��ԭ����();
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
		��ɫ��ӡ("hook failure!");
}

VOID UnsetGlobalKeyboardHook()
{
	//SetConsoleCtrlHandler(ConsoleCtrlhandler, FALSE);
}

void ProcessExit()
{
	OutputDebugString("111111111111233333333333333");
	RestoreProtectFile();
	_Process.Clear();
	UnhookWindowsHookEx(g_hHook);
	exit(0);
}