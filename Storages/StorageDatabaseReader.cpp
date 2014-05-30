#include "StorageDatabaseReader.h"

StorageDatabaseReader::StorageDatabaseReader()
{
}

StorageDatabaseReader::StorageDatabaseReader(const QString &dataBaseName):
    StorageDatabaseInterface(dataBaseName)
{

}

StorageTree StorageDatabaseReader::read(const QString idTree)
{
    return StorageTree();

}
