#include <windows.h>
#include <stdio.h>
#include <string.h>

#include "HookStart.h"
#include "ProcessUtils.h"
#include "PathExeUtils.h"

extern HWND        secretModuleWindow;
HANDLE hChildProcess = NULL;

typedef void (*tpHookStart)  (HWND hMessageDestination, HWND hTargetHook);


void HookStart(HMODULE mod, const char* name, HWND hMessageDestination, HWND hTargetHook)
{
    tpHookStart hookStart = (tpHookStart)GetProcAddress(mod, name);
    if(hookStart)
    {
        printf("Hooking %s\n", name);
        hookStart(hMessageDestination, hTargetHook);
    }
    else
    {
        printf("Impossible de trouver la procedure %s\n", name);
    }

}



void StartHooks(HWND target, const char* gbHooks, unsigned int hooksNumber, ...)
{
    HMODULE gbHooks32;
    gbHooks32 = LoadLibraryA(gbHooks);

    if(gbHooks32)
    {

        va_list ap;
        va_start(ap, hooksNumber);

        for(unsigned int i = 0; i < hooksNumber; i++) {
                const char* hook = va_arg(ap, const char*);
                HookStart(gbHooks32, hook, target, NULL);
        }

    }
    else
    {
        printf("Error 0x%p\n", GetLastError());
    }

    FreeLibrary(gbHooks32);
}
