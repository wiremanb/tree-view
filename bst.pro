#-------------------------------------------------
#
# Project created by QtCreator 2016-07-06T17:38:31
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = bst
TEMPLATE = app


SOURCES += main.cpp\
        bstviewer.cpp \
    node.cpp \
    avl_tree/avl.cpp \
    min_heap/min_heap.cpp \
    bst/binary_search_tree.cpp

HEADERS  += bstviewer.h \
    node.h \
    avl_tree/avl.h \
    min_heap/min_heap.h \
    bst/binary_search_tree.h

FORMS    += bstviewer.ui
