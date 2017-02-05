#include <iostream>
#include <windows.h>
#include <sstream>

#include "start.h"
#include "ArgUtils.h"
#include "UniReceiverIPC.h"
#include "ConnectorIPC.h"
#include "PathExeUtils.h"

#include "MessagesDefine.h"
#include "WindowsCallback.h"

#define DLLEXPORT __declspec(dllimport)
#include "ShellHook.h"
#include "GetMsgHook.h"
#include "KeyboardLLHook.h"
#include "MouseLLHook.h"

using namespace std;

int main(int argc, char* argv[])
{
    char path[2048] = {'\0'};
    GetCurrentDirectoryName(path, 2048);

    UniReceiverIPC msgReceiver;
#ifdef _WIN64
    std::string msgStr = std::string(path) + "\\..\\WallhackGUI.exe";
#else
    std::string msgStr = std::string(path) + "\\WallhackGUI.exe";
#endif

    std::string args = "-bits 32 ";
    HANDLE pHookStarter = NULL;
    #ifdef _WIN64
    args = "-bits 64 ";
    #endif

    msgReceiver.addListener(MESSAGE_HOOK_WINDOW_GETMSG, GetMsgProc);
    msgReceiver.addListener(MESSAGE_HOOK_WINDOW_GETMSG_PARAMS, GetMsgParamsProc);
    msgReceiver.addListener(MESSAGE_HOOK_WINDOW_KEYBOARDLL, ManageKeyPress);
    msgReceiver.addListener(MESSAGE_HOOK_WINDOW_MOUSELL, ManageMouseWheel);
    msgReceiver.addListener(MESSAGE_HOOK_WINDOW_SHELL_WINDOWCREATED, WindowCreatedProc);
    msgReceiver.addListener(MESSAGE_WALLHACKGUI_DEFAULT_TRANSPARENCY, DefaultTransparencyProc);
    msgReceiver.addListener(MESSAGE_WALLHACKGUI_SHORTCUT, ShortcutProc);

    /* Si on est le processus principal, on lance un processus fils. Le processus
     * fils à lancer se déclenche uniquement en version 64 bits  */
#ifdef _WIN64
    string w64msgStr = string(path) + "\\..\\HookStarter.exe";
    msgReceiver.newInstance(w64msgStr, args, true);

    /* récupération du handle de processus lancé */
    pHookStarter = msgReceiver.getHandle();
#endif


    /* Démarrage des hooks */
    start(msgReceiver.getHwnd());

    if(pHookStarter != NULL) {
        stringstream ss;
        ss << args << "-HookStarterPID " << GetProcessId(pHookStarter);
        args = ss.str();
    }

    msgReceiver.newInstance(msgStr, args, true);

    msgReceiver.listenMessages();

    return 0;
}

