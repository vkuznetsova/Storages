#ifndef NSUNSSTORAGETREEPREDICAT_H
#define NSUNSSTORAGETREEPREDICAT_H

#include"StorageTreePredicat.h"

class StorageTree;

class NSunsStorageTreePredicat: public StorageTreePredicat
{
public:
    bool (*greater_)(int, int);

    NSunsStorageTreePredicat(const int count, bool (*greater)(int, int)):
        count_(count), greater_(greater)
    {}
    bool (*equal_)(int, int);

    bool check(const StorageTree &tree, const QString &nodeID) const
    {
        if(greater_)
            return greater_(tree.childrenIDs(nodeID).size(),count_);
        else {
            return equal_(tree.childrenIDs(nodeID).size(), count_) && !tree.isLeaf(nodeID);
        }
    }

private:
    int count_;
};


#endif // NSUNSSTORAGETREEPREDICAT_H
