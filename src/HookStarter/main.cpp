#include <iostream>

#include "UniReceiverIPC.h"
#include "HookStart.h"

using namespace std;

int main(int argc, char* argv[]) {
#ifndef _WIN64
    UniReceiverIPC c;
    c.syncFromArgs(argc, argv);
    if(c.getHwnd() == NULL) {
        cout << "Erreur : HookStarter ne peut etre execute seul. Il doit etre lance par un programme utilisant la connexion inter-processus par HWND" << endl;
        return 0;
    }
    c.deathResponsability(GetProcessId(c.getHandle()));
    StartHooks(c.getHwnd(), "GlobalHooksx86.dll", 2, "GetMsgHookStart", "ShellHookStart");
    c.listenMessages();
    return 0;
#else
    cout << "Erreur : Ce programme est compile pour les plateformes x64. Il est impossible de demarrer les hooks. Fin du programme" << endl;
    return 0;
#endif
}

