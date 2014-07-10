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
    QTest::addColumn <StorageTree> ("tree");

    QTest::newRow("empty-tree") << StorageTree("id0");

    QTest::newRow("single-root") << (StorageTree("first")
                                     .setRoot("root"))
                                    .setBalance("root", 2)
                                    .setExpense("root", 9)
                                    .setDeliveryTime("root", 8);

    QTest::newRow("level2") << (StorageTree("second")
                                .setRoot("root")
                                .addChild("root", "node1"))
                               .setBalance("root", 5)
                               .setExpense("root", 2)
                               .setBalance("node1", 59)
                               .setExpense("node1", 50)
                               .setDeliveryTime("root", 2)
                               .setDeliveryTime("node1", 18);

    QTest::newRow("level3") << (StorageTree("third")
                                .setRoot("root")
                                .addChild("root", "node1")
                                .addChild("node1", "leaf1"))
                               .setBalance("root", 6)
                               .setExpense("root", 1)
                               .setBalance("node1", 45)
                               .setExpense("node1", 12)
                               .setBalance("leaf1", 5)
                               .setExpense("leaf1", 100)
                               .setDeliveryTime("root", 1)
                               .setDeliveryTime("node1", 11)
                               .setDeliveryTime("leaf1", 100);

    QTest::newRow("level4") << (StorageTree("fourth")
                                .setRoot("root")
                                .addChild("root", "node1")
                                .addChild("node1", "leaf1")
                                .addChild("root", "node2")
                                .addChild("node2", "leaf2")
                                .addChild("node2", "leaf3"))
                               .setBalance("leaf3", -100)
                               .setExpense("leaf3", 100)
                               .setBalance("root", 3)
                               .setExpense("root", 6)
                               .setBalance("node1", 6)
                               .setExpense("node1", 5)
                               .setBalance("leaf1", 5)
                               .setExpense("leaf1", 1)
                               .setBalance("node2", 88)
                               .setExpense("node2", 100)
                               .setBalance("leaf2", 8)
                               .setExpense("leaf2", 10)
                               .setDeliveryTime("root", 100)
                               .setDeliveryTime("node1", 1)
                               .setDeliveryTime("node2", 3)
                               .setDeliveryTime("leaf1", 113)
                               .setDeliveryTime("leaf2", 13)
                               .setDeliveryTime("leaf3", 5);

    QTest::newRow("level5") << (StorageTree("fifth")
                                .setRoot("root")
                                .addChild("root", "leaf1")
                                .addChild("root", "leaf2")
                                .addChild("leaf1", "leaf3")
                                .addChild("leaf2", "leaf4")
                                .addChild("leaf2", "leaf5"))
                               .setBalance("root", -55)
                               .setExpense("root", 55)
                               .setBalance("leaf1", 10)
                               .setExpense("leaf1", 10)
                               .setBalance("leaf2", -13)
                               .setExpense("leaf2", 66)
                               .setBalance("leaf3", 0)
                               .setExpense("leaf3",1)
                               .setBalance("leaf4", 10)
                               .setExpense("leaf4",1)
                               .setBalance("leaf5", 0)
                               .setExpense("leaf5",1)
                               .setDeliveryTime("root", 1)
                               .setDeliveryTime("leaf1", 100)
                               .setDeliveryTime("leaf2", 2)
                               .setDeliveryTime("leaf3", 3)
                               .setDeliveryTime("leaf4", 6)
                               .setDeliveryTime("leaf5", 9);
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
    QTest::addColumn <StorageTree> ("tree");
    QTest::addColumn <StorageTree> ("newTree");

    QTest::newRow("empty-tree") << StorageTree("id0")
                                << StorageTree("id0");

    QTest::newRow("single-root") << (StorageTree("first")
                                     .setRoot("root"))
                                    .setBalance("root", 2)
                                    .setExpense("root", 9)
                                    .setDeliveryTime("root", 1)
                                 << (StorageTree("first")
                                     .setRoot("root"))
                                    .setBalance("root", 8)
                                    .setExpense("root", 2)
                                    .setDeliveryTime("root", 2);

    QTest::newRow("level2") << (StorageTree("second")
                                .setRoot("root"))
                               .setBalance("root", 5)
                               .setExpense("root", 2)
                               .setDeliveryTime("root", 2)
                            << (StorageTree("second")
                                .setRoot("root"))
                               .setBalance("root", 6)
                               .setExpense("root", 27)
                               .setDeliveryTime("root", 3);

    QTest::newRow("level3") << (StorageTree("third")
                                .setRoot("root")
                                .addChild("root", "node1")
                                .addChild("node1", "leaf1"))
                               .setBalance("root", 6)
                               .setExpense("root", 1)
                               .setBalance("node1", 45)
                               .setExpense("node1", 12)
                               .setBalance("leaf1", 5)
                               .setExpense("leaf1", 100)
                               .setDeliveryTime("root", 1)
                               .setDeliveryTime("node1", 4)
                               .setDeliveryTime("leaf1", 12)
                            << (StorageTree("third")
                                .setRoot("root"))
                               .setBalance("root", 2)
                               .setExpense("root", 9)
                               .setDeliveryTime("root", 4);

    QTest::newRow("level4") << (StorageTree("fourth")
                                .setRoot("root")
                                .addChild("root", "node1")
                                .addChild("node1", "leaf1")
                                .addChild("root", "node2")
                                .addChild("node2", "leaf2")
                                .addChild("node2", "leaf3"))
                               .setBalance("leaf3", -100)
                               .setExpense("leaf3", 100)
                               .setBalance("root", 3)
                               .setExpense("root", 6)
                               .setBalance("node1", 6)
                               .setExpense("node1", 5)
                               .setBalance("leaf1", 5)
                               .setExpense("leaf1", 1)
                               .setBalance("node2", 88)
                               .setExpense("node2", 100)
                               .setBalance("leaf2", 8)
                               .setExpense("leaf2", 10)
                               .setDeliveryTime("root", 1)
                               .setDeliveryTime("node1", 10)
                               .setDeliveryTime("leaf1", 5)
                               .setDeliveryTime("node2", 13)
                               .setDeliveryTime("leaf2", 6)
                               .setDeliveryTime("leaf3", 9)
                            << StorageTree("fourth");

    QTest::newRow("level5") << (StorageTree("fifth")
                                .setRoot("root")
                                .addChild("root", "leaf1")
                                .addChild("root", "leaf2")
                                .addChild("leaf1", "leaf3")
                                .addChild("leaf2", "leaf4")
                                .addChild("leaf2", "leaf5"))
                               .setBalance("root", -55)
                               .setExpense("root", 55)
                               .setBalance("leaf1", 10)
                               .setExpense("leaf1", 10)
                               .setBalance("leaf2", -13)
                               .setExpense("leaf2", 66)
                               .setBalance("leaf3", 0)
                               .setExpense("leaf3",1)
                               .setBalance("leaf4", 10)
                               .setExpense("leaf4",1)
                               .setBalance("leaf5", 0)
                               .setExpense("leaf5",1)
                               .setDeliveryTime("root", 1)
                               .setDeliveryTime("leaf1", 31)
                               .setDeliveryTime("leaf2", 6)
                               .setDeliveryTime("leaf3", 9)
                               .setDeliveryTime("leaf4", 7)
                               .setDeliveryTime("leaf5", 61)
                            << (StorageTree("fifth")
                                .setRoot("root")
                                .addChild("root", "leaf1"))
                               .setBalance("root", -55)
                               .setExpense("root", 55)
                               .setBalance("leaf1", 10)
                               .setExpense("leaf1", 10)
                               .setDeliveryTime("root", 22)
                               .setDeliveryTime("leaf1", 4);

}

void TStorageDatabaseInterface::TestReWrite()
{
    QFETCH(StorageTree, tree);
    QFETCH(StorageTree, newTree);

    const QString tag = QTest::currentDataTag();
    const QString dataBaseName = tag + ".TStorageDatabaseInterface.TestReWrite.db";

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
    writer.write(newTree);
    const StorageTree actualTree = reader.read(newTree.id());

    QCOMPARE(actualTree, newTree);
}

void TStorageDatabaseInterface::TestWriteToFile_data()
{
    QTest::addColumn <QList <StorageTree> > ("expected");

    QTest::newRow("empty-list") << QList <StorageTree>();

    QTest::newRow("one-trees") << (QList <StorageTree> ()
                                   << StorageTree("id0")
                                   .setRoot("root")
                                   .setBalance("root", 5)
                                   .setExpense("root", 999)
                                   .setDeliveryTime("root", 15));

    QTest::newRow("two-trees") << (QList <StorageTree> ()
                                   << (StorageTree("first-1")
                                       .setRoot("root-1")
                                       .setBalance("root-1", -99)
                                       .setExpense("root-1", 55)
                                       .setDeliveryTime("root-1", 5))
                                   << (StorageTree("first")
                                       .setRoot("root"))
                                   .setBalance("root", 2)
                                   .setExpense("root", 9)
                                   .setDeliveryTime("root", 2));
        QTest::newRow("two-trees-1") << (QList <StorageTree> ()
                                       << (StorageTree("first")
                                           .setRoot("root")
                                           .setBalance("root", -99)
                                           .setExpense("root", 55)
                                           .setDeliveryTime("root", 5))
                                       << (StorageTree("second")
                                           .setRoot("root"))
                                       .setBalance("root", -99)
                                       .setExpense("root", 55)
                                       .setDeliveryTime("root", 5));

        QTest::newRow("two-trees-2") << (QList <StorageTree> ()
                                       << (StorageTree("first")
                                           .setRoot("root")
                                           .addChild("root", "node1"))
                                         .setBalance("root", 5)
                                         .setExpense("root", 2)
                                         .setDeliveryTime("root", 12)
                                         .setBalance("node1", 59)
                                         .setExpense("node1", 50)
                                         .setDeliveryTime("node1", 1)
                                       << (StorageTree("second")
                                           .setRoot("root")
                                           .addChild("root", "node1")
                                           .addChild("root", "node2"))
                                         .setBalance("root", 5)
                                         .setExpense("root", 2)
                                         .setDeliveryTime("root", 12)
                                         .setBalance("node1", 59)
                                         .setExpense("node1", 50)
                                         .setDeliveryTime("node1", 1)
                                         .setBalance("node2", 1)
                                         .setExpense("node2", 2)
                                         .setDeliveryTime("node2", 3));

    QTest::newRow("one-trees-1") << (QList <StorageTree>()
                                     <<(StorageTree("first")
                                        .setRoot("root"))
                                     .setBalance("root", 2)
                                     .setExpense("root", 9)
                                     .setDeliveryTime("root", 2));

    QTest::newRow("three-trees") << (QList <StorageTree> ()
                                     <<(StorageTree("second")
                                        .setRoot("root")
                                        .addChild("root", "node1"))
                                     .setBalance("root", 5)
                                     .setExpense("root", 2)
                                     .setDeliveryTime("root", 12)
                                     .setBalance("node1", 59)
                                     .setExpense("node1", 50)
                                     .setDeliveryTime("node1", 1)
                                     << (StorageTree("first")
                                         .setRoot("root"))
                                     .setBalance("root", 5)
                                     .setExpense("root", 2)
                                     .setDeliveryTime("root", 12)
                                     << StorageTree("third")
                                     .setRoot("root")
                                     .setBalance("root", 5)
                                     .setExpense("root", 2)
                                     .setDeliveryTime("root", 12));

    QTest::newRow("four-trees") << (QList <StorageTree> ()
                                    << (StorageTree("first")
                                        .setRoot("root"))
                                    .setBalance("root", 5)
                                    .setExpense("root", 2)
                                    .setDeliveryTime("root", 12)
                                    << (StorageTree("second")
                                        .setRoot("root")
                                        .addChild("root", "node1"))
                                     .setBalance("root", 5)
                                     .setExpense("root", 2)
                                     .setDeliveryTime("root", 12)
                                     .setBalance("node1", 59)
                                     .setExpense("node1", 50)
                                     .setDeliveryTime("node1", 1)
                                    << (StorageTree("third")
                                        .setRoot("root")
                                        .addChild("root", "leaf1")
                                        .addChild("root", "leaf2")
                                        .addChild("leaf1", "leaf3")
                                        .addChild("leaf2", "leaf4")
                                        .addChild("leaf2", "leaf5"))
                                    .setBalance("root", 5)
                                    .setExpense("root", 2)
                                    .setDeliveryTime("root", 12)
                                    .setBalance("leaf1", 12)
                                    .setExpense("leaf1", 10)
                                    .setDeliveryTime("leaf1", 9)
                                    .setBalance("leaf2", -13)
                                    .setExpense("leaf2", 66)
                                    .setDeliveryTime("leaf2", 5)
                                    .setBalance("leaf3", 0)
                                    .setExpense("leaf3",1)
                                    .setDeliveryTime("leaf3", 33)
                                    .setBalance("leaf4", 10)
                                    .setExpense("leaf4",1)
                                    .setDeliveryTime("leaf4", 8)
                                    .setBalance("leaf5", 0)
                                    .setExpense("leaf5",1)
                                    .setDeliveryTime("leaf5", 9)
                                    << (StorageTree("fourth")
                                        .setRoot("root")
                                        .addChild("root", "node1")
                                        .addChild("node1", "leaf1")
                                        .addChild("root", "node2")
                                        .addChild("node2", "leaf2")
                                        .addChild("node2", "leaf3"))
                                    .setBalance("leaf3", 0)
                                    .setExpense("leaf3", 1)
                                    .setDeliveryTime("leaf3", 33)
                                    .setBalance("root", 5)
                                    .setExpense("root", 2)
                                    .setDeliveryTime("root", 12)
                                    .setBalance("node1", 59)
                                    .setExpense("node1", 50)
                                    .setDeliveryTime("node1", 1)
                                    .setBalance("leaf1", 12)
                                    .setExpense("leaf1", 10)
                                    .setDeliveryTime("leaf1", 9)
                                    .setBalance("node2", 88)
                                    .setExpense("node2", 100)
                                    .setDeliveryTime("node2", 6)
                                    .setBalance("leaf2", -13)
                                    .setExpense("leaf2", 66)
                                    .setDeliveryTime("leaf2", 5));

    QTest::newRow("five-trees") << (QList <StorageTree> ()
                                    << (StorageTree("fourth")
                                        .setRoot("root")
                                        .addChild("root", "node1")
                                        .addChild("node1", "leaf1")
                                        .addChild("root", "node2")
                                        .addChild("node2", "leaf2")
                                        .addChild("node2", "leaf3"))
                                    .setBalance("leaf3", -100)
                                    .setExpense("leaf3", 100)
                                    .setDeliveryTime("leaf3", 6)
                                    .setBalance("root", 3)
                                    .setExpense("root", 6)
                                    .setDeliveryTime("root", 45)
                                    .setBalance("node1", 6)
                                    .setExpense("node1", 5)
                                    .setDeliveryTime("node1", 4)
                                    .setBalance("leaf1", 5)
                                    .setExpense("leaf1", 1)
                                    .setDeliveryTime("leaf1", 5)
                                    .setBalance("node2", 88)
                                    .setExpense("node2", 100)
                                    .setDeliveryTime("node2", 55)
                                    .setBalance("leaf2", 8)
                                    .setExpense("leaf2", 10)
                                    .setDeliveryTime("leaf2", 7)
                                    << (StorageTree("third")
                                        .setRoot("root")
                                        .setBalance("root", 3)
                                        .setExpense("root", 6)
                                        .setDeliveryTime("root", 45))
                                    << (StorageTree("second")
                                        .setRoot("root")
                                        .addChild("root", "node1")
                                        .addChild("node1", "leaf1"))
                                    .setBalance("root", 3)
                                    .setExpense("root", 6)
                                    .setDeliveryTime("root", 45)
                                    .setBalance("node1", 6)
                                    .setExpense("node1", 5)
                                    .setDeliveryTime("node1", 4)
                                    .setBalance("leaf1", 5)
                                    .setExpense("leaf1", 1)
                                    .setDeliveryTime("leaf1", 5)
                                    << (StorageTree("fifth")
                                        .setRoot("root")
                                        .addChild("root", "leaf1")
                                        .addChild("root", "leaf2")
                                        .addChild("leaf1", "leaf3")
                                        .addChild("leaf2", "leaf4")
                                        .addChild("leaf2", "leaf5"))
                                    .setBalance("root", 3)
                                    .setExpense("root", 6)
                                    .setDeliveryTime("root", 45)
                                    .setBalance("leaf1", 5)
                                    .setExpense("leaf1", 1)
                                    .setDeliveryTime("leaf1", 5)
                                    .setBalance("leaf2", 8)
                                    .setExpense("leaf2", 10)
                                    .setDeliveryTime("leaf2", 7)
                                    .setBalance("leaf3", -100)
                                    .setExpense("leaf3",100)
                                    .setDeliveryTime("leaf3", 6)
                                    .setBalance("leaf4", 10)
                                    .setExpense("leaf4",1)
                                    .setDeliveryTime("leaf4", 2)
                                    .setBalance("leaf5", 0)
                                    .setExpense("leaf5",1)
                                    .setDeliveryTime("leaf5", 7)
                                    << (StorageTree("first")
                                    .setRoot("root"))
                                    .addChild("root", "leaf1")
                                    .setBalance("root", 3)
                                    .setExpense("root", 6)
                                    .setDeliveryTime("root", 45)
                                    .setBalance("leaf1", 5)
                                    .setExpense("leaf1", 1)
                                    .setDeliveryTime("leaf1", 5));
}

void TStorageDatabaseInterface::TestWriteToFile()
{
    QFETCH(QList <StorageTree>, expected);

    const QString tag = QTest::currentDataTag();
    const QString dataBaseName = tag + "TStorageDatabaseInterface.TestWriteToFile.db";
    const QString fileName = tag + "TStorageDatabaseInterface.TestWriteToFile.json";
    if(QFile::exists(dataBaseName))
    {
        if(!QFile::remove(dataBaseName))
        {
            QFAIL("can't remove testing database");
        }
    }
    if(QFile::exists(fileName))
    {
        if(!QFile::remove(fileName))
        {
            QFAIL("can't remove testing file with data");
        }
    }
    //записать все деревья в базу
    //записать базу в json файл
    //пройтись в цикле по изначальным деревьям, считывать для текущего имени дерева дерево из базы, сравнивать считаное дерево с текущим деревом

    StorageDatabaseWriter writer(dataBaseName);
    for(int i = 0; i < expected.size(); i++)
    {
        writer.write(expected[i]);
    }
    StorageDatabaseReader reader(dataBaseName);
    reader.writeToFile(fileName);
    writer.readFromJSONFile(fileName);
    qSort(expected);
    QList<QString> allID = reader.readID();
    for(int i = 0; i < allID.count(); i++)
    {
        StorageTree tree = reader.read(allID[i]);
        QCOMPARE(tree, expected[i]);
    }
}
