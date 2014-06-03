#include "TTableModel.h"

TTableModel::TTableModel()
{

}

void TTableModel::TestColumnCount()
{
    TableModel model;
    QCOMPARE(model.columnCount(QModelIndex()), 4);
}

void TTableModel::TestHorizontalHeader()
{
    TableModel model;
    QCOMPARE(model.headerData(0, Qt::Horizontal), QVariant("Потомок"));
    QCOMPARE(model.headerData(1, Qt::Horizontal), QVariant("Родитель"));
    QCOMPARE(model.headerData(2, Qt::Horizontal), QVariant("Баланс Потомка"));
    QCOMPARE(model.headerData(3, Qt::Horizontal), QVariant("Расход"));
}

void TTableModel::TestRowCount_data()
{
    QTest::addColumn<StorageTree>("tree");
    QTest::addColumn<int>("rowCount");

    QTest::newRow("empty-tree")<<StorageTree()
                              <<0;

    QTest::newRow("single-root")<<StorageTree(StorageTreeNode("root"))
                               <<1;

    QTest::newRow("level1")<<(StorageTree(StorageTreeNode("root"))
                              .addChild("root", StorageTreeNode("leaf1")))
                          <<2;

    QTest::newRow("level2")<<(StorageTree(StorageTreeNode("root"))
                              .addChild("root", StorageTreeNode("leaf1"))
                              .addChild("root", StorageTreeNode("leaf2")))
                          <<3;

    QTest::newRow("level2")<<(StorageTree(StorageTreeNode("root"))
                              .addChild("root", StorageTreeNode("leaf1"))
                              .addChild("leaf1", StorageTreeNode("leaf2")))
                          <<3;

}

void TTableModel::TestRowCount()
{
    QFETCH(StorageTree, tree);
    QFETCH(int, rowCount);

    TableModel model(tree);

    QCOMPARE(model.rowCount(QModelIndex()), rowCount);
}

void TTableModel::TestRowData_data()
{
    QTest::addColumn<StorageTree>("tree");
    QTest::addColumn<int>("row");
    QTest::addColumn<int>("column");
    QTest::addColumn<QVariant>("data");

    QTest::newRow("empty-tree")<<StorageTree()
                              << 0
                              << 0
                              << QVariant();

    QTest::newRow("single-tree1")<<StorageTree(StorageTreeNode("root"))
                                << 0
                                << 0
                                <<QVariant("root");

    QTest::newRow("single-tree2")<<StorageTree(StorageTreeNode("root"))
                                << 0
                                << 1
                                << QVariant(QString());

    QTest::newRow("single-tree3")<<StorageTree(StorageTreeNode("root", 1, 1, 10))
                                << 0
                                << 2
                                <<QVariant(10);
    QTest::newRow("level1")<<(StorageTree(StorageTreeNode("root", 1, 3, -100)))
                             .addChild("root", StorageTreeNode("leaf1", 2, 1, -1))
                          << 1
                          << 0
                          <<QVariant("leaf1");
}

void TTableModel::TestRowData()
{
    QFETCH(StorageTree, tree);
    QFETCH(int, row);
    QFETCH(int, column);
    QFETCH(QVariant, data);

    TableModel model(tree);

    QCOMPARE(model.data(model.index(row, column, QModelIndex()), Qt::DisplayRole), data);
}

void TTableModel::TestAddNewChild_data()
{
    QTest::addColumn<StorageTree>("tree");
    QTest::addColumn<QString>("parentID");
    QTest::addColumn<QString>("childID");
    QTest::addColumn<int>("row");
    QTest::addColumn<int>("column");
    QTest::addColumn<QVariant>("data");

    QTest::newRow("empty-tree")<<StorageTree()
                              << QString()
                              << QString()
                              << 0
                              << 0
                              << QVariant();

    QTest::newRow("single-tree")<<StorageTree(StorageTreeNode("root"))
                               << "root"
                               << "node1"
                               << 1
                               << 0
                               << QVariant("node1");

    QTest::newRow("level2")<<(StorageTree(StorageTreeNode("root"))
                              .addChild("root", StorageTreeNode("node1")))
                          << "node1"
                          << "leaf1"
                          << 2
                          << 0
                          << QVariant("leaf1");

    QTest::newRow("level3")<<(StorageTree(StorageTreeNode("root"))
                              .addChild("root", StorageTreeNode("node1"))
                              .addChild("node1", StorageTreeNode("leaf1"))
                              .addChild("node1", StorageTreeNode("leaf2")))
                          << "node1"
                          << "leaf3"
                          << 4
                          << 0
                          << QVariant("leaf3");
}

void TTableModel::TestAddNewChild()
{
    QFETCH(StorageTree, tree);
    QFETCH(QString, parentID);
    QFETCH(QString, childID);
    QFETCH(int, row);
    QFETCH(int, column);
    QFETCH(QVariant, data);

    TableModel model(tree);
    model.addNewChild(parentID, childID);
    QCOMPARE(model.data(model.index(row, column, QModelIndex()), Qt::DisplayRole), data);
}

void TTableModel::TestSort_data()
{
    QTest::addColumn<StorageTree>("tree");
    QTest::addColumn<int>("column");
    QTest::addColumn<Qt::SortOrder>("order");
    QTest::addColumn<QStringList>("data");

    QTest::newRow("empty-tree") << StorageTree()
                                << 0
                                << Qt::AscendingOrder
                                << QStringList();

    QTest::newRow("single-root") << StorageTree(StorageTreeNode("root"))
                                 << 0
                                 << Qt::AscendingOrder
                                 << (QStringList() << "root");

    QTest::newRow("level-2-1") << (StorageTree(StorageTreeNode("root"))
                                   .addChild("root", StorageTreeNode("node1")))
                               << 1
                               << Qt::AscendingOrder
                               << (QStringList() << "node1" << "root");

    QTest::newRow("level-2-2") << (StorageTree(StorageTreeNode("root"))
                                   .addChild("root", StorageTreeNode("node1")))
                               << 1
                               << Qt::DescendingOrder
                               << (QStringList() << "root" << "node1");

}

void TTableModel::TestSort()
{
    QFETCH(StorageTree, tree);
    QFETCH(int, column);
    QFETCH(Qt::SortOrder, order);
    QFETCH(QStringList, data);

    TableModel model(tree);
    model.sort(column, order);

    QStringList modelData;
    for(int i = 0; i < model.rowCount(); i++)
    {
        QStringList rowData;
        rowData << model.data(model.index(i, 0)).toString();

        modelData << rowData.join(" ;");
    }

    const QStringList actual = modelData;
    const QStringList expected = data;

    QCOMPARE(actual, expected);
}

void TTableModel::TestRemoveNode_data()
{
    QTest::addColumn<StorageTree>("tree");
    QTest::addColumn<QString>("node");
    QTest::addColumn<QStringList>("result");

    QTest::newRow("empty-tree") << StorageTree()
                                << QString()
                                << QStringList();

    QTest::newRow("single-root") << StorageTree(StorageTreeNode("root", 1, 8, 10))
                                 << "root"
                                 << QStringList();

    QTest::newRow("level2-1") << (StorageTree(StorageTreeNode("root"))
                                  .addChild("root", StorageTreeNode("node1")))
                              << "node1"
                              << (QStringList()<< QString("root"));


}

void TTableModel::TestRemoveNode()
{
    QFETCH(StorageTree, tree);
    QFETCH(QString, node);
    QFETCH(QStringList, result);

    TableModel model(tree);
    model.removeNode(node);

    QStringList modelData;
    for(int i = 0; i < model.rowCount(); i++)
    {
        QStringList rowData;

        rowData << model.data(model.index(i, 0)).toString();

        modelData << rowData.join(" ;");
    }

    const QStringList actualResult = modelData;
    const QStringList expectedResult = result;

    QCOMPARE(actualResult, expectedResult);

}
Q_DECLARE_METATYPE(Qt::SortOrder)
