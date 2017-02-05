TEMPLATE = app
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    main.cpp \
    PathExeUtils.cpp \
    start.cpp \
    WindowsCallback.cpp \
    HookStart.cpp \
    ProcessUtils.cpp \
    ArgUtils.cpp \
    WindowUtils.cpp \
    HWNDStack.cpp \
    UserMessages.cpp

HEADERS += \
    start.h \
    WindowsCallback.h \
    ProcessUtils.h \
    HookStart.h \
    PathExeUtils.h \
    ArgUtils.h \
    MessagesDefine.h \
    WindowUtils.h \
    HWNDStack.h \
    UserMessages.h

LIBS += -lpsapi

QMAKE_CXXFLAGS += -std=c++11

INCLUDEPATH += $$PWD/../GlobalHooks
DEPENDPATH += $$PWD/../GlobalHooks

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../build-LIB_HWND_IPC-Mingw_32-Release/release/ -lLIB_HWND_IPC
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../build-LIB_HWND_IPC-Mingw_32-Debug/debug/ -lLIB_HWND_IPC

INCLUDEPATH += $$PWD/../LIB_HWND_IPC
DEPENDPATH += $$PWD/../LIB_HWND_IPC

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../build-LIB_HWND_IPC-Mingw_32-Release/release/libLIB_HWND_IPC.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../build-LIB_HWND_IPC-Mingw_32-Debug/debug/libLIB_HWND_IPC.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../build-LIB_HWND_IPC-Mingw_32-Release/release/LIB_HWND_IPC.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../build-LIB_HWND_IPC-Mingw_32-Debug/debug/LIB_HWND_IPC.lib
