#ifndef HWNDSTACK_H
#define HWNDSTACK_H

#include <windows.h>

typedef struct _HWNDStack {
    HWND hwnd;
    int opacity;
    struct _HWNDStack* next;
} HWNDStack;



HWNDStack* CreateWindowTransparencyElement(HWND hwnd, int opacity);
HWNDStack* PushWindowTransparencyStack(HWNDStack** stack, HWND hwnd, int opacity);
HWNDStack* PopWindowTransparencyStack(HWNDStack** stack);
void ClearWindowTransparencyStack(HWNDStack ** stack);

#endif // HWNDSTACK_H
