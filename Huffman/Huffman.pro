#-------------------------------------------------
#
# Project created by QtCreator 2015-05-12T15:53:37
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Huffman
TEMPLATE = app

SOURCES += main.cpp\
    HTree.cpp \
    zip.cpp \
    Node.cpp \
    bitvector.cpp \
    huffman.cpp

HEADERS  += huffman.h \
    Node.h \
    HTree.h \
    zip.h \
    help.h \
    bitvector.h \

FORMS    += huffman.ui

RC_FILE += dialogo.rc
