#ifndef MESSAGESIPC_H
#define MESSAGESIPC_H

#include <unordered_map>
#include <windows.h>

class MessagesIPC
{
public:
    MessagesIPC();
    void sendMessage(HWND hwnd, std::string message, WPARAM wParam, LPARAM lParam);
    UINT getMessage(std::string key);

private:
    std::unordered_map<std::string, UINT> messages;
};

#endif // MESSAGESIPC_H
