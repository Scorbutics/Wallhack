#ifndef HOOKSTART_H
#define HOOKSTART_H

#include <windows.h>

void StartHooks(HWND target, const char* gbHooks, unsigned int hooksNumber, ...);

#endif // HOOKSTART_H
