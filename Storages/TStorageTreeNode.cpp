#include "TStorageTreeNode.h"


TStorageTreeNode::TStorageTreeNode()
{
}

void TStorageTreeNode::TestToJSON_data()
{
    QTest::addColumn <StorageTreeNode> ("node");
    QTest::addColumn <QJsonObject> ("expected");

    QJsonObject json1;
    json1.insert(StorageTreeNode::idKey, QString(""));
    json1.insert(StorageTreeNode::balanceKey, 0);
    json1.insert(StorageTreeNode::expenseKey, 0);

    QTest::newRow("empty-node") << StorageTreeNode()
                                << json1;

    QJsonObject json2;
    json2.insert(StorageTreeNode::idKey, QString("node1"));
    json2.insert(StorageTreeNode::balanceKey, 10);
    json2.insert(StorageTreeNode::expenseKey, 2);

    QTest::newRow("one-node") << StorageTreeNode("node1", 1, 2, 10)
                                << json2;

    QJsonObject json3;
    json3.insert(StorageTreeNode::idKey, QString("root"));
    json3.insert(StorageTreeNode::balanceKey, -10);
    json3.insert(StorageTreeNode::expenseKey, 2);

    QTest::newRow("one-node-1") << StorageTreeNode("root", 1, 2, -10)
                                << json3;

}

void TStorageTreeNode::TestToJSON()
{
    QFETCH(StorageTreeNode, node);
    QFETCH(QJsonObject, expected);

    QJsonObject actual = node.toJSON();
    QCOMPARE(actual, expected);
}
