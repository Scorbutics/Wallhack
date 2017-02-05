#include <cstdlib>
#include "HWNDStack.h"

HWNDStack* hwndStack = NULL;
int stackLength = 0;

HWNDStack* CreateWindowTransparencyElement(HWND hwnd, int opacity)
{
    HWNDStack* result = (HWNDStack*) calloc(1, sizeof(HWNDStack));
    result->hwnd = hwnd;
    result->next = NULL;
    result->opacity = opacity;
    return result;
}

HWNDStack* PushWindowTransparencyStack(HWNDStack** stack, HWND hwnd, int opacity)
{
     HWNDStack* el = CreateWindowTransparencyElement(hwnd, opacity);
     el->next = (*stack) ;
     *stack = el;
     stackLength++;
    return (*stack);
}

HWNDStack* PopWindowTransparencyStack(HWNDStack** stack)
{
    if(*stack == NULL)
    {
        return NULL;
    }

    HWNDStack* nextEl = (*stack)->next;
    free(*stack);
    *stack = nextEl;
    return *stack;
}

void ClearWindowTransparencyStack(HWNDStack ** stack)
{
    while(PopWindowTransparencyStack(stack));
}
