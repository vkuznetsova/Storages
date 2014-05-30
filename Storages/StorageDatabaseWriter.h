#ifndef STORAGEDATABASEWRITER_H

#define STORAGEDATABASEWRITER_H

#include "StorageTree.h"
#include "StorageDatabaseInterface.h"

class StorageDatabaseWriter: public StorageDatabaseInterface
{
public:
    StorageDatabaseWriter();

    StorageDatabaseWriter(const QString &dataBaseName);

    void write(const StorageTree &tree);

};

#endif // STORAGEDATABASEWRITER_H
