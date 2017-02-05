#ifndef UNIRECEIVERIPC_H
#define UNIRECEIVERIPC_H

#include <windows.h>
#include <unordered_map>
#include <memory>

#include "ConnectorIPC.h"
#include "AbstractReceiverIPC.h"

class UniReceiverIPC : public ConnectorIPC, public AbstractReceiverIPC
{
public:
    static std::unordered_map<unsigned int, IReceiverIPC*>* getInstances(HWND hwnd);
    UniReceiverIPC();


    virtual void sync(HWND hWnd);
    virtual void addListener(std::string messageName, CallbackProc proc);
    virtual void wndProc(UINT msg, WPARAM wParam, LPARAM lParam);
    virtual void listenMessages();

    virtual ~UniReceiverIPC();

private:
    static std::unordered_map<HWND, std::unordered_map<unsigned int, IReceiverIPC*>> pool;
    static unsigned int gIndexPool;
    unsigned int indexPool;

    HWND createHwnd();

};

#endif // UNIRECEIVERIPC_H
