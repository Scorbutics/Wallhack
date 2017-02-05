#include <windows.h>
#include <stdio.h>
#include <string.h>
#include <Psapi.h>

#ifndef DLLEXPORT
#define DLLEXPORT __declspec(dllimport)
#endif

#include "HookStart.h"

DWORD WINAPI start(HWND target)
{
    /* Une seul des fonctions selon la plateforme compilée sera exécutée */
#ifndef __WIN64
    StartHooks(target, "GlobalHooksx86.dll", 4, "MouseLLHookStart", "KeyboardLLHookStart", "GetMsgHookStart", "ShellHookStart");
#else
    StartHooks(target, "GlobalHooks.dll", 4, "MouseLLHookStart", "KeyboardLLHookStart", "GetMsgHookStart", "ShellHookStart");
#endif
    return 1;
}
