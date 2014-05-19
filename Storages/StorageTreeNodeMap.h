#ifndef STORAGETREENODEMAP_H

#define STORAGETREENODEMAP_H

#include "StorageTreeNode.h"

class StorageTreeNodeMap
{
public:
    virtual StorageTreeNode map(const StorageTreeNode &node) const = 0;
};

class STNConsumptionMap : public StorageTreeNodeMap
{
public:
    STNConsumptionMap(const int consumption) :
        consumption_(consumption)
    {
    }

    virtual StorageTreeNode map(const StorageTreeNode &node) const
    {
        StorageTreeNode copy = node;
        copy.expend(consumption_);

        return copy;
    }

private:
    int consumption_;
};

#endif // STORAGETREENODEMAP_H
