#-------------------------------------------------
#
# Project created by QtCreator 2014-05-08T11:10:30
#
#-------------------------------------------------

QT       += core testlib

QT       -= gui

TARGET = Storages
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    StorageTree.cpp \
    TStorageTree.cpp

HEADERS += \
    StorageTree.h \
    TStorageTree.h \
    StorageTreeNode.h \
    StorageTreeNodeMap.h \
    StorageTreePredicat.h \
    BooleanStorageTreePredicat.h \
    StorageUtils.h \
    BalancedStorageTreePredicat.h \
    IDStorageTreePredicat.h \
    NSunsStorageTreePredicat.h \
    STNFold.h \
    STNToStringFold.h \
    STNSum.h \
    STNTotalSum.h
