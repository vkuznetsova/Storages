#ifndef STORAGEDATABASEREADER_H

#define STORAGEDATABASEREADER_H

#include <QSqlRecord>
#include <QFile>

#include "StorageTree.h"
#include "StorageDatabaseInterface.h"

class StorageDatabaseReader: public StorageDatabaseInterface
{
public:
    StorageDatabaseReader();
    StorageDatabaseReader (const QString &dataBaseName);

    StorageTree read(const QString &idTree);

    QList<QString> readID();

    void writeToFile(const QString &idTree, const QString &name);

};

#endif // STORAGEDATABASEREADER_H
