#include <iostream>
#include <sstream>
#include <cstdlib>
#include "ConnectorIPC.h"
#include "ArgUtils.h"

using namespace std;

ConnectorIPC::ConnectorIPC()
{
    hProcess = NULL;
    hwndProcess = NULL;
    needClose = false;
}

void ConnectorIPC::syncFromArgs(int argc, char *argv[]) {
    const char* hwndArg = FindArg((const char**)argv, argc, CONNECTOR_IPC_HWND_ARG);
    const char* hwndStr = FindNextArg((const char**)argv, argc, CONNECTOR_IPC_HWND_ARG);

    if(hwndArg == NULL || hwndStr == NULL) {
        cout << "Warning : HWND non trouve dans la liste de parametres de l'application" << endl;
    } else {
#ifdef DEBUG
        cout << "DEBUG : HWND trouve : " << hwndStr << endl;
#endif
        HWND toSync = 0;
        /* No risk about truncating HWND by getting it in an integer because windows
         * only use the lower part of the pointer to store HWND in x64 */
        int tmp = atoi(hwndStr);
        toSync = (HWND) tmp;
        sync(toSync);
    }
}

void ConnectorIPC::newInstance(std::string& pathToExe, std::string& args,  bool deathResponsible) {

    string finalArgs;
    stringstream ss;
    ss << args;
    char currentDirectory[2048];

    if(hwndProcess != NULL) {
        /* adding HWND param*/
        unsigned long long decimalAddress = (unsigned long long)hwndProcess;
        ss << " " << CONNECTOR_IPC_HWND_ARG << " " << decimalAddress;
#ifdef DEBUG
        cout << "DEBUG : HWND passe en parametres : " << decimalAddress << endl;
#endif
    }

    finalArgs = ss.str();

    SHELLEXECUTEINFOA shellInfo;
    shellInfo.cbSize = sizeof(SHELLEXECUTEINFOA);
    shellInfo.fMask = SEE_MASK_NOCLOSEPROCESS;
    shellInfo.hwnd = NULL;
    shellInfo.lpVerb = "open";
    shellInfo.lpFile = pathToExe.c_str();
    shellInfo.lpParameters = finalArgs.c_str();

    size_t lSlashPos = pathToExe.find_last_of('\\');
    if(lSlashPos != string::npos) {
        pathToExe.copy(currentDirectory, lSlashPos+1);
        shellInfo.lpDirectory = currentDirectory;
#ifdef DEBUG
        cout << "current directory : " << currentDirectory << endl;
#endif
    } else {
        shellInfo.lpDirectory = NULL;
    }
    shellInfo.nShow = SW_SHOWNORMAL;
    shellInfo.lpIDList = NULL;
    shellInfo.lpClass = NULL;
    shellInfo.hkeyClass = NULL;
    shellInfo.dwHotKey = 0;


    ShellExecuteExA(&shellInfo);

    if(deathResponsible) {
        deathResponsability(GetProcessId(shellInfo.hProcess));
    }

    identify(shellInfo.hProcess);
}

HANDLE ConnectorIPC::getHandle() {
    return hProcess;
}

void ConnectorIPC::sync(HWND hWnd) {
    hwndProcess = hWnd;
    if(hWnd == NULL) {
        cout << "HWND invalide : " << hWnd << endl;
    } else {
        close();
        DWORD pid;
        GetWindowThreadProcessId(hWnd, &pid);
        identify(pid);
    }
}

HWND ConnectorIPC::getHwnd() {
    return hwndProcess;
}

void ConnectorIPC::identify(DWORD pid) {
    identify(OpenProcess(PROCESS_ALL_ACCESS, 0, pid));
    needClose = true;
}

void ConnectorIPC::identify(HANDLE hProcess) {
    this->hProcess = hProcess;
    if(hProcess == NULL) {
        cout << "HANDLE invalide : " << hProcess << endl;
    }
}

void ConnectorIPC::deathResponsability(DWORD pidChild) {
    childs.push_front(pidChild);
#ifdef DEBUG
        cout << "DEBUG : Adding " << pidChild << " to death processes"<< endl;
#endif
}

void ConnectorIPC::close() {
    if(needClose) {
        CloseHandle(hProcess);
    }
    needClose = false;
}

ConnectorIPC::~ConnectorIPC(){
    for(list<DWORD>::iterator it = childs.begin(); it != childs.end(); it++) {
#ifdef DEBUG
        cout << "DEBUG : Terminating " << (*it) << endl;
#endif
        HANDLE curH = OpenProcess(PROCESS_TERMINATE, 0, (*it));
        TerminateProcess(curH, 0);
        CloseHandle(curH);
    }
    close();
}

