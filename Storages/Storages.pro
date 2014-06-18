#-------------------------------------------------
#
# Project created by QtCreator 2014-05-08T11:10:30
#
#-------------------------------------------------

QT       += core testlib gui widgets sql


TARGET = Storages

CONFIG   -= app_bundle

TEMPLATE = app

CODECFORTR  = utf8
CODECFORSRC = utf8

CONFIG(tests){
    QT       -= gui
    CONFIG  += console
    DEFINES += TESTS
}

CONFIG(gui){
    DEFINES += GUI
}

SOURCES += main.cpp \
    StorageTree.cpp \
    TStorageTree.cpp \
    Swindow.cpp \
    TableModel.cpp \
    TTableModel.cpp \
    TStorageDatabaseInterface.cpp \
    StorageDatabaseInterface.cpp \
    StorageDatabaseWriter.cpp \
    StorageDatabaseReader.cpp \
    StorageTreeNode.cpp \
    TStorageTreeNode.cpp

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
    STNTotalSum.h \
    Swindow.h \
    TableModel.h \
    TTableModel.h \
    TStorageDatabaseInterface.h \
    StorageDatabaseInterface.h \
    StorageDatabaseWriter.h \
    StorageDatabaseReader.h \
    TStorageTreeNode.h
