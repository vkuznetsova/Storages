#include "TStorageTreeNode.h"


TStorageTreeNode::TStorageTreeNode()
{
}

void TStorageTreeNode::TestToJSON_data()
{
    QTest::addColumn <StorageTreeNode> ("node");
    QTest::addColumn <QJsonObject> ("expected");

    QJsonObject json1;
    json1.insert("id" + QString(":"), QString(""));
    json1.insert("balance" + QString(":"), 0);
    json1.insert("expense" + QString(":"), 0);

    QTest::newRow("empty-node") << StorageTreeNode()
                                << json1;

    QJsonObject json;
    json.insert("id" + QString(":"), QString("node1"));
    json.insert("balance" + QString(":"), 10);
    json.insert("expense" + QString(":"), 2);

    QTest::newRow("one-node") << StorageTreeNode("node1", 1, 2, 10)
                                << json;

    QJsonObject js;
    js.insert("id" + QString(":"), QString(""));
    js.insert("balance" + QString(":"), -10);
    js.insert("expense" + QString(":"), 2);

    QTest::newRow("one-node-1") << StorageTreeNode("", 1, 2, -10)
                                << js;

}

void TStorageTreeNode::TestToJSON()
{
    QFETCH(StorageTreeNode, node);
    QFETCH(QJsonObject, expected);

    QJsonObject actual = node.toJSON();

    QCOMPARE(actual, expected);
}
