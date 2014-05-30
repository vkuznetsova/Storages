#include "TStorageDatabaseInterface.h"


TStorageDatabaseInterface::TStorageDatabaseInterface()
{
}

void TStorageDatabaseInterface::TestCreateDataBase()
{
    const QString dataBaseName = "TStorageDatabaseInterface.TestCreateDataBase.db";

    if(QFile::exists(dataBaseName))
    {
        if(!QFile::remove(dataBaseName))
        {
            QFAIL("can't remove testing database");
        }
    }

    StorageDatabaseInterface i(dataBaseName);

    QCOMPARE(QFile::exists(dataBaseName), true);
}

void TStorageDatabaseInterface::TestWriteAndRead_data()
{
    QTest::addColumn<StorageTree>("tree");

    QTest::newRow("empty-tree") << StorageTree("id0");
}

void TStorageDatabaseInterface::TestWriteAndRead()
{
    QFETCH(StorageTree, tree);

    const QString tag = QTest::currentDataTag();
    const QString dataBaseName = tag + ".TStorageDatabaseInterface.TestWriteAndRead.db";

    if(QFile::exists(dataBaseName))
    {
        if(!QFile::remove(dataBaseName))
        {
            QFAIL("can't remove testing database");
        }
    }

    StorageDatabaseWriter writer(dataBaseName);
    writer.write(tree);

    StorageDatabaseReader reader(dataBaseName);

    QCOMPARE(reader.read(tree.id()), tree);
}
