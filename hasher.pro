#-------------------------------------------------
#
# Project created by QtCreator 2015-07-19T10:28:20
#
#-------------------------------------------------

QT       += core webchannel websockets

QT       -= gui

TARGET = hasher
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    shared/websocketclientwrapper.cpp \
    shared/websockettransport.cpp \
    hasher.cpp

HEADERS += \
    shared/websocketclientwrapper.h \
    shared/websockettransport.h \
    hasher.h
