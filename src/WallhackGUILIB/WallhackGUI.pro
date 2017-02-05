#-------------------------------------------------
#
# Project created by QtCreator 2015-02-02T23:48:01
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = WallhackGUI
TEMPLATE = app

CONFIG += static

SOURCES +=\
        MainWindow.cpp \
    main.cpp \
    ArgUtils.cpp \
    PathExeUtils.cpp \
    ProcessUtils.cpp \
    ShortcutPlainTextEdit.cpp

HEADERS  += MainWindow.h \
    ArgUtils.h \
    PathExeUtils.h \
    ProcessUtils.h \
    ShortcutPlainTextEdit.h

FORMS    += MainWindow.ui

LIBS += -lpsapi

QMAKE_CXXFLAGS += -std=c++11

INCLUDEPATH += $$PWD/../Wallhack


win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../build-LIB_HWND_IPC-Mingw_32-Release/release/ -lLIB_HWND_IPC
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../build-LIB_HWND_IPC-Mingw_32-Debug/debug/ -lLIB_HWND_IPC

INCLUDEPATH += $$PWD/../LIB_HWND_IPC
DEPENDPATH += $$PWD/../LIB_HWND_IPC

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../build-LIB_HWND_IPC-Mingw_32-Release/release/libLIB_HWND_IPC.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../build-LIB_HWND_IPC-Mingw_32-Debug/debug/libLIB_HWND_IPC.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../build-LIB_HWND_IPC-Mingw_32-Release/release/LIB_HWND_IPC.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../build-LIB_HWND_IPC-Mingw_32-Debug/debug/LIB_HWND_IPC.lib
