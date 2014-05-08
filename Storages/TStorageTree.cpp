#include "TStorageTree.h"

TStorageTree::TStorageTree()
{
}

void TStorageTree::TestChildren_data()
{
    QTest::addColumn<StorageTree>("tree");
    QTest::addColumn<QString>("parent");
    QTest::addColumn<QStringList>("children");

    QTest::newRow("empty") << StorageTree()
                           << ""
                           << QStringList();

    QTest::newRow("single-root") << (StorageTree()
                                     .setRoot(StorageTreeNode("root")))
                                 << "root"
                                 << QStringList();

    QTest::newRow("single-leaf") << (StorageTree()
                                     .setRoot(StorageTreeNode("root"))
                                     .addChild("root", StorageTreeNode("leaf1")))
                                 << "root"
                                 << (QStringList() << "leaf1");

    QTest::newRow("two-leafs") <<( StorageTree()
                                   .setRoot(StorageTreeNode("root"))
                                   .addChild("root",  StorageTreeNode("leaf1"))
                                   .addChild("root", StorageTreeNode("leaf2")))
                              << "root"
                              << (QStringList() << "leaf1" << "leaf2");

    QTest::newRow("three-levels-tree") <<( StorageTree()
                                           .setRoot(StorageTreeNode("root"))
                                           .addChild("root",StorageTreeNode("node1"))
                                           .addChild("node1", StorageTreeNode("leaf1"))
                                           .addChild("node1", StorageTreeNode("leaf2")))
                                      << "node1"
                                      << (QStringList() << "leaf1" << "leaf2");

    QTest::newRow("no-such-id") << ( StorageTree()
                                     .setRoot(StorageTreeNode("root"))
                                     .addChild("root",StorageTreeNode("node1"))
                                     .addChild("node1", StorageTreeNode("leaf1"))
                                     .addChild("node1", StorageTreeNode("leaf2")))
                                << "node2"
                                << (QStringList());
}

void TStorageTree::TestChildren()
{
    QFETCH(StorageTree, tree);
    QFETCH(QString, parent);
    QFETCH(QStringList, children);

    const QStringList actual = tree.children(parent);

    QCOMPARE(actual, children);
}
