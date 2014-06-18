#include "TStorageTreeNode.h"


TStorageTreeNode::TStorageTreeNode()
{
}

void TStorageTreeNode::TestToJSON_data()
{
    QTest::addColumn <StorageTreeNode> ("node");
    QTest::addColumn <QJsonObject> ("expected");

    QTest::newRow("empty-node") << StorageTreeNode()
                                << QJsonObject();

}

void TStorageTreeNode::TestToJSON()
{
    QFETCH(StorageTreeNode, node);
    QFETCH(QJsonObject, expected);

    QJsonObject actual = node.toJSON();

    QCOMPARE(actual, expected);
}
