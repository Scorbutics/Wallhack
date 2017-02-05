#ifndef ABSTRACTSENDERIPC_H
#define ABSTRACTSENDERIPC_H

#include <unordered_map>
#include "CallbackProc.h"
#include "ISenderIPC.h"


class AbstractSenderIPC : public ISenderIPC
{
public:
    AbstractSenderIPC() {
    }

    virtual ~AbstractSenderIPC() {
    }

protected:
    std::unordered_map<std::string, UINT> listeners;
};

#endif // ABSTRACTSENDERIPC_H
