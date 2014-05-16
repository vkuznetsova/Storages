#ifndef STORAGETREEPREDICAT_H
#define STORAGETREEPREDICAT_H

#include <QtCore>

class StorageTree;

class StorageTreePredicat
{
public:
    virtual bool check(const StorageTree &tree, const QString &nodeID) const = 0;
};

#endif // STORAGETREEPREDICAT_H
