#ifndef STORAGETREENODEMAP_H
#define STORAGETREENODEMAP_H

#include <QtCore>

class StorageTreeNodeMap
{
public:
    virtual StorageTreeNode map(const StorageTreeNode &node) const = 0;
};

#endif // STORAGETREENODEMAP_H
