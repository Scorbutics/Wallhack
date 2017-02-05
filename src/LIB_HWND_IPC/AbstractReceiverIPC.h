#ifndef ABSTRACTRECEIVERIPC_H
#define ABSTRACTRECEIVERIPC_H

#include <unordered_map>
#include "IReceiverIPC.h"

class AbstractReceiverIPC : public IReceiverIPC
{
public:
    AbstractReceiverIPC() {
    }

    virtual ~AbstractReceiverIPC() {
    }

protected:
    std::unordered_map<UINT, CallbackProc> listeners;
};

#endif // ABSTRACTRECEIVERIPC_H
