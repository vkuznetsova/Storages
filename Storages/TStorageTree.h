#ifndef TSTORAGETREE_H

#define TSTORAGETREE_H

#include <QtTest/QtTest>
#include "StorageTree.h"

class TStorageTree : public QObject
{
    Q_OBJECT
public:
    TStorageTree();

private slots:
    void TestChildren_data();
    void TestChildren();

    void TestLevel_data();
    void TestLevel();

    void TestParent_data();
    void TestParent();

    void TestSubTree_data();
    void TestSubTree();

    void TestToString_data();
    void TestToString();

    void TestIsLeaf_data();
    void TestIsLeaf();

    void TestIsBoolean_data();
    void TestIsBoolean();

   /* void TestIsBalanced_data();
    void TestIsBalanced();

    void TestLeafs_data();
    void TestLeafs();*/


};

#endif // TSTORAGETREE_H
