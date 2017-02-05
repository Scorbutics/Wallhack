#ifndef IRECEIVERIPC_H
#define IRECEIVERIPC_H

#include <windows.h>
#include <iostream>
#include "CallbackProc.h"


class IReceiverIPC {

public:
    IReceiverIPC() {
    }

    /* Ajoute une écoute (CallbackProc proc) pour un message donné (std::string& messageName) */
    virtual void addListener(std::string messageName, CallbackProc proc) = 0;

    /* Méthode de réception d'un message d'ID msg */
    virtual void wndProc(UINT msg, WPARAM wParam, LPARAM lParam) = 0;

    virtual void listenMessages() = 0;

    virtual ~IReceiverIPC(){
    }


};

#endif // RECEIVERIPC_H
