#include <windows.h>
#include <stdio.h>
#include <time.h>

#include "WindowsCallback.h"
#include "UserMessages.h"
#define DLLEXPORT __declspec(dllimport)
//#include "ShellHook.h"
//#include "GetMsgHook.h"
//#include "KeyboardLLHook.h"
//#include "MouseLLHook.h"
#include "HWNDStack.h"
#include "MessagesDefine.h"
#include "WindowUtils.h"
#include "UserMessages.h"


extern HWNDStack* hwndStack;
extern int stackLength;

int defaultOpacityPercent = 100;

UINT getmsgMessage = 0;
HWND getmsgHandle = NULL;

int keyDown = 0;
int key1 = VK_LWIN;
int key2 = VK_LMENU;

void ManageKeyPress(WPARAM wParam, LPARAM lParam)
{
    if(wParam == WM_SYSKEYDOWN || wParam == WM_KEYDOWN)
    {
        PKBDLLHOOKSTRUCT pKey = (PKBDLLHOOKSTRUCT) lParam;
        SHORT winKeyState = GetKeyState(key1);
        if((pKey->vkCode == key2) && (winKeyState == -127 || winKeyState == -128) )
        {
            if(!keyDown)
            {
                HWND currentTopW = GetForegroundWindow();
                printf("Windows + Alt Down \nHWND %p \n", currentTopW);
                keyDown = 1;

                if(currentTopW)
                {
                    PushWindowTransparencyStack(&hwndStack, currentTopW, 255);
                    SetWindowEXTTransparent(hwndStack, 1);
                }
            }
        }
    }
    else if(wParam == WM_SYSKEYUP || wParam == WM_KEYUP)
    {
        PKBDLLHOOKSTRUCT pKey = (PKBDLLHOOKSTRUCT) lParam;
        SHORT winKeyState = GetKeyState(key1);
        if((pKey->vkCode == key2) || (winKeyState == 0 || winKeyState == 1) )
        {
            if(keyDown)
            {
                printf("Windows + Alt Up\n");
                keyDown = 0;
                HWNDStack* it = hwndStack;
                for(it = hwndStack; it != NULL; it = it->next)
                {
                    if(it->hwnd != NULL)
                    {
                        SetWindowEXTTransparent(it, 0);
                    }
                }
                ClearWindowTransparencyStack(&hwndStack);
            }
        }
    }
}



void ManageMouseWheel(WPARAM wParam, LPARAM lParam)
{
    if(wParam == WM_MOUSEWHEEL && keyDown && hwndStack)
    {
        PMSLLHOOKSTRUCT mouseInfo = (MSLLHOOKSTRUCT*)lParam;
        short int wheelMovement = (short) ((mouseInfo->mouseData >> 16) & 0xffff);

        if(wheelMovement >= WHEEL_DELTA)
        {
            HWND currentTopW = GetNextVisibleWindow(hwndStack->hwnd);
            if(currentTopW)
            {
                //printf("MOUSE WHEEL UP delta %i\nHWND %p \n", wheelMovement, currentTopW);
                PushWindowTransparencyStack(&hwndStack, currentTopW, 255);
                SetWindowEXTTransparent(hwndStack, 1);
            }
        }
        else if( (wheelMovement) < 0 && hwndStack->next)
        {
            //printf("MOUSE WHEEL DOWN delta %i\nHWND %p \n", wheelMovement, hwndStack->hwnd);
            SetWindowEXTTransparent(hwndStack, 0);
            PopWindowTransparencyStack(&hwndStack);
        }
    }
}


void WindowCreatedProc(WPARAM wParam, LPARAM lParam) {
    SetWindowCustomMenu((HWND)wParam);
    SetWindowOpacity((HWND)wParam, defaultOpacityPercent);
}


void DefaultTransparencyProc(WPARAM wParam, LPARAM lParam) {
    defaultOpacityPercent = (int) wParam;
}

void ShortcutProc(WPARAM wParam, LPARAM lParam) {
    key1 = (int) wParam;
    key2 = (int) lParam;
}

void GetMsgProc(WPARAM wParam, LPARAM lParam) {
    getmsgHandle = (HWND) wParam;
    getmsgMessage = (UINT)lParam;
}


void GetMsgParamsProc(WPARAM wParam, LPARAM lParam) {
    if(getmsgMessage == WM_SYSCOMMAND)
    {
        int opacity = 10;
        switch(LOWORD((UINT)wParam))
        {
        case MENU_ITEM_OPACITY_100:
            opacity +=10;
        case MENU_ITEM_OPACITY_90:
            opacity +=10;
        case MENU_ITEM_OPACITY_80:
            opacity +=10;
        case MENU_ITEM_OPACITY_70:
            opacity +=10;
        case MENU_ITEM_OPACITY_60:
            opacity +=10;
        case MENU_ITEM_OPACITY_50:
            opacity +=10;
        case MENU_ITEM_OPACITY_40:
            opacity +=10;
        case MENU_ITEM_OPACITY_30:
            opacity +=10;
        case MENU_ITEM_OPACITY_20:
            opacity +=10;
        case MENU_ITEM_OPACITY_10:
            SetWindowOpacity(getmsgHandle, opacity);
            break;

        default:
            break;
        }


    }

    getmsgHandle = NULL;
    getmsgMessage = 0;
}


