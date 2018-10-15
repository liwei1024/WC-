#pragma once

VOID ThreadMessage(UINT message, WPARAM wParam, LPARAM lParam);

VOID SetGlobalKeyboardHook();

VOID UnsetGlobalKeyboardHook();

void ProcessExit();
