#ifndef WINDOWSCALLBACK_H
#define WINDOWSCALLBACK_H

#include <windows.h>

void GetMsgParamsProc(WPARAM wParam, LPARAM lParam);
void ManageKeyPress(WPARAM wParam, LPARAM lParam);
void ManageMouseWheel(WPARAM wParam, LPARAM lParam);
void WindowCreatedProc(WPARAM wParam, LPARAM lParam);
void DefaultTransparencyProc(WPARAM wParam, LPARAM lParam);
void GetMsgProc(WPARAM wParam, LPARAM lParam);
void GetMsgParamsProc(WPARAM wParam, LPARAM lParam);
void ShortcutProc(WPARAM wParam, LPARAM lParam);

#endif // WINDOWSCALLBACK_H
