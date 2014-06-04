#ifndef TSTORAGEDATABASEINTERFACE_H

#define TSTORAGEDATABASEINTERFACE_H

#include <QtCore>
#include <QtTest/QtTest>
#include "StorageTree.h"
#include "StorageDatabaseReader.h"
#include "StorageDatabaseInterface.h"
#include "StorageDatabaseWriter.h"

class TStorageDatabaseInterface : public QObject
{
    Q_OBJECT
public:
    TStorageDatabaseInterface();

private slots:
    void TestCreateDataBase();

    void TestWriteAndRead_data();
    void TestWriteAndRead();

    void TestReWrite_data();
    void TestReWrite();
};

#endif // TSTORAGEDATABASEINTERFACE_H
