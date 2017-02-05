#ifndef UNISENDERIPC_H
#define UNISENDERIPC_H

#include "ConnectorIPC.h"
#include "AbstractSenderIPC.h"

class UniSenderIPC : public ConnectorIPC, public AbstractSenderIPC
{
public:
    UniSenderIPC();

    virtual void send(std::string& messageName, WPARAM wParam, LPARAM lParam);

    virtual ~UniSenderIPC();

};

#endif // UNISENDERIPC_H
