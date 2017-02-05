#include <iostream>
#include <windows.h>
#include "UniReceiverIPC.h"

std::unordered_map<HWND, std::unordered_map<unsigned int, IReceiverIPC*>> UniReceiverIPC::pool;
unsigned int UniReceiverIPC::gIndexPool = 0;

using namespace std;


LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    /* notify all the instances of receivers for this hwnd */
    unordered_map<unsigned int, IReceiverIPC*>* receivers = UniReceiverIPC::getInstances(hwnd);
    if(receivers != NULL) {
        for(auto& it : (*receivers)) {
            if(it.second != NULL) {
                it.second->wndProc(msg, wParam, lParam);
            }
        }
    }


    switch(msg)
    {
        case WM_CLOSE:
            DestroyWindow(hwnd);
        break;

        case WM_DESTROY:
            PostQuitMessage(0);
        break;

        default:
            return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}


unordered_map<unsigned int, IReceiverIPC*>* UniReceiverIPC::getInstances(HWND hwnd) {
    if(pool.find(hwnd) != pool.end()) {
        return &pool[hwnd];
    }

    return NULL;
}

void UniReceiverIPC::listenMessages() {
    MSG messages;
    while (GetMessage (&messages, NULL, 0, 0))
    {
        TranslateMessage(&messages);
        DispatchMessage(&messages);
    }
}


UniReceiverIPC::UniReceiverIPC() {
    indexPool = gIndexPool++;
}

void UniReceiverIPC::sync(HWND hWnd) {
    ConnectorIPC::sync(hWnd);
    std::unordered_map<unsigned int, IReceiverIPC*>& mapInstances = pool[hWnd];
    if(mapInstances.find(indexPool) == mapInstances.end()) {
        mapInstances[indexPool] = this;
    } else {
        cout << "Erreur lors de la synchronisation de l'instance : un autre connecteur entre en conflit avec cet id" << endl;
    }
}

HWND UniReceiverIPC::createHwnd() {
    WNDCLASSEX wc;

    wc.cbSize        = sizeof(WNDCLASSEX);
    wc.style         = 0;
    wc.lpfnWndProc   = WndProc;
    wc.cbClsExtra    = 0;
    wc.cbWndExtra    = 0;
    wc.hInstance     = NULL;
    wc.hIcon         = LoadIcon(NULL, IDI_APPLICATION);
    wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
    wc.lpszMenuName  = NULL;
    wc.lpszClassName = L"IPCModuleWindow";
    wc.hIconSm       = LoadIcon(NULL, IDI_APPLICATION);

    RegisterClassEx(&wc);
    HWND result = CreateWindowEx(WS_EX_CLIENTEDGE,
                                         wc.lpszClassName,
                                         L"IPCModuleWindow",
                                         WS_OVERLAPPEDWINDOW,
                                         CW_USEDEFAULT, CW_USEDEFAULT, 240, 120,
                                         NULL, NULL, NULL, NULL);
    ShowWindow(result, SW_HIDE);
    UpdateWindow(result);
    return result;
}

void UniReceiverIPC::wndProc(UINT msg, WPARAM wParam, LPARAM lParam) {
#ifdef DEBUG
    cout << "DEBUG : Message recu : " << msg << " wParam : " << wParam << " lParam : " << lParam << endl;
#endif
    if(listeners.find(msg) != listeners.end()) {
        CallbackProc callback = listeners[msg];
        (*callback)(wParam, lParam);
    }
}


void UniReceiverIPC::addListener(std::string messageName, CallbackProc proc) {
    if(listeners.empty()) {
        sync(createHwnd());
    }
    UINT uidListener = RegisterWindowMessageA(messageName.c_str());
    listeners[uidListener] = proc;
}


UniReceiverIPC::~UniReceiverIPC(){
    std::unordered_map<unsigned int, IReceiverIPC*>& listInstances = pool[getHwnd()];
    if(listInstances.find(indexPool) != listInstances.end()) {
        listInstances[indexPool] = NULL;
    }
}
