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

    QTest::newRow("two-leafs") <<(StorageTree()
                                  .setRoot(StorageTreeNode("root"))
                                  .addChild("root",  StorageTreeNode("leaf1"))
                                  .addChild("root", StorageTreeNode("leaf2")))
                              << "root"
                              << (QStringList() << "leaf1" << "leaf2");

    QTest::newRow("three-levels-tree") <<(StorageTree()
                                          .setRoot(StorageTreeNode("root"))
                                          .addChild("root",StorageTreeNode("node1"))
                                          .addChild("node1", StorageTreeNode("leaf1"))
                                          .addChild("node1", StorageTreeNode("leaf2")))
                                      << "node1"
                                      << (QStringList() << "leaf1" << "leaf2");

    QTest::newRow("no-such-id") << (StorageTree()
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

void TStorageTree::TestLevel_data()
{
    QTest::addColumn<StorageTree>("tree");
    QTest::addColumn<QString>("node");
    QTest::addColumn<int>("level");

    QTest::newRow("empty-tree") << StorageTree()
                                << ""
                                << 0;

    QTest::newRow("single-root") << (StorageTree()
                                     .setRoot(StorageTreeNode("root")))
                                 << "root"
                                 << 1;

    QTest::newRow("level2-1") << (StorageTree()
                                  .setRoot(StorageTreeNode("root"))
                                  .addChild("root", StorageTreeNode("leaf1")))
                              << "leaf1"
                              << 2;


    QTest::newRow("level2-2") << (StorageTree()
                                  .setRoot(StorageTreeNode("root"))
                                  .addChild("root", StorageTreeNode("node1"))
                                  .addChild("node1", StorageTreeNode("leaf1")))
                              << "node1"
                              << 2;

    QTest::newRow("level3-1") << (StorageTree()
                                  .setRoot(StorageTreeNode("root"))
                                  .addChild("root", StorageTreeNode("node1"))
                                  .addChild("node1", StorageTreeNode("leaf1")))
                              << "leaf1"
                              << 3;

    QTest::newRow("level3-2") << (StorageTree()
                                  .setRoot(StorageTreeNode("root"))
                                  .addChild("root", StorageTreeNode("node1"))
                                  .addChild("node1", StorageTreeNode("leaf1"))
                                  .addChild("node1", StorageTreeNode("leaf2"))
                                  .addChild("node1", StorageTreeNode("leaf3")))
                              << "leaf1"
                              << 3;

    QTest::newRow("level4") << (StorageTree()
                                .setRoot(StorageTreeNode("root"))
                                .addChild("root", StorageTreeNode("node1"))
                                .addChild("node1", StorageTreeNode("node2"))
                                .addChild("node1", StorageTreeNode("leaf2"))
                                .addChild("node2", StorageTreeNode("leaf1")))
                            << "leaf1"
                            << 4;
}

void TStorageTree::TestLevel()
{
    QFETCH(StorageTree, tree);
    QFETCH(QString, node);
    QFETCH(int, level);

    const int actual = tree.level(node);
    QCOMPARE(actual, level);
}

void TStorageTree::TestParent_data()
{
    QTest::addColumn<StorageTree>("tree");
    QTest::addColumn<QString>("child");
    QTest::addColumn<QString>("t_parent");

    QTest::newRow("empty-tree") << StorageTree()
                                << ""
                                << "";

    QTest::newRow("single-root") << (StorageTree()
                                     .setRoot(StorageTreeNode("root")))
                                 << ""
                                 << "";

    QTest::newRow("level12-1") << (StorageTree(StorageTreeNode("root"))
                                   .addChild("root",StorageTreeNode("leaf1")))
                               << "leaf1"
                               << "root";
    
    QTest::newRow("level2-2") << (StorageTree(StorageTreeNode("root"))
                                  .addChild("root", StorageTreeNode("node1"))
                                  .addChild("node1", StorageTreeNode("leaf1")))
                              << "leaf1"
                              << "node1";

    QTest::newRow("level3-1") << (StorageTree(StorageTreeNode("root"))
                                  .addChild("root", StorageTreeNode("node1"))
                                  .addChild("node1", StorageTreeNode("leaf1")))
                              << "node1"
                              << "root";

    QTest::newRow("level3-2") << (StorageTree(StorageTreeNode("root"))
                                  .addChild("root", StorageTreeNode("node1"))
                                  .addChild("node1", StorageTreeNode("leaf1"))
                                  .addChild("node1", StorageTreeNode("leaf2"))
                                  .addChild("node1", StorageTreeNode("leaf3")))
                              << "leaf2"
                              << "node1";

    QTest::newRow("level4") << (StorageTree(StorageTreeNode("root"))
                                .addChild("root", StorageTreeNode("node1"))
                                .addChild("node1", StorageTreeNode("node2"))
                                .addChild("node1", StorageTreeNode("leaf2"))
                                .addChild("node2", StorageTreeNode("leaf1")))
                            << "leaf1"
                            << "node2";

}

void TStorageTree::TestParent()
{
    QFETCH(StorageTree, tree);
    QFETCH(QString, child);
    QFETCH(QString, t_parent);

    const QString actual = tree.parent(child);
    QCOMPARE(actual, t_parent);

}

void TStorageTree::TestSubTree_data()
{
    QTest::addColumn<StorageTree>("tree");
    QTest::addColumn<QString>("root");
    QTest::addColumn<StorageTree>("sub_tree");

    QTest::newRow("empty-tree") << StorageTree()
                                << ""
                                << StorageTree();

    QTest::newRow("single-root") << (StorageTree(StorageTreeNode("root")))
                                 << "root"
                                 << (StorageTree(StorageTreeNode("root")));

    QTest::newRow("level12-1") << (StorageTree(StorageTreeNode("root"))
                                   .addChild("root",StorageTreeNode("leaf1")))
                               << "root"
                               << (StorageTree(StorageTreeNode("root")).addChild("root", StorageTreeNode("leaf1")));

    QTest::newRow("level2-2") << (StorageTree(StorageTreeNode("root"))
                                  .addChild("root", StorageTreeNode("node1"))
                                  .addChild("node1", StorageTreeNode("leaf1")))
                              << "node1"
                              <<(StorageTree(StorageTreeNode("node1"))
                                 .addChild("node1", StorageTreeNode("leaf1")));

    QTest::newRow("level-3") << (StorageTree(StorageTreeNode("root"))
                                 .addChild("root", StorageTreeNode("node1"))
                                 .addChild("node1", StorageTreeNode("leaf1"))
                                 .addChild("root", StorageTreeNode("node2"))
                                 .addChild("node2", StorageTreeNode("leaf2"))
                                 .addChild("node2", StorageTreeNode("leaf3")))
                             << "node2"
                             << (StorageTree(StorageTreeNode("node2"))
                                 .addChild("node2", StorageTreeNode("leaf2"))
                                 .addChild("node2", StorageTreeNode("leaf3")));

}
void TStorageTree::TestSubTree()
{
    QFETCH(StorageTree, tree);
    QFETCH(QString, root);
    QFETCH(StorageTree, sub_tree);

    const StorageTree actual = tree.subTree(root);

    QCOMPARE(actual, sub_tree);
}

void TStorageTree::TestToString_data()
{
    QTest::addColumn<StorageTree>("tree");
    QTest::addColumn<QString>("sRecord");

    QTest::newRow("empty-tree") << StorageTree()
                                << "()";

    QTest::newRow("single-root") << (StorageTree()
                                     .setRoot(StorageTreeNode("root")))
                                 << "(root)";

    QTest::newRow("level12-1") << (StorageTree(StorageTreeNode("root"))
                                   .addChild("root",StorageTreeNode("leaf1")))
                               << "(root(leaf1))";

    QTest::newRow("level2-2") << (StorageTree(StorageTreeNode("root"))
                                  .addChild("root", StorageTreeNode("node1"))
                                  .addChild("node1", StorageTreeNode("leaf1")))
                              << "(root(node1(leaf1)))";

    QTest::newRow("level-3") << (StorageTree(StorageTreeNode("root"))
                                 .addChild("root", StorageTreeNode("node1"))
                                 .addChild("node1", StorageTreeNode("leaf1"))
                                 .addChild("root", StorageTreeNode("node2"))
                                 .addChild("node2", StorageTreeNode("leaf2"))
                                 .addChild("node2", StorageTreeNode("leaf3")))
                             << "(root(node1(leaf1))(node2(leaf2)(leaf3)))";

}

void TStorageTree::TestToString()
{
    QFETCH(StorageTree, tree);
    QFETCH(QString, sRecord);

    const QString actual = tree.toString();
    QCOMPARE(actual, sRecord);
}

void TStorageTree::TestIsLeaf_data()
{
    QTest::addColumn<StorageTree>("tree");
    QTest::addColumn<QString>("node");
    QTest::addColumn<bool>("expected");

    QTest::newRow("empty-tree") << StorageTree()
                                << ""
                                << true;

    QTest::newRow("single-root") << (StorageTree()
                                     .setRoot(StorageTreeNode("root")))
                                 << "root"
                                 << true;

    QTest::newRow("level12-1") << (StorageTree(StorageTreeNode("root"))
                                   .addChild("root",StorageTreeNode("leaf1")))
                               << "leaf1"
                               << true;

    QTest::newRow("level12-2") << (StorageTree(StorageTreeNode("root"))
                                   .addChild("root",StorageTreeNode("leaf1")))
                               << "root"
                               << false;

    QTest::newRow("level2-3") << (StorageTree(StorageTreeNode("root"))
                                  .addChild("root", StorageTreeNode("node1"))
                                  .addChild("node1", StorageTreeNode("leaf1")))
                              << "root"
                              << false;

    QTest::newRow("level2-4") << (StorageTree(StorageTreeNode("root"))
                                  .addChild("root", StorageTreeNode("node1"))
                                  .addChild("node1", StorageTreeNode("leaf1")))
                              << "node1"
                              << false;

    QTest::newRow("level3-1") << (StorageTree(StorageTreeNode("root"))
                                  .addChild("root", StorageTreeNode("node1"))
                                  .addChild("node1", StorageTreeNode("leaf1"))
                                  .addChild("root", StorageTreeNode("node2"))
                                  .addChild("node2", StorageTreeNode("leaf2"))
                                  .addChild("node2", StorageTreeNode("leaf3")))
                              << "leaf2"
                              << true;

    QTest::newRow("level3-2") << (StorageTree(StorageTreeNode("root"))
                                  .addChild("root", StorageTreeNode("node1"))
                                  .addChild("node1", StorageTreeNode("leaf1"))
                                  .addChild("root", StorageTreeNode("node2"))
                                  .addChild("node2", StorageTreeNode("leaf2"))
                                  .addChild("node2", StorageTreeNode("leaf3")))
                              << "node2"
                              << false;



}
void TStorageTree::TestIsLeaf()
{
    QFETCH(StorageTree, tree);
    QFETCH(QString, node);
    QFETCH(bool, expected);

    const bool actual = (tree.isLeaf(node) == true);
    QCOMPARE(actual, expected);
}

void TStorageTree::TestIsBoolean_data()
{
    QTest::addColumn<StorageTree>("tree");
    QTest::addColumn<bool>("expected");

    QTest::newRow("empty-tree") << StorageTree()
                                << true;

    QTest::newRow("single-root") << (StorageTree()
                                     .setRoot(StorageTreeNode("root")))
                                 << true;

    QTest::newRow("level12-1") << (StorageTree(StorageTreeNode("root"))
                                   .addChild("root",StorageTreeNode("leaf1"))
                                   .addChild("root", StorageTreeNode("leaf2")))
                               << true;

    QTest::newRow("level12-2") << (StorageTree(StorageTreeNode("root"))
                                   .addChild("root",StorageTreeNode("leaf1")))
                               << false;

    QTest::newRow("level2-3") << (StorageTree(StorageTreeNode("root"))
                                  .addChild("root", StorageTreeNode("node1"))
                                  .addChild("node1", StorageTreeNode("leaf1"))
                                  .addChild("node1", StorageTreeNode("leaf2")))
                              << false;


    QTest::newRow("level3-1") << (StorageTree(StorageTreeNode("root"))
                                  .addChild("root", StorageTreeNode("node1"))
                                  .addChild("node1", StorageTreeNode("leaf1"))
                                  .addChild("root", StorageTreeNode("node2"))
                                  .addChild("node2", StorageTreeNode("leaf2"))
                                  .addChild("node2", StorageTreeNode("leaf3")))
                              << false;

}
void TStorageTree:: TestIsBoolean()
{
    QFETCH(StorageTree, tree);
    QFETCH(bool, expected);

    const bool actual = (tree.isBoolean());
    QCOMPARE(actual, expected);
}

void TStorageTree::TestIsBalanced_data()
{
    QTest::addColumn<StorageTree>("tree");
    QTest::addColumn<bool>("expected");

    QTest::newRow("empty-tree") << StorageTree()
                                << false;

    QTest::newRow("single-root") << (StorageTree(StorageTreeNode("root")))
                                 << false;

    QTest::newRow("level12-1") << (StorageTree(StorageTreeNode("root"))
                                   .addChild("root",StorageTreeNode("leaf1"))
                                   .addChild("root", StorageTreeNode("leaf2")))
                               << true;

   QTest::newRow("level12-2") << (StorageTree(StorageTreeNode("root"))
                                   .addChild("root",StorageTreeNode("leaf1")))
                               << true;

    QTest::newRow("level2-3") << (StorageTree(StorageTreeNode("root"))
                                  .addChild("root", StorageTreeNode("node1"))
                                  .addChild("node1", StorageTreeNode("leaf1"))
                                  .addChild("node1", StorageTreeNode("leaf2")))
                              << false;


    QTest::newRow("level3-1") << (StorageTree(StorageTreeNode("root"))
                                  .addChild("root", StorageTreeNode("node1"))
                                  .addChild("node1", StorageTreeNode("leaf1"))
                                  .addChild("root", StorageTreeNode("node2"))
                                  .addChild("node2", StorageTreeNode("leaf2"))
                                  .addChild("node2", StorageTreeNode("leaf3")))
                              << false;

}

void TStorageTree::TestIsBalanced()
{
    QFETCH(StorageTree, tree);
    QFETCH(bool, expected);

    const bool actual = (tree.isBalanced());
    QCOMPARE(actual, expected);

}

void TStorageTree::TestLeafs_data()
{
    QTest::addColumn<StorageTree>("tree");
    QTest::addColumn<QString>("node");
    QTest::addColumn<QStringList>("expected");

    QTest::newRow("empty-tree") << StorageTree()
                                <<""
                               << QStringList();

    QTest::newRow("single-root") << (StorageTree()
                                     .setRoot(StorageTreeNode("root")))
                                 <<"root"
                                << QStringList();

    QTest::newRow("level12-1") << (StorageTree(StorageTreeNode("root"))
                                   .addChild("root",StorageTreeNode("leaf1")))
                               << "root"
                               << (QStringList()<<"leaf1");

    QTest::newRow("level2-2") << (StorageTree(StorageTreeNode("root"))
                                  .addChild("root", StorageTreeNode("node1"))
                                  .addChild("node1", StorageTreeNode("leaf1")))
                              << "node1"
                              <<(QStringList()<<"leaf1");

    QTest::newRow("level2-3") << (StorageTree(StorageTreeNode("root"))
                                  .addChild("root", StorageTreeNode("node1"))
                                  .addChild("node1", StorageTreeNode("leaf1")))
                              << "leaf1"
                              <<QStringList();

    QTest::newRow("level3-1") << (StorageTree(StorageTreeNode("root"))
                                  .addChild("root", StorageTreeNode("node1"))
                                  .addChild("node1", StorageTreeNode("leaf1"))
                                  .addChild("root", StorageTreeNode("node2"))
                                  .addChild("node2", StorageTreeNode("leaf2"))
                                  .addChild("node2", StorageTreeNode("leaf3")))
                              << "node2"
                              << (QStringList() << "leaf2" << "leaf3");

    QTest::newRow("level3-2") << (StorageTree(StorageTreeNode("root"))
                                  .addChild("root", StorageTreeNode("node1"))
                                  .addChild("node1", StorageTreeNode("leaf1"))
                                  .addChild("root", StorageTreeNode("node2"))
                                  .addChild("node2", StorageTreeNode("leaf2"))
                                  .addChild("node2", StorageTreeNode("leaf3")))
                              << "node1"
                              << (QStringList() << "leaf1" );

    QTest::newRow("level3-3") << (StorageTree(StorageTreeNode("root"))
                                  .addChild("root", StorageTreeNode("node1"))
                                  .addChild("node1", StorageTreeNode("leaf1"))
                                  .addChild("root", StorageTreeNode("node2"))
                                  .addChild("node2", StorageTreeNode("leaf2"))
                                  .addChild("node2", StorageTreeNode("leaf3")))
                              << "root"
                              << (QStringList() << "leaf1" << "leaf2" << "leaf3" );



}

void TStorageTree::TestLeafs()
{
    QFETCH(StorageTree, tree);
    QFETCH(QString, node);
    QFETCH(QStringList, expected);

    const QStringList actual = tree.leafs(node);
    QCOMPARE(actual, expected);

}
