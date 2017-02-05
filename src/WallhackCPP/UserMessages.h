#ifndef GLOBALHOOKCALLBACKS_H
#define GLOBALHOOKCALLBACKS_H

#include <windows.h>
#include <unordered_map>

class UserMessages {

public:
    UserMessages& getInstance();
    ~UserMessages();
    UINT getMessage(std::string mess);

private:
    UserMessages();
    std::unordered_map<std::string, UINT> messages;
};

#endif
