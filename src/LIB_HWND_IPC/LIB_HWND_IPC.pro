#-------------------------------------------------
#
# Project created by QtCreator 2015-02-09T02:33:40
#
#-------------------------------------------------

QT       -= core gui

TARGET = LIB_HWND_IPC
TEMPLATE = lib
CONFIG += staticlib

SOURCES += \
    ConnectorIPC.cpp \
    UniReceiverIPC.cpp \
    UniSenderIPC.cpp \
    ArgUtils.cpp

HEADERS += LIB_HWND_IPC.h \
    AbstractReceiverIPC.h \
    AbstractSenderIPC.h \
    CallbackProc.h \
    ConnectorIPC.h \
    IReceiverIPC.h \
    ISenderIPC.h \
    UniReceiverIPC.h \
    UniSenderIPC.h \
    ArgUtils.h
unix {
    target.path = /usr/lib
    INSTALLS += target
}


QMAKE_CXXFLAGS += -std=c++11
