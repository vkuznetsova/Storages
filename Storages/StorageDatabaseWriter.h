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

    void updateBalance(const int value, const QString idNode);

    void updateExpense(const int value, const QString idNode);

    void readFromJSONFile(const QString &fileName);

};

#endif // STORAGEDATABASEWRITER_H
