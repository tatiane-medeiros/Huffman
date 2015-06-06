#-------------------------------------------------
#
# Project created by QtCreator 2014-12-09T17:38:54
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Huffman-Project
TEMPLATE = app


SOURCES += main.cpp\
    Node.cpp \
    Code.cpp \
    Decode.cpp \
    gui.cpp

HEADERS  += \
    Node.h \
    Code.h \
    Decode.h \
    gui.h \
    help.h

FORMS    += \
    gui.ui

RC_FILE = dialogo.rc
