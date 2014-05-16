#ifndef BALANCEDSTORAGETREEPREDICAT_H
#define BALANCEDSTORAGETREEPREDICAT_H

#include"StorageTreePredicat.h"

class StorageTree;

class BalancedStorageTreePredicat : public StorageTreePredicat
{
public:
    BalancedStorageTreePredicat(const int count, const int level) :
        count_(count),
        level_(level)
    {
    }

    bool check(const StorageTree &tree, const QString &nodeID) const
    {
        if(tree.isLeaf(nodeID))
        {
            return tree.level(nodeID) == level_;
        }
        else
        {
            return tree.node(nodeID).children().size() == count_;
        }
    }

private:
    int count_;
    int level_;
};

#endif // BALANCEDSTORAGETREEPREDICAT_H
