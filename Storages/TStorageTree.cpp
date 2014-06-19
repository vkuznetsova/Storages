#include "TStorageTree.h"
#include "StorageTreeNode.h"

TStorageTree::TStorageTree()
{
}

void TStorageTree::TestChildren_data()
{
    QTest::addColumn <StorageTree> ("tree");
    QTest::addColumn <QString> ("parent");
    QTest::addColumn <QStringList> ("children");

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

    QTest::newRow("two-leafs") << (StorageTree()
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

    const QStringList actual = tree.childrenIDs(parent);

    QCOMPARE(actual, children);
}

void TStorageTree::TestLevel_data()
{
    QTest::addColumn <StorageTree> ("tree");
    QTest::addColumn <QString> ("node");
    QTest::addColumn <int> ("level");

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

    QTest::newRow("level12-1") << (StorageTree(StorageTreeNode("root"))
                                   .addChild("root",StorageTreeNode("leaf1"))
                                   .addChild("root", StorageTreeNode("leaf2")))
                               << "leaf2"
                               << 2;

    QTest::newRow("level12-2") << (StorageTree(StorageTreeNode("root"))
                                   .addChild("root",StorageTreeNode("leaf1"))
                                   .addChild("root", StorageTreeNode("leaf2")))
                               << "leaf1"
                               << 2;
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
    QTest::addColumn <StorageTree> ("tree");
    QTest::addColumn <QString> ("child");
    QTest::addColumn <QString> ("t_parent");

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
    QTest::addColumn <StorageTree> ("tree");
    QTest::addColumn <QString> ("root");
    QTest::addColumn <StorageTree> ("sub_tree");

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
    QTest::addColumn <StorageTree> ("tree");
    QTest::addColumn <QString> ("sRecord");

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
    QTest::addColumn <StorageTree> ("tree");
    QTest::addColumn <QString> ("node");
    QTest::addColumn <bool> ("expected");

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
    QTest::addColumn <StorageTree> ("tree");
    QTest::addColumn <bool> ("expected");

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
    QTest::addColumn <StorageTree> ("tree");
    QTest::addColumn <bool> ("expected");

    QTest::newRow("empty-tree") << StorageTree()
                                << true;

    QTest::newRow("single-root") << (StorageTree(StorageTreeNode("root")))
                                 << true;

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
    QTest::addColumn <StorageTree> ("tree");
    QTest::addColumn <QString> ("node");
    QTest::addColumn <QStringList> ("expected");

    QTest::newRow("empty-tree") << StorageTree()
                                << ""
                                << QStringList();

    QTest::newRow("single-root") << (StorageTree()
                                     .setRoot(StorageTreeNode("root")))
                                 << "root"
                                 << QStringList();

    QTest::newRow("level12-1") << (StorageTree(StorageTreeNode("root"))
                                   .addChild("root",StorageTreeNode("leaf1")))
                               << "root"
                               << (QStringList()<<"leaf1");

    QTest::newRow("level2-2") << (StorageTree(StorageTreeNode("root"))
                                  .addChild("root", StorageTreeNode("node1"))
                                  .addChild("node1", StorageTreeNode("leaf1")))
                              << "node1"
                              << (QStringList()<<"leaf1");

    QTest::newRow("level2-3") << (StorageTree(StorageTreeNode("root"))
                                  .addChild("root", StorageTreeNode("node1"))
                                  .addChild("node1", StorageTreeNode("leaf1")))
                              << "leaf1"
                              << QStringList();

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

void TStorageTree::TestCheck_data()
{
    QTest::addColumn <StorageTree> ("tree");
    QTest::addColumn <int> ("size");
    QTest::addColumn <bool> ("expected");

    QTest::newRow("empty-tree") << StorageTree()
                                << 10
                                << true;

    QTest::newRow("single-root") << (StorageTree()
                                     .setRoot(StorageTreeNode("root")))
                                 << 3
                                 << false;

    QTest::newRow("single-root-1") << (StorageTree()
                                       .setRoot(StorageTreeNode("root-root-1")))
                                   << 10
                                   << false;

    QTest::newRow("level12-1") << (StorageTree(StorageTreeNode("root"))
                                   .addChild("root",StorageTreeNode("leaf1")))
                               << 5
                               << true;

    QTest::newRow("level2-2") << (StorageTree(StorageTreeNode("root"))
                                  .addChild("root", StorageTreeNode("node1"))
                                  .addChild("node1", StorageTreeNode("leaf1")))
                              << 2
                              << false;

    QTest::newRow("level2-2") << (StorageTree(StorageTreeNode("root"))
                                  .addChild("root", StorageTreeNode("node1-node1"))
                                  .addChild("node1-node1", StorageTreeNode("leaf1")))
                              << 5
                              << false;

}

void TStorageTree::TestCheck()
{
    QFETCH(StorageTree, tree);
    QFETCH(int, size);
    QFETCH(bool, expected);

    const bool actual = tree.idSize(size);
    QCOMPARE(actual, expected);

}

void TStorageTree::TestCheckMore_data()
{
    QTest::addColumn <StorageTree> ("tree");
    QTest::addColumn <int> ("count");
    QTest::addColumn <bool> ("expected");

    QTest::newRow("empty-tree") << StorageTree()
                                << 10
                                << false;

    QTest::newRow("single-root") << (StorageTree()
                                     .setRoot(StorageTreeNode("root")))
                                 << 0
                                 << false;

    QTest::newRow("level12-1") << (StorageTree(StorageTreeNode("root"))
                                   .addChild("root",StorageTreeNode("leaf1")))
                               << 1
                               << false;

    QTest::newRow("level2-2") << (StorageTree(StorageTreeNode("root"))
                                  .addChild("root", StorageTreeNode("node1"))
                                  .addChild("node1", StorageTreeNode("leaf1")))
                              << 2
                              << false;

    QTest::newRow("level2-1") << (StorageTree(StorageTreeNode("root"))
                                  .addChild("root", StorageTreeNode("node1"))
                                  .addChild("node1", StorageTreeNode("leaf1")))
                              << 5
                              << false;

    QTest::newRow("level2-2") << (StorageTree(StorageTreeNode("root"))
                                  .addChild("root", StorageTreeNode("node1"))
                                  .addChild("node1", StorageTreeNode("leaf1")))
                              << 0
                              << true;

    QTest::newRow("level3-3") << (StorageTree(StorageTreeNode("root"))
                                  .addChild("root", StorageTreeNode("node1"))
                                  .addChild("node1", StorageTreeNode("leaf1"))
                                  .addChild("root", StorageTreeNode("node2"))
                                  .addChild("node2", StorageTreeNode("leaf2"))
                                  .addChild("node2", StorageTreeNode("leaf3")))
                              << 1
                              << true;

}

void TStorageTree::TestCheckMore()
{
    QFETCH(StorageTree, tree);
    QFETCH(int, count);
    QFETCH(bool, expected);

    const bool actual = tree.moreNSuns(count);
    QCOMPARE(actual, expected);

}

void TStorageTree::TestNSuns_data()
{
    QTest::addColumn <StorageTree> ("tree");
    QTest::addColumn <int> ("count");
    QTest::addColumn <bool> ("expected");

    QTest::newRow("empty-tree") << StorageTree()
                                << 10
                                << false;

    QTest::newRow("single-root") << (StorageTree()
                                     .setRoot(StorageTreeNode("root")))
                                 << 0
                                 << true;

    QTest::newRow("level12-1") << (StorageTree(StorageTreeNode("root"))
                                   .addChild("root",StorageTreeNode("leaf1")))
                               << 1
                               << true;

    QTest::newRow("level2-2") << (StorageTree(StorageTreeNode("root"))
                                  .addChild("root", StorageTreeNode("node1"))
                                  .addChild("node1", StorageTreeNode("leaf1")))
                              << 2
                              << false;

    QTest::newRow("level2-1") << (StorageTree(StorageTreeNode("root"))
                                  .addChild("root", StorageTreeNode("node1"))
                                  .addChild("node1", StorageTreeNode("leaf1")))
                              << 5
                              << false;

    QTest::newRow("level2-2") << (StorageTree(StorageTreeNode("root"))
                                  .addChild("root", StorageTreeNode("node1"))
                                  .addChild("node1", StorageTreeNode("leaf1")))
                              << 1
                              << true;

    QTest::newRow("level3-3") << (StorageTree(StorageTreeNode("root"))
                                  .addChild("root", StorageTreeNode("node1"))
                                  .addChild("node1", StorageTreeNode("leaf1"))
                                  .addChild("root", StorageTreeNode("node2"))
                                  .addChild("node2", StorageTreeNode("leaf2"))
                                  .addChild("node2", StorageTreeNode("leaf3")))
                              << 1
                              << true;

    QTest::newRow("level3-4") << (StorageTree(StorageTreeNode("root"))
                                  .addChild("root", StorageTreeNode("node1"))
                                  .addChild("root", StorageTreeNode("node2"))
                                  .addChild("node1", StorageTreeNode("leaf1"))
                                  .addChild("node1", StorageTreeNode("leaf2"))
                                  .addChild("node2", StorageTreeNode("leaf3"))
                                  .addChild("node2", StorageTreeNode("leaf4")))
                              << 2
                              << true;
}

void TStorageTree::TestNSuns()
{
    QFETCH(StorageTree, tree);
    QFETCH(int, count);
    QFETCH(bool, expected);

    const bool actual = tree.nSuns(count);
    QCOMPARE(actual, expected);

}

void TStorageTree::TestRun_data()
{
    QTest::addColumn <StorageTree> ("tree");
    QTest::addColumn <StorageTree> ("expected");

    QTest::newRow("empty-tree") << StorageTree()
                                << StorageTree();

    QTest::newRow("single-root") << (StorageTree(StorageTreeNode("root", 0,
                                                                 7, 10)))
                                 << (StorageTree(StorageTreeNode("root", 0,
                                                                 7, 3)));

    QTest::newRow("level12-1") << (StorageTree(StorageTreeNode("root", 0,
                                                               4, 10)))
                                  .addChild("root",StorageTreeNode("leaf1",
                                                                   0, 4, 5 ))
                               << (StorageTree(StorageTreeNode("root", 0,
                                                               4, 6))
                                   .addChild("root",StorageTreeNode("leaf1",
                                                                    0,4, 1)));

    QTest::newRow("level2") << (StorageTree(StorageTreeNode("root", 0,
                                                            16, 7)))
                               .addChild("root",StorageTreeNode("leaf1",
                                                                0, 5, 5 ))
                               .addChild("root", StorageTreeNode("leaf2",
                                                                 0, 8, 1))
                            << (StorageTree(StorageTreeNode("root", 0,
                                                            16, -9)))
                               .addChild("root",StorageTreeNode("leaf1",
                                                                0,5, 0 ))
                               .addChild("root", StorageTreeNode("leaf2",
                                                                 0, 8, -7));

    QTest::newRow("level3") << (StorageTree(StorageTreeNode("root", 1, 3, 100)))
                               .addChild("root", StorageTreeNode("leaf1", 2, 1, 1))
                               .addChild("root", StorageTreeNode("leaf2", 2, 5, 10))
                               .addChild("leaf1", StorageTreeNode("leaf3", 3, 10, 5))
                               .addChild("leaf2", StorageTreeNode("leaf4", 3, 5, 5))
                               .addChild("leaf2", StorageTreeNode("leaf5", 3, 1, 0))
                            << (StorageTree(StorageTreeNode("root", 1, 3, 97)))
                               .addChild("root", StorageTreeNode("leaf1", 2, 1, 0))
                               .addChild("root", StorageTreeNode("leaf2", 2, 5, 5))
                               .addChild("leaf1", StorageTreeNode("leaf3", 3, 10, -5))
                               .addChild("leaf2", StorageTreeNode("leaf4", 3, 5, 0))
                               .addChild("leaf2", StorageTreeNode("leaf5", 3, 1, -1));
}

void TStorageTree::TestRun()
{
    QFETCH(StorageTree, tree);
    QFETCH(StorageTree, expected);

    const StorageTree actual = tree.run();
    QCOMPARE(actual, expected);
}

void TStorageTree::TestTotalSum_data()
{
    QTest::addColumn <StorageTree> ("tree");
    QTest::addColumn <int> ("expected");

    QTest::newRow("empty-tree") << StorageTree()
                                << 0;

    QTest::newRow("single-root") << (StorageTree(StorageTreeNode("root", 0,
                                                                 7, 10)))
                                 << 10;

    QTest::newRow("level12-1") << (StorageTree(StorageTreeNode("root", 0,
                                                               4, 10)))
                                  .addChild("root",StorageTreeNode("leaf1",
                                                                   0, 4, 5 ))
                               << 15;

    QTest::newRow("level2") << (StorageTree(StorageTreeNode("root", 0,
                                                            16, 7)))
                               .addChild("root",StorageTreeNode("leaf1",
                                                                0, 5, 5 ))
                               .addChild("root", StorageTreeNode("leaf2",
                                                                 0, 8, 1))
                            << 13;

    QTest::newRow("level3") << (StorageTree(StorageTreeNode("root", 1, 3, 100)))
                               .addChild("root", StorageTreeNode("leaf1", 2, 1, 1))
                               .addChild("root", StorageTreeNode("leaf2", 2, 5, 10))
                               .addChild("leaf1", StorageTreeNode("leaf3", 3, 10, 5))
                               .addChild("leaf2", StorageTreeNode("leaf4", 3, 5, 5))
                               .addChild("leaf2", StorageTreeNode("leaf5", 3, 1, 0))
                            << 121;


}

void TStorageTree::TestTotalSum()
{
    QFETCH(StorageTree, tree);
    QFETCH(int, expected);

    const int actual = tree.totalSum();
    QCOMPARE(actual, expected);
}

void TStorageTree::TestPositiveElemsSum_data()
{
    QTest::addColumn <StorageTree> ("tree");
    QTest::addColumn <int> ("expected");

    QTest::newRow("empty-tree") << StorageTree()
                                << 0;

    QTest::newRow("single-root") << (StorageTree(StorageTreeNode("root", 0,
                                                                 7, -10)))
                                 << 0;

    QTest::newRow("level12-1") << (StorageTree(StorageTreeNode("root", 0,
                                                               4, -10)))
                                  .addChild("root",StorageTreeNode("leaf1",
                                                                   0, 4, 5 ))
                               << 5;

    QTest::newRow("level2") << (StorageTree(StorageTreeNode("root", 0,
                                                            16, 7)))
                               .addChild("root",StorageTreeNode("leaf1",
                                                                0, 5, 5 ))
                               .addChild("root", StorageTreeNode("leaf2",
                                                                 0, 8, -1))
                            << 12;

    QTest::newRow("level3-1") << (StorageTree(StorageTreeNode("root", 1, 3, -100)))
                                 .addChild("root", StorageTreeNode("leaf1", 2, 1, -1))
                                 .addChild("root", StorageTreeNode("leaf2", 2, 5, 10))
                                 .addChild("leaf1", StorageTreeNode("leaf3", 3, 10, 5))
                                 .addChild("leaf2", StorageTreeNode("leaf4", 3, 5, 5))
                                 .addChild("leaf2", StorageTreeNode("leaf5", 3, 1, 0))
                              << 20;

    QTest::newRow("level3-2") << (StorageTree(StorageTreeNode("root", 1, 3, -100)))
                                 .addChild("root", StorageTreeNode("leaf1", 2, 1, -1))
                                 .addChild("root", StorageTreeNode("leaf2", 2, 5, -10))
                                 .addChild("leaf1", StorageTreeNode("leaf3", 3, 10, -5))
                                 .addChild("leaf2", StorageTreeNode("leaf4", 3, 5, -5))
                                 .addChild("leaf2", StorageTreeNode("leaf5", 3, 1, -0))
                              << 0;

    QTest::newRow("level3-3") << (StorageTree(StorageTreeNode("root", 1, 3, -100)))
                                 .addChild("root", StorageTreeNode("leaf1", 2, 1, -1))
                                 .addChild("root", StorageTreeNode("leaf2", 2, 5, -10))
                                 .addChild("leaf1", StorageTreeNode("leaf3", 3, 10, -5))
                                 .addChild("leaf2", StorageTreeNode("leaf4", 3, 5, -5))
                                 .addChild("leaf2", StorageTreeNode("leaf5", 3, 1, 50))
                              << 50;
}

void TStorageTree::TestPositiveElemsSum()
{
    QFETCH(StorageTree, tree);
    QFETCH(int, expected);

    const int actual = tree.PositiveElemsSum();
    QCOMPARE(actual, expected);

}

void TStorageTree::TestEuclidMetric_data()
{
    QTest::addColumn<StorageTree> ("tree");
    QTest::addColumn<int> ("expected");

    QTest::newRow("empty-tree") << StorageTree()
                                << 0;

    QTest::newRow("single-root") << (StorageTree(StorageTreeNode("root", 0,
                                                                 7, -10)))
                                 << 10;

    QTest::newRow("level12-1") << (StorageTree(StorageTreeNode("root", 0,
                                                               4, -10)))
                                  .addChild("root",StorageTreeNode("leaf1",
                                                                   0, 4, 5 ))
                               << 11;

    QTest::newRow("level2") << (StorageTree(StorageTreeNode("root", 0,
                                                            16, 7)))
                               .addChild("root",StorageTreeNode("leaf1",
                                                                0, 5, 5 ))
                               .addChild("root", StorageTreeNode("leaf2",
                                                                 0, 8, -1))
                            << 8;

    QTest::newRow("level3-1") << (StorageTree(StorageTreeNode("root", 1, 3, -10)))
                                 .addChild("root", StorageTreeNode("leaf1", 2, 1, -1))
                                 .addChild("root", StorageTreeNode("leaf2", 2, 5, 10))
                                 .addChild("leaf1", StorageTreeNode("leaf3", 3, 10, 5))
                                 .addChild("leaf2", StorageTreeNode("leaf4", 3, 5, 5))
                                 .addChild("leaf2", StorageTreeNode("leaf5", 3, 1, 0))
                              << 15;
}

void TStorageTree::TestEuclidMetric()
{
    QFETCH(StorageTree, tree);
    QFETCH(int, expected);

    const int actual = tree.euclidMetric();
    QCOMPARE(actual, expected);

}

void TStorageTree::TestAccumBalance_data()
{
    QTest::addColumn <StorageTree> ("tree");
    QTest::addColumn <StorageTree> ("expected");

    QTest::newRow("empty-tree") << StorageTree()
                                << StorageTree();

    QTest::newRow("single-root") << (StorageTree(StorageTreeNode("root", 0,
                                                                 7, -10)))
                                 << (StorageTree(StorageTreeNode("root", 0,
                                                                 7, -10)));

    QTest::newRow("level12-1") << (StorageTree(StorageTreeNode("root", 0,
                                                               4, -10)))
                                  .addChild("root",StorageTreeNode("leaf1",
                                                                   0, 4, 5 ))
                               << (StorageTree(StorageTreeNode("root", 0,
                                                               4, -5)))
                                  .addChild("root",StorageTreeNode("leaf1",
                                                                   0, 4, 5 ));

    QTest::newRow("level2") << (StorageTree(StorageTreeNode("root", 0,
                                                            16, 7)))
                               .addChild("root",StorageTreeNode("leaf1",
                                                                0, 5, 5 ))
                               .addChild("root", StorageTreeNode("leaf2",
                                                                 0, 8, -1))
                            << (StorageTree(StorageTreeNode("root", 0,
                                                            16, 11)))
                               .addChild("root",StorageTreeNode("leaf1",
                                                                0, 5, 5 ))
                               .addChild("root", StorageTreeNode("leaf2",
                                                                 0, 8, -1));

    QTest::newRow("level3-1") << (StorageTree(StorageTreeNode("root", 1, 3, -100)))
                                 .addChild("root", StorageTreeNode("leaf1", 2, 1, -1))
                                 .addChild("root", StorageTreeNode("leaf2", 2, 5, 10))
                                 .addChild("leaf1", StorageTreeNode("leaf3", 3, 10, 5))
                                 .addChild("leaf2", StorageTreeNode("leaf4", 3, 5, 5))
                                 .addChild("leaf2", StorageTreeNode("leaf5", 3, 1, 0))
                              << (StorageTree(StorageTreeNode("root", 1, 3, -81)))
                                 .addChild("root", StorageTreeNode("leaf1", 2, 1, 4))
                                 .addChild("root", StorageTreeNode("leaf2", 2, 5, 15))
                                 .addChild("leaf1", StorageTreeNode("leaf3", 3, 10, 5))
                                 .addChild("leaf2", StorageTreeNode("leaf4", 3, 5, 5))
                                 .addChild("leaf2", StorageTreeNode("leaf5", 3, 1, 0));
}

void TStorageTree::TestAccumBalance()
{
    QFETCH(StorageTree, tree);
    QFETCH(StorageTree, expected);

    const StorageTree actual = tree.accumBalance();
    QCOMPARE(actual, expected);
}

void TStorageTree::TestGenerateTree_data()
{
    QTest::addColumn <int> ("level");
    QTest::addColumn <StorageTree> ("expected");

    QTest::newRow("empty-tree") << 0
                                << StorageTree();

    QTest::newRow("single-root") << 1
                                 << (StorageTree(StorageTreeNode("root")));


    QTest::newRow("level2-2") << 2
                              << (StorageTree(StorageTreeNode("root"))
                                  .addChild("root", StorageTreeNode("leaf1"))
                                  .addChild("root", StorageTreeNode("leaf2")));

    QTest::newRow("level3-1") << 3
                              << (StorageTree(StorageTreeNode("root"))
                                  .addChild("root", StorageTreeNode("leaf1"))
                                  .addChild("root", StorageTreeNode("leaf2"))
                                  .addChild("leaf1", StorageTreeNode("leaf3"))
                                  .addChild("leaf1", StorageTreeNode("leaf4"))
                                  .addChild("leaf2", StorageTreeNode("leaf5"))
                                  .addChild("leaf2", StorageTreeNode("leaf6")));

    QTest::newRow("level4") << 4
                            << (StorageTree(StorageTreeNode("root"))
                                .addChild("root", StorageTreeNode("leaf1"))
                                .addChild("root", StorageTreeNode("leaf2"))
                                .addChild("leaf1", StorageTreeNode("leaf3"))
                                .addChild("leaf1", StorageTreeNode("leaf4"))
                                .addChild("leaf2", StorageTreeNode("leaf9"))
                                .addChild("leaf2", StorageTreeNode("leaf10"))
                                .addChild("leaf3", StorageTreeNode("leaf5"))
                                .addChild("leaf3", StorageTreeNode("leaf6"))
                                .addChild("leaf4", StorageTreeNode("leaf7"))
                                .addChild("leaf4", StorageTreeNode("leaf8"))
                                .addChild("leaf9", StorageTreeNode("leaf11"))
                                .addChild("leaf9", StorageTreeNode("leaf12"))
                                .addChild("leaf10", StorageTreeNode("leaf13"))
                                .addChild("leaf10", StorageTreeNode("leaf14")));
}

void TStorageTree::TestGenerateTree()
{
    QFETCH(int, level);
    QFETCH(StorageTree, expected);

    const StorageTree actual = StorageTree::generateTree(level);
    QCOMPARE(actual, expected);

}

void TStorageTree::TestNodeForNum_data()
{
    QTest::addColumn <StorageTree> ("tree");
    QTest::addColumn <int> ("num");
    QTest::addColumn <QString> ("expected");

    QTest::newRow("empty-tree")<< StorageTree()
                               << 0
                               << "";

    QTest::newRow("single-root")<< StorageTree(StorageTreeNode("root"))
                                << 1
                                << "root";

    QTest::newRow("level12-1") << (StorageTree(StorageTreeNode("root"))
                                   .addChild("root", StorageTreeNode("leaf1")))
                               << 1
                               << "root";

    QTest::newRow("level12-2") << (StorageTree(StorageTreeNode("root"))
                                   .addChild("root", StorageTreeNode("leaf1")))
                               << 2
                               << "leaf1";

    QTest::newRow("level3-1") << (StorageTree(StorageTreeNode("root"))
                                  .addChild("root", StorageTreeNode("node1"))
                                  .addChild("node1", StorageTreeNode("leaf1"))
                                  .addChild("root", StorageTreeNode("node2"))
                                  .addChild("node2", StorageTreeNode("leaf2"))
                                  .addChild("node2", StorageTreeNode("leaf3")))
                              << 2
                              << "node1";

    QTest::newRow("level3-2") << (StorageTree(StorageTreeNode("root"))
                                  .addChild("root", StorageTreeNode("node1"))
                                  .addChild("node1", StorageTreeNode("leaf1"))
                                  .addChild("root", StorageTreeNode("node2"))
                                  .addChild("node2", StorageTreeNode("leaf2"))
                                  .addChild("node2", StorageTreeNode("leaf3")))
                              << 3
                              << "leaf1";

    QTest::newRow("level3-3") << (StorageTree(StorageTreeNode("root"))
                                  .addChild("root", StorageTreeNode("node1"))
                                  .addChild("node1", StorageTreeNode("leaf1"))
                                  .addChild("root", StorageTreeNode("node2"))
                                  .addChild("node2", StorageTreeNode("leaf2"))
                                  .addChild("node2", StorageTreeNode("leaf3")))
                              << 4
                              << "node2";

    QTest::newRow("level3-4") << (StorageTree(StorageTreeNode("root"))
                                  .addChild("root", StorageTreeNode("node1"))
                                  .addChild("node1", StorageTreeNode("leaf1"))
                                  .addChild("root", StorageTreeNode("node2"))
                                  .addChild("node2", StorageTreeNode("leaf2"))
                                  .addChild("node2", StorageTreeNode("leaf3")))
                              << 6
                              << "leaf3";

    QTest::newRow("level3-5") << (StorageTree(StorageTreeNode("root"))
                                  .addChild("root", StorageTreeNode("node1"))
                                  .addChild("node1", StorageTreeNode("leaf1"))
                                  .addChild("root", StorageTreeNode("node2"))
                                  .addChild("node2", StorageTreeNode("leaf2"))
                                  .addChild("node2", StorageTreeNode("leaf3")))
                              << 1
                              << "root";
}

void TStorageTree::TestNodeForNum()
{
    QFETCH(StorageTree, tree);
    QFETCH(int, num);
    QFETCH(QString, expected);

    const QString actual = tree.nodeForNum(num);
    QCOMPARE(actual, expected);
}

void TStorageTree::TestOrder_data()
{
    QTest::addColumn <StorageTree> ("tree");
    QTest::addColumn <QStringList> ("nodes");

    QTest::newRow("empty-tree") << StorageTree()
                                << QStringList();

    QTest::newRow("single-root") << (StorageTree()
                                     .setRoot(StorageTreeNode("root")))
                                 << (QStringList() << "root");

    QTest::newRow("single-root") << (StorageTree()
                                     .setRoot(StorageTreeNode("root"))
                                     .addChild("root", StorageTreeNode("node1"))
                                     .addChild("root", StorageTreeNode("node2"))
                                     .addChild("node1", StorageTreeNode("leaf1"))
                                     .addChild("node1", StorageTreeNode("leaf2"))
                                     .addChild("node2", StorageTreeNode("leaf3")))
                                 << (QStringList() << "root"
                                     << "node1"
                                     << "leaf1"
                                     << "leaf2"
                                     << "node2"
                                     << "leaf3");
}

void TStorageTree::TestOrder()
{
    QFETCH(StorageTree, tree);
    QFETCH(QStringList, nodes);

    QCOMPARE(tree.order(), nodes);
}

void TStorageTree::TestRemoveNode_data()
{
    QTest::addColumn <StorageTree> ("tree");
    QTest::addColumn <QString> ("node");
    QTest::addColumn <StorageTree> ("expected");

    QTest::newRow("empty-tree") << StorageTree()
                                << QString()
                                << StorageTree();

    QTest::newRow("single-root") << StorageTree().setRoot(StorageTreeNode("root"))
                                 << "root"
                                 << StorageTree();

    QTest::newRow("level2-1") << (StorageTree(StorageTreeNode("root"))
                                  .addChild("root", "node1"))
                              << "node1"
                              << StorageTree(StorageTreeNode("root"));

    QTest::newRow("level2-2") << (StorageTree(StorageTreeNode("root"))
                                  .addChild("root", "node1"))
                              << "root"
                              << StorageTree();

    QTest::newRow("level3-1") << (StorageTree(StorageTreeNode("root"))
                                  .addChild("root", "node1")
                                  .addChild("node1", "leaf1"))
                              << "node1"
                              << StorageTree(StorageTreeNode("root"));

    QTest::newRow("single-root")<<StorageTree(StorageTreeNode("root"))
                               << "root"
                               << StorageTree();

    QTest::newRow("level2-1") << (StorageTree(StorageTreeNode("root"))
                                  .addChild("root", StorageTreeNode("node1")))
                              << "node1"
                              << StorageTree(StorageTreeNode("root"));

    QTest::newRow("level2-2") << (StorageTree(StorageTreeNode("root"))
                                  .addChild("root", StorageTreeNode("node1")))
                              << "root"
                              << StorageTree();

    QTest::newRow("level3-1") << (StorageTree(StorageTreeNode("root"))
                                  .addChild("root", StorageTreeNode("node1"))
                                  .addChild("node1", StorageTreeNode("leaf1")))
                              << "node1"
                              << StorageTree(StorageTreeNode("root"));

    QTest::newRow("level3-2") << (StorageTree(StorageTreeNode("root"))
                                  .addChild("root", StorageTreeNode("node1"))
                                  .addChild("node1", StorageTreeNode("leaf1")))
                              << "leaf1"
                              << (StorageTree(StorageTreeNode("root"))
                                  .addChild("root", "node1"));

    QTest::newRow("level4") << (StorageTree(StorageTreeNode("root"))
                                .addChild("root", "node1")
                                .addChild("node1","leaf1")
                                .addChild("root", "node2")
                                .addChild("node2","leaf2")
                                .addChild("node2", "leaf3"))
                            << "node2"
                            << (StorageTree(StorageTreeNode("root"))
                                .addChild("root","node1")
                                .addChild("node1", "leaf1"));

    QTest::newRow("level5") << (StorageTree(StorageTreeNode("root"))
                                .addChild("root", "leaf1")
                                .addChild("root", "leaf2")
                                .addChild("leaf1", "leaf3")
                                .addChild("leaf2", "leaf4")
                                .addChild("leaf2", "leaf5"))
                            << "leaf2"
                            << (StorageTree(StorageTreeNode("root"))
                                .addChild("root", "leaf1")
                                .addChild("leaf1", "leaf3"));

    QTest::newRow("level4") << (StorageTree(StorageTreeNode("root"))
                                .addChild("root", StorageTreeNode("node1"))
                                .addChild("node1", StorageTreeNode("leaf1"))
                                .addChild("root", StorageTreeNode("node2"))
                                .addChild("node2", StorageTreeNode("leaf2"))
                                .addChild("node2", StorageTreeNode("leaf3")))
                            << "node2"
                            << (StorageTree(StorageTreeNode("root"))
                                .addChild("root", StorageTreeNode("node1"))
                                .addChild("node1", StorageTreeNode("leaf1")));

    QTest::newRow("level5") << (StorageTree(StorageTreeNode("root"))
                                .addChild("root", StorageTreeNode("leaf1"))
                                .addChild("root", StorageTreeNode("leaf2"))
                                .addChild("leaf1", StorageTreeNode("leaf3"))
                                .addChild("leaf2", StorageTreeNode("leaf4"))
                                .addChild("leaf2", StorageTreeNode("leaf5")))
                            << "leaf2"
                            << (StorageTree(StorageTreeNode("root"))
                                .addChild("root", StorageTreeNode("leaf1"))
                                .addChild("leaf1", StorageTreeNode("leaf3")));
}

void TStorageTree::TestRemoveNode()
{
    QFETCH(StorageTree, tree);
    QFETCH(QString, node);
    QFETCH(StorageTree, expected);

    tree.removeNode(node);

    QCOMPARE(tree, expected);
}

void TStorageTree::TestAutoSetRoot_data()
{
    QTest::addColumn <StorageTree> ("tree");
    QTest::addColumn <StorageTree> ("expected");

    QTest::newRow("empty-tree") << StorageTree()
                                << StorageTree();

    QTest::newRow("single-root") << (StorageTree()
                                     .addChild(QString(), "root"))
                                 << (StorageTree(StorageTreeNode("root")));

    QTest::newRow("level2") << (StorageTree()
                                .addChild(QString(), "root")
                                .addChild("root", "node1"))
                            << (StorageTree(StorageTreeNode("root"))
                                .addChild("root", ("node1")));

    QTest::newRow("level3") << (StorageTree()
                                .addChild(QString(), "root")
                                .addChild("root", ("node1"))
                                .addChild("node1", ("leaf1")))
                            << (StorageTree(StorageTreeNode("root"))
                                .addChild("root", ("node1"))
                                .addChild("node1", ("leaf1")));

    QTest::newRow("level4") << (StorageTree()
                                .addChild(QString(), "root")
                                .addChild("root", ("node1"))
                                .addChild("node1", ("leaf1"))
                                .addChild("root", ("node2"))
                                .addChild("node2", ("leaf2"))
                                .addChild("node2", ("leaf3")))
                            << (StorageTree(StorageTreeNode("root"))
                                .addChild("root", ("node1"))
                                .addChild("node1", ("leaf1"))
                                .addChild("root", ("node2"))
                                .addChild("node2", ("leaf2"))
                                .addChild("node2", ("leaf3")));

    QTest::newRow("level5") << (StorageTree()
                                .addChild(QString(), "root")
                                .addChild("root", ("leaf1"))
                                .addChild("root", ("leaf2"))
                                .addChild("leaf1", ("leaf3"))
                                .addChild("leaf2", ("leaf4"))
                                .addChild("leaf2", ("leaf5")))
                            << (StorageTree(StorageTreeNode("root"))
                                .addChild("root", ("leaf1"))
                                .addChild("root", ("leaf2"))
                                .addChild("leaf1", ("leaf3"))
                                .addChild("leaf2", ("leaf4"))
                                .addChild("leaf2", ("leaf5")));

}

void TStorageTree::TestAutoSetRoot()
{
    QFETCH(StorageTree, tree);
    QFETCH(StorageTree, expected);

    tree.autoSetRoot();

    QCOMPARE(tree, expected);

}

void TStorageTree::TestAutoSetLevel_data()
{
    QTest::addColumn <StorageTree> ("tree");
    QTest::addColumn <StorageTree> ("expected");

    QTest::newRow("empty-tree") << StorageTree()
                                << StorageTree();

    QTest::newRow("single-root") << (StorageTree().setRoot("root"))
                                 << (StorageTree(StorageTreeNode("root"))).setLevel("root", 1);

    QTest::newRow("level2") << (StorageTree()
                                .setRoot("root")
                                .addChild("root", "node1"))
                            << (StorageTree().setRoot("root")
                                .addChild("root", "node1"))
                               .setLevel("root", 1)
                               .setLevel("node1", 2);

    QTest::newRow("level3") << (StorageTree().setRoot("root")
                                .addChild("root", ("node1"))
                                .addChild("node1", ("leaf1")))
                            << (StorageTree().setRoot("root")
                                .addChild("root", "node1")
                                .addChild("node1", "leaf1"))
                               .setLevel("root", 1)
                               .setLevel("node1", 2)
                               .setLevel("leaf1", 3);

    QTest::newRow("level4") << (StorageTree().setRoot("root")
                                .addChild("root", "node1")
                                .addChild("node1", "leaf1")
                                .addChild("root", "node2")
                                .addChild("node2", "leaf2")
                                .addChild("node2", "leaf3"))
                            << (StorageTree().setRoot("root")
                                .addChild("root", "node1")
                                .addChild("node1", "leaf1")
                                .addChild("root", "node2")
                                .addChild("node2", "leaf2")
                                .addChild("node2", "leaf3"))
                               .setLevel("root", 1)
                               .setLevel("node1", 2)
                               .setLevel("leaf1", 3)
                               .setLevel("node2", 2)
                               .setLevel("leaf2", 3)
                               .setLevel("leaf3", 3);

    QTest::newRow("level5") << (StorageTree().setRoot("root")
                                .addChild("root", "leaf1")
                                .addChild("root", "leaf2")
                                .addChild("leaf1", "leaf3")
                                .addChild("leaf2", "leaf4")
                                .addChild("leaf2", "leaf5"))
                            << (StorageTree().setRoot("root")
                                .addChild("root", "leaf1")
                                .addChild("root", "leaf2")
                                .addChild("leaf1", "leaf3")
                                .addChild("leaf2", "leaf4")
                                .addChild("leaf2", "leaf5"))
                               .setLevel("root", 1)
                               .setLevel("leaf1", 2)
                               .setLevel("leaf2", 2)
                               .setLevel("leaf3", 3)
                               .setLevel("leaf4", 3)
                               .setLevel("leaf5", 3);

    QTest::newRow("order2") << (StorageTree())
                               .addChild("root", "node1")
                               .addChild(QString(), "root")
                            << (StorageTree().setRoot("root"))
                               .addChild("root", "node1")
                               .addChild(QString(), "root")
                               .setLevel("root", 1)
                               .setLevel("node1", 2);
}

void TStorageTree::TestAutoSetLevel()
{
    QFETCH(StorageTree, tree);
    QFETCH(StorageTree, expected);

    tree.autoSetRoot();
    tree.autoSetLevel();

    QCOMPARE(tree, expected);

}

void TStorageTree::TestAutoSetLeaf_data()
{
    QTest::addColumn <StorageTree> ("tree");
    QTest::addColumn <StorageTree> ("expected");

    QTest::newRow("empty-tree") << StorageTree()
                                << StorageTree();

    QTest::newRow("single-root") << (StorageTree().setRoot("root"))
                                 << (StorageTree(StorageTreeNode("root")))
                                    .setLeaf("root", true);

    QTest::newRow("level2") << (StorageTree()
                                .setRoot("root")
                                .addChild("root", "node1"))
                            << (StorageTree(StorageTreeNode("root", 1))
                                .addChild("root", "node1"))
                               .setLeaf("root", false)
                               .setLeaf("node1", true);

    QTest::newRow("level3") << (StorageTree().setRoot("root")
                                .addChild("root", ("node1"))
                                .addChild("node1", ("leaf1")))
                            << (StorageTree().setRoot("root")
                                .addChild("root", "node1")
                                .addChild("node1", "leaf1"))
                               .setLeaf("root", false)
                               .setLeaf("node1", false)
                               .setLeaf("leaf1", true);

    QTest::newRow("level4") << (StorageTree().setRoot("root")
                                .addChild("root", "node1")
                                .addChild("node1", "leaf1")
                                .addChild("root", "node2")
                                .addChild("node2", "leaf2")
                                .addChild("node2", "leaf3"))
                            << (StorageTree().setRoot("root")
                                .addChild("root", "node1")
                                .addChild("node1", "leaf1")
                                .addChild("root", "node2")
                                .addChild("node2", "leaf2")
                                .addChild("node2", "leaf3"))
                               .setLeaf("root", false)
                               .setLeaf("node1", false)
                               .setLeaf("leaf1", true)
                               .setLeaf("node2", false)
                               .setLeaf("leaf3", true)
                               .setLeaf("leaf2", true);

    QTest::newRow("level5") << (StorageTree().setRoot("root")
                                .addChild("root", "leaf1")
                                .addChild("root", "leaf2")
                                .addChild("leaf1", "leaf3")
                                .addChild("leaf2", "leaf4")
                                .addChild("leaf2", "leaf5"))
                            << (StorageTree().setRoot("root")
                                .addChild("root", "leaf1")
                                .addChild("root", "leaf2")
                                .addChild("leaf1", "leaf3")
                                .addChild("leaf2", "leaf4")
                                .addChild("leaf2", "leaf5"))
                               .setLeaf("root", false)
                               .setLeaf("leaf1", false)
                               .setLeaf("leaf2", false)
                               .setLeaf("leaf3", true)
                               .setLeaf("leaf4", true)
                               .setLeaf("leaf5", true);

}

void TStorageTree::TestAutoSetLeaf()
{
    QFETCH(StorageTree, tree);
    QFETCH(StorageTree, expected);

    tree.autoSetLeaf();

    QCOMPARE(tree, expected);

}

void TStorageTree::TestAddChild_data()
{
    QTest::addColumn <StorageTree> ("tree");
    QTest::addColumn <QString> ("parent1");
    QTest::addColumn <QString> ("child1");
    QTest::addColumn <QString> ("parent2");
    QTest::addColumn <QString> ("child2");
    QTest::addColumn <StorageTree> ("expected");

    QTest::newRow("order1") << StorageTree()
                            << QString()
                            << "root"
                            << "root"
                            << "node1"
                            << (StorageTree().setRoot("root"))
                               .addChild(QString(), "root")
                               .addChild("root", "node1");

    QTest::newRow("order2") << StorageTree()
                            << "root"
                            << "node1"
                            << QString()
                            << "root"
                            << (StorageTree().setRoot("root"))
                               .addChild(QString(), "root")
                               .addChild("root", "node1");
}

void TStorageTree::TestAddChild()
{
    QFETCH(StorageTree, tree);
    QFETCH(QString, parent1);
    QFETCH(QString, child1);
    QFETCH(QString, parent2);
    QFETCH(QString, child2);
    QFETCH(StorageTree, expected);

    tree.addChild(parent1, child1);
    tree.addChild(parent2, child2);
    tree.autoSetRoot();
    tree.autoSetLevel();

    QCOMPARE(tree, expected);
}

void TStorageTree::TestNodesToJSONArray_data()
{
    QTest::addColumn <StorageTree> ("tree");
    QTest::addColumn <QJsonArray> ("expected");

    QTest::newRow("empty-tree") << StorageTree()
                                << QJsonArray();

    QJsonObject json1;
    json1.insert("id" + QString(":"), QString("root"));
    json1.insert("balance" + QString(":"), -10);
    json1.insert("expense" + QString(":"), 5);
    QJsonArray array;
    array.append(QJsonValue(json1));

    QTest::newRow("single-root") << (StorageTree("first")
                                     .setRoot("root"))
                                    .setBalance("root", -10)
                                    .setExpense("root", 5)
                                 << array;

    QJsonObject json;
    json.insert("id" + QString(":"), QString("root"));
    json.insert("balance" + QString(":"), -10);
    json.insert("expense" + QString(":"), 5);
    QJsonObject json11;
    json11.insert("id" + QString(":"), QString("node1"));
    json11.insert("balance" + QString(":"), 0);
    json11.insert("expense" + QString(":"), 10);
    QJsonArray array1;
    array1.append(QJsonValue(json));
    array1.append(QJsonValue(json11));

    QTest::newRow("level2") << (StorageTree("second")
                                .setRoot("root"))
                               .addChild("root", "node1")
                               .setBalance("root", -10)
                               .setExpense("root", 5)
                               .setBalance("node1", 0)
                               .setExpense("node1", 10)
                            << array1;

    QJsonObject json211;
    json211.insert("id" + QString(":"), QString("root"));
    json211.insert("balance" + QString(":"), -10);
    json211.insert("expense" + QString(":"), 5);
    QJsonObject json212;
    json212.insert("id" + QString(":"), QString("node1"));
    json212.insert("balance" + QString(":"), 0);
    json212.insert("expense" + QString(":"), 10);
    QJsonObject json213;
    json213.insert("id" + QString(":"), QString("node2"));
    json213.insert("balance" + QString(":"), 50);
    json213.insert("expense" + QString(":"), 50);
    QJsonArray array2;
    array2.append(QJsonValue(json211));
    array2.append(QJsonValue(json212));
    array2.append(QJsonValue(json213));

    QTest::newRow("level2-1") << (StorageTree("second1")
                                  .setRoot("root"))
                                 .addChild("root", "node1")
                                 .addChild("root", "node2")
                                 .setBalance("root", -10)
                                 .setExpense("root", 5)
                                 .setBalance("node1", 0)
                                 .setExpense("node1", 10)
                                 .setBalance("node2", 50)
                                 .setExpense("node2", 50)
                              << array2;

    QJsonObject json311;
    json311.insert("id" + QString(":"), QString("root"));
    json311.insert("balance" + QString(":"), -10);
    json311.insert("expense" + QString(":"), 5);
    QJsonObject json312;
    json312.insert("id" + QString(":"), QString("node1"));
    json312.insert("balance" + QString(":"), 0);
    json312.insert("expense" + QString(":"), 10);
    QJsonObject json313;
    json313.insert("id" + QString(":"), QString("node2"));
    json313.insert("balance" + QString(":"), 50);
    json313.insert("expense" + QString(":"), 50);
    QJsonObject json314;
    json314.insert("id" + QString(":"), QString("leaf1"));
    json314.insert("balance" + QString(":"), 1);
    json314.insert("expense" + QString(":"), 500);
    QJsonArray array3;
    array3.append(QJsonValue(json311));
    array3.append(QJsonValue(json312));
    array3.append(QJsonValue(json313));
    array3.append(QJsonValue(json314));

    QTest::newRow("level3") << (StorageTree("third")
                                .setRoot("root"))
                               .addChild("root", "node1")
                               .addChild("root", "node2")
                               .addChild("node1", "leaf1")
                               .setBalance("root", -10)
                               .setExpense("root", 5)
                               .setBalance("node1", 0)
                               .setExpense("node1", 10)
                               .setBalance("node2", 50)
                               .setExpense("node2", 50)
                               .setBalance("leaf1", 1)
                               .setExpense("leaf1", 500)
                            << array3;


    QJsonObject json315;
    json315.insert("id" + QString(":"), QString("leaf2"));
    json315.insert("balance" + QString(":"), 10);
    json315.insert("expense" + QString(":"), 500);
    QJsonArray array31;
    array31.append(QJsonValue(json311));
    array31.append(QJsonValue(json312));
    array31.append(QJsonValue(json313));
    array31.append(QJsonValue(json314));
    array31.append(QJsonValue(json315));

    QTest::newRow("level3-1") << (StorageTree("third")
                                  .setRoot("root"))
                                 .addChild("root", "node1")
                                 .addChild("root", "node2")
                                 .addChild("node1", "leaf1")
                                 .addChild("node1", "leaf2")
                                 .setBalance("root", -10)
                                 .setExpense("root", 5)
                                 .setBalance("node1", 0)
                                 .setExpense("node1", 10)
                                 .setBalance("node2", 50)
                                 .setExpense("node2", 50)
                                 .setBalance("leaf1", 1)
                                 .setExpense("leaf1", 500)
                                 .setBalance("leaf2", 10)
                                 .setExpense("leaf2", 500)
                              << array31;

}

void TStorageTree::TestNodesToJSONArray()
{
    QFETCH(StorageTree, tree);
    QFETCH(QJsonArray, expected);

    const QJsonArray actual = tree.nodesToJSONArray();

    QCOMPARE(actual, expected);

}

void TStorageTree::TestEdgeToJSON_data()
{
    QTest::addColumn <StorageTree> ("tree");
    QTest::addColumn <QString> ("parent");
    QTest::addColumn <QString> ("child");
    QTest::addColumn <QJsonObject> ("expected");

    QJsonObject jsonInner;
    jsonInner.insert("from" + QString(":"), QString());
    jsonInner.insert("to" + QString(":"), QString());
    QTest::newRow("empty-tree") << StorageTree("id0")
                                << QString()
                                << QString()
                                << jsonInner;

    QJsonObject jsonInner1;
    jsonInner1.insert("from" + QString(":"), QString("root"));
    jsonInner1.insert("to" + QString(":"), QString());
    QTest::newRow("single-root") << StorageTree("id1")
                                   .setRoot("root")
                                << "root"
                                << QString()
                                << jsonInner1;

    QJsonObject jsonInner12;
    jsonInner12.insert("from" + QString(":"), QString("root"));
    jsonInner12.insert("to" + QString(":"), QString("node1"));
    QTest::newRow("level2") << (StorageTree("second")
                                .setRoot("root"))
                               .addChild("root", "node1")
                             << "root"
                             << "node1"
                             << jsonInner12;

    QJsonObject jsonInner121;
    jsonInner121.insert("from" + QString(":"), QString("root"));
    jsonInner121.insert("to" + QString(":"), QString("node2"));
    QTest::newRow("level2-1") << (StorageTree("second")
                                .setRoot("root"))
                               .addChild("root", "node1")
                                .addChild("root", "node2")
                             << "root"
                             << "node2"
                             << jsonInner121;

}

void TStorageTree::TestEdgeToJSON()
{
    QFETCH(StorageTree, tree);
    QFETCH(QString, parent);
    QFETCH(QString, child);
    QFETCH(QJsonObject, expected);

    const QJsonObject actual = tree.edgeToJSON(parent, child);

    QCOMPARE(actual, expected);

}

void TStorageTree::TestEdgesToJSONArray_data()
{
    QTest::addColumn <StorageTree> ("tree");
    QTest::addColumn <QJsonArray> ("expected");

    QJsonObject json;
    json.insert("from" + QString(":"), QString());
    json.insert("to" + QString(":"), QString());
    QJsonArray array;
    array.append(QJsonValue(json));
    QTest::newRow("empty-tree") << StorageTree()
                                << array;

    QJsonObject json1;
    json1.insert("from" + QString(":"), QString("root"));
    json1.insert("to" + QString(":"), QString());
    QJsonArray array1;
    array1.append(QJsonValue(json1));
    QTest::newRow("single-root") << StorageTree().setRoot("root")
                                << array1;

    QJsonObject json2;
    json2.insert("from" + QString(":"), QString("root"));
    json2.insert("to" + QString(":"), QString("node1"));
    QJsonArray array2;
    array2.append(QJsonValue(json2));
    QTest::newRow("level2") << (StorageTree("second")
                                .setRoot("root"))
                               .addChild("root", "node1")
                             << array2;

    QJsonObject json21;
    json21.insert("from" + QString(":"), QString("root"));
    json21.insert("to" + QString(":"), QString("node1"));
    QJsonObject json211;
    json211.insert("from" + QString(":"), QString("root"));
    json211.insert("to" + QString(":"), QString("node2"));
    QJsonArray array21;
    array21.append(QJsonValue(json21));
    array21.append(QJsonValue(json211));
    QTest::newRow("level2-1") << (StorageTree("second1")
                                  .setRoot("root"))
                                 .addChild("root", "node1")
                                 .addChild("root", "node2")
                              << array21;

    QJsonObject json3;
    json3.insert("from" + QString(":"), QString("root"));
    json3.insert("to" + QString(":"), QString("node1"));
    QJsonObject json31;
    json31.insert("from" + QString(":"), QString("root"));
    json31.insert("to" + QString(":"), QString("node2"));
    QJsonObject json32;
    json32.insert("from" + QString(":"), QString("node1"));
    json32.insert("to" + QString(":"), QString("leaf1"));
    QJsonArray array3;
    array3.append(QJsonValue(json3));
    array3.append(QJsonValue(json31));
    array3.append(QJsonValue(json32));
    QTest::newRow("level3") << (StorageTree("third")
                                .setRoot("root"))
                               .addChild("root", "node1")
                               .addChild("root", "node2")
                               .addChild("node1", "leaf1")
                            << array3;


    QJsonObject json311;
    json311.insert("from" + QString(":"), QString("node1"));
    json311.insert("to" + QString(":"), QString("leaf2"));
    QJsonArray array31;
    array31.append(QJsonValue(json3));
    array31.append(QJsonValue(json31));
    array31.append(QJsonValue(json32));
    array31.append(QJsonValue(json311));
    QTest::newRow("level3-1") << (StorageTree("third")
                                  .setRoot("root"))
                                 .addChild("root", "node1")
                                 .addChild("root", "node2")
                                 .addChild("node1", "leaf1")
                                 .addChild("node1", "leaf2")
                                 .setBalance("root", -10)
                                 .setExpense("root", 5)
                                 .setBalance("node1", 0)
                                 .setExpense("node1", 10)
                                 .setBalance("node2", 50)
                                 .setExpense("node2", 50)
                                 .setBalance("leaf1", 1)
                                 .setExpense("leaf1", 500)
                                 .setBalance("leaf2", 10)
                                 .setExpense("leaf2", 500)
                              << array31;

}

void TStorageTree::TestEdgesToJSONArray()
{
    QFETCH(StorageTree, tree);
    QFETCH(QJsonArray, expected);

    const QJsonArray actual = tree.edgesToJSONArray();

    QCOMPARE(actual, expected);

}

void TStorageTree::TestToJSON_data()
{
    QTest::addColumn <StorageTree> ("tree");
    QTest::addColumn <QJsonObject> ("expected");

    QJsonObject innerjson;
    innerjson.insert("from" + QString(":"), QString());
    innerjson.insert("to" + QString(":"), QString());
    QJsonArray array;
    array.append(QJsonValue(innerjson));
    QJsonObject json;
    json.insert("id" + QString(":"), QString("id"));
    json.insert("edges" + QString(":"), array);
    QTest::newRow("empty - tree") << StorageTree("id")
                                  << json;

    QJsonObject innerjson1;
    innerjson1.insert("from" + QString(":"), QString("root"));
    innerjson1.insert("to" + QString(":"), QString());
    QJsonArray array1;
    array1.append(QJsonValue(innerjson1));
    QJsonObject json1;
    json1.insert("id" + QString(":"), QString("id1"));
    json1.insert("edges" + QString(":"), array1);
    QTest::newRow("single-root") << StorageTree("id1").setRoot("root")
                                << json1;

    QJsonObject innerjson2;
    innerjson2.insert("from" + QString(":"), QString("root"));
    innerjson2.insert("to" + QString(":"), QString("node1"));
    QJsonArray array2;
    array2.append(QJsonValue(innerjson2));
    QJsonObject json2;
    json2.insert("id" + QString(":"), QString("second"));
    json2.insert("edges" + QString(":"), array2);
    QTest::newRow("level2") << (StorageTree("second")
                                .setRoot("root"))
                               .addChild("root", "node1")
                             << json2;

    QJsonObject innerjson21;
    innerjson21.insert("from" + QString(":"), QString("root"));
    innerjson21.insert("to" + QString(":"), QString("node1"));
    QJsonObject innerjson211;
    innerjson211.insert("from" + QString(":"), QString("root"));
    innerjson211.insert("to" + QString(":"), QString("node2"));
    QJsonArray array21;
    array21.append(QJsonValue(innerjson21));
    array21.append(QJsonValue(innerjson211));
    QJsonObject json21;
    json21.insert("id" + QString(":"), QString("second1"));
    json21.insert("edges" + QString(":"), array21);
    QTest::newRow("level2-1") << (StorageTree("second1")
                                  .setRoot("root"))
                                 .addChild("root", "node1")
                                 .addChild("root", "node2")
                              << json21;

    QJsonObject innerjson3;
    innerjson3.insert("from" + QString(":"), QString("root"));
    innerjson3.insert("to" + QString(":"), QString("node1"));
    QJsonObject innerjson31;
    innerjson31.insert("from" + QString(":"), QString("root"));
    innerjson31.insert("to" + QString(":"), QString("node2"));
    QJsonObject innerjson32;
    innerjson32.insert("from" + QString(":"), QString("node1"));
    innerjson32.insert("to" + QString(":"), QString("leaf1"));
    QJsonArray array3;
    array3.append(QJsonValue(innerjson3));
    array3.append(QJsonValue(innerjson31));
    array3.append(QJsonValue(innerjson32));\
    QJsonObject json3;
    json3.insert("id" + QString(":"), QString("third"));
    json3.insert("edges" + QString(":"), array3);
    QTest::newRow("level3") << (StorageTree("third")
                                .setRoot("root"))
                               .addChild("root", "node1")
                               .addChild("root", "node2")
                               .addChild("node1", "leaf1")
                            << json3;


    QJsonObject innerjson311;
    innerjson311.insert("from" + QString(":"), QString("node1"));
    innerjson311.insert("to" + QString(":"), QString("leaf2"));
    QJsonArray array31;
    array31.append(QJsonValue(innerjson3));
    array31.append(QJsonValue(innerjson31));
    array31.append(QJsonValue(innerjson32));
    array31.append(QJsonValue(innerjson311));
    QJsonObject json31;
    json31.insert("id" + QString(":"), QString("third"));
    json31.insert("edges" + QString(":"), array31);
    QTest::newRow("level3-1") << (StorageTree("third")
                                  .setRoot("root"))
                                 .addChild("root", "node1")
                                 .addChild("root", "node2")
                                 .addChild("node1", "leaf1")
                                 .addChild("node1", "leaf2")
                                 .setBalance("root", -10)
                                 .setExpense("root", 5)
                                 .setBalance("node1", 0)
                                 .setExpense("node1", 10)
                                 .setBalance("node2", 50)
                                 .setExpense("node2", 50)
                                 .setBalance("leaf1", 1)
                                 .setExpense("leaf1", 500)
                                 .setBalance("leaf2", 10)
                                 .setExpense("leaf2", 500)
                              << json31;
}

void TStorageTree::TestToJSON()
{
    QFETCH(StorageTree, tree);
    QFETCH(QJsonObject, expected);

    const QJsonObject actual = tree.toJSON();

    QCOMPARE(actual, expected);

}


