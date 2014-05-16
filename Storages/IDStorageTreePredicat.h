#ifndef IDSTORAGETREEPREDICAT_H
#define IDSTORAGETREEPREDICAT_H

#include"StorageTreePredicat.h"

class StorageTree;

class IDStorageTreePredicat: public StorageTreePredicat
{
public:
    IDStorageTreePredicat(const int size):
        size_(size)
    {}
    bool check(const StorageTree &tree, const QString &nodeID) const
    {
        return nodeID.size() <= size_;
    }
private:
    int size_;
};

#endif // IDSTORAGETREEPREDICAT_H
