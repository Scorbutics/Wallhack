#include <stdio.h>

#include "MessagesIPC.h"

using namespace std;

MessagesIPC::MessagesIPC()
{


}

UINT MessagesIPC::getMessage(std::string key)
{
    return (messages.find(key) != messages.end() ? messages[key] : 0);
}

void MessagesIPC::sendMessage(HWND hwnd, string message, WPARAM wParam, LPARAM lParam)
{
    SendMessageA(hwnd, getMessage(message), wParam, lParam);
}
