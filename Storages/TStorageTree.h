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
};

#endif // TSTORAGETREE_H
