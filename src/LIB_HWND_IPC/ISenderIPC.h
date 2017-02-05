#ifndef ISENDERIPC_H
#define ISENDERIPC_H

#include <windows.h>
#include <iostream>

class ISenderIPC {

public:
    ISenderIPC() {
    }

    virtual void send(std::string& messageName, WPARAM wParam, LPARAM lParam) = 0;

    virtual ~ISenderIPC() {
    }

};

#endif // SENDERIPC_H
