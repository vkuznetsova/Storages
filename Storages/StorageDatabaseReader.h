#ifndef STORAGEDATABASEREADER_H

#define STORAGEDATABASEREADER_H

#include <QSqlRecord>

#include "StorageTree.h"
#include "StorageDatabaseInterface.h"

class StorageDatabaseReader: public StorageDatabaseInterface
{
public:
    StorageDatabaseReader();
    StorageDatabaseReader (const QString &dataBaseName);

    StorageTree read(const QString &idTree);


    QList<QString> readID();

};

#endif // STORAGEDATABASEREADER_H
