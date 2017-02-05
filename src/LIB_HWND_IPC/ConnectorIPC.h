#ifndef CONNECTORIPC_H
#define CONNECTORIPC_H

#define CONNECTOR_IPC_HWND_ARG "-CONNECTOR_IPC_HWND"

#include <windows.h>
#include <iostream>
#include <list>

class ConnectorIPC
{

public:
    ConnectorIPC() ;

    /* Démarrage d'une instance d'un programme donné avec des paramètres ajoutés
     * en extra par le connecteur en vue d'être lus par un connecteur du programme cible */
    void newInstance(std::string& pathToExe, std::string& args, bool deathResponsability);

    /* Analyse des arguments de l'application pour effectuer une récupération
     * automatique d'un HWND d'une autre application en paramètres si possible
     * Par exemple, lorsque l'application courante a été lancée avec ConnectorIPC::newInstance */
    void syncFromArgs(int argc, char* argv[]);

    /* Synchronisation "classique" en fournissant explicitement le HWND */
    virtual void sync(HWND hWnd);

    /* Lors de la destruction du connecteur, tous les processus "fils" ajoutés par cette fonction
     * seront automatiquement tués*/
    void deathResponsability(DWORD pidChild);

    HANDLE getHandle();
    HWND getHwnd();

    virtual ~ConnectorIPC();

protected:
    HANDLE hProcess;

private:
    HWND hwndProcess;
    std::list<DWORD> childs;
    bool needClose;

    void identify(HANDLE hProcess);
    void identify(DWORD pid);
    void close();
};

#endif // CONNECTORIPC_H
