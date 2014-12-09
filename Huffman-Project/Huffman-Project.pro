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
        gui.cpp \
    Node.cpp \
    Code.cpp \
    Decode.cpp

HEADERS  += gui.h \
    Node.h \
    Code.h \
    Decode.h

FORMS    += gui.ui
