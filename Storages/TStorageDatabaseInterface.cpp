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

        QTest::newRow("single-root") << (StorageTree("first")
                                         .setRoot(StorageTreeNode("root"))
                                        .setBalance("root", 2)
                                        .setExpense("root", 9));

        QTest::newRow("level2") << (StorageTree("second")
                                    .setRoot(StorageTreeNode("root"))
                                    .setBalance("root", 5)
                                    .setExpense("root", 2)
                                    .addChild("root", "node1")
                                    .setBalance("node1", 59)
                                    .setExpense("node1", 50));

        QTest::newRow("level3") << (StorageTree("third")
                                    .setRoot(StorageTreeNode("root"))
                                    .setBalance("root", 6)
                                    .setExpense("root", 1)
                                    .addChild("root", ("node1")
                                              ).setBalance("node1", 45)
                                    .setExpense("node1", 12)
                                    .addChild("node1", ("leaf1"))
                                    .setBalance("leaf1", 5)
                                    .setExpense("leaf1", 100));

        QTest::newRow("level4") << (StorageTree("fourth")
                                    .setRoot(StorageTreeNode("root"))
                                    .setBalance("root", 3)
                                    .setExpense("root", 6)
                                    .addChild("root", ("node1"))
                                    .setBalance("node1", 6)
                                    .setExpense("node1", 5)
                                    .addChild("node1", ("leaf1"))
                                    .setBalance("leaf1", 5)
                                    .setExpense("leaf1", 1)
                                    .addChild("root", ("node2"))
                                    .setBalance("node2", 88)
                                    .setExpense("node2", 100)
                                    .addChild("node2", ("leaf2"))
                                    .setBalance("leaf2", 8)
                                    .setExpense("leaf2", 10)
                                    .addChild("node2", ("leaf3"))
                                    .setBalance("leaf3", -100)
                                    .setExpense("leaf3", 100));

    QTest::newRow("level5")<< (StorageTree("fifth")
                               .setRoot(StorageTreeNode("root"))
                               .setBalance("root", -55)
                               .setExpense("root", 55)
                               .addChild("root", ("leaf1"))
                               .setBalance("leaf1", 10)
                               .setExpense("leaf1", 10)
                               .addChild("root", ("leaf2"))
                               .setBalance("leaf2", -13)
                               .setExpense("leaf2", 66)
                               .addChild("leaf1", ("leaf3"))
                               .setBalance("leaf3", 0)
                               .setExpense("leaf3",1)
                               .addChild("leaf2", ("leaf4"))
                               .setBalance("leaf4", 10)
                               .setExpense("leaf4",1)
                               .addChild("leaf2", ("leaf5"))
                               .setBalance("leaf5", 0)
                               .setExpense("leaf5",1));
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
    const StorageTree actualTree = reader.read(tree.id());
    QCOMPARE(actualTree, tree);
}

void TStorageDatabaseInterface::TestReWrite_data()
{

}

void TStorageDatabaseInterface::TestReWrite()
{

}
