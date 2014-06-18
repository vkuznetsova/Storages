#ifndef TSTORAGETREENODE_H

#define TSTORAGETREENODE_H

#include <QtTest/QtTest>
#include <QJsonObject>

#include "StorageTreeNode.h"

class TStorageTreeNode: public QObject
{
    Q_OBJECT
public:
    TStorageTreeNode();

private slots:

    void TestToJSON_data();
    void TestToJSON();

};

#endif // TSTORAGETREENODE_H
