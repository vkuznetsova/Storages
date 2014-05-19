#ifndef BOOLEANSTORAGETREEPREDICAT_H
#define BOOLEANSTORAGETREEPREDICAT_H

#include"StorageTreePredicat.h"


class StorageTree;

class BooleanStorageTreePredicat : public StorageTreePredicat
{
public:
    bool check(const StorageTree &tree, const QString &nodeID) const
    {
        return tree.node(nodeID).childrenID().size() == 2 || tree.isLeaf(nodeID);
    }
};

#endif // BOOLEANSTORAGETREEPREDICAT_H
