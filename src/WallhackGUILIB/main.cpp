#include <stdio.h>
#include <windows.h>
#include <QApplication>
#include "MainWindow.h"
#include "ArgUtils.h"
#include "PathExeUtils.h"
#include "ProcessUtils.h"

#include "UniSenderIPC.h"



int main(int argc, char* argv[])
{
    QApplication a(argc, argv);

    UniSenderIPC msgSender;
    msgSender.syncFromArgs(argc, argv);
    if(msgSender.getHwnd() == NULL) {
        std::cout << "Erreur : ce programme a pour vocation d'etre lance par Wallhack ou Wallhack.x86" << std::endl;
        return 0;
    }
    msgSender.deathResponsability(GetProcessId(msgSender.getHandle()));
    const char* hHookStarterPid = FindNextArg((const char**)argv, argc, "-HookStarterPID");
    const char* bitsPlateformStart = FindNextArg((const char**)argv, argc, "-bits");
    if(hHookStarterPid != NULL) {
        msgSender.deathResponsability(atoi(hHookStarterPid));
    }

    MainWindow w(NULL, &msgSender);
    if(bitsPlateformStart != NULL) {
        if(atoi(bitsPlateformStart) == 64) {
            w.setWindowTitle(w.windowTitle() + " (x64)");
        } else {
            w.setWindowTitle(w.windowTitle() + " (x86)");
        }
    }

    w.show();

    int result = a.exec();
    return  result;
}

