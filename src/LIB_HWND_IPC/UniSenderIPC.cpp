#include "UniSenderIPC.h"

using namespace std;

UniSenderIPC::UniSenderIPC()
{
}

void UniSenderIPC::send(std::string& messageName, WPARAM wParam, LPARAM lParam) {
    if(listeners.find(messageName) == listeners.end()) {
        listeners[messageName] = RegisterWindowMessageA(messageName.c_str());
    }
    if(getHwnd() == NULL) {
        cout << "Erreur : connecteur non synchronise avec un HWND. Impossible d'envoyer le message " << messageName << endl;
    } else {
        SendMessageA(getHwnd(), listeners[messageName], wParam, lParam);
    }
}

UniSenderIPC::~UniSenderIPC() {
}
