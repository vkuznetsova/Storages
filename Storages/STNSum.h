#ifndef STNSUM_H

#define STNSUM_H


class STNSum
{
public:
    virtual int map(const StorageTreeNode &node) = 0;
    virtual int sum(const QList<int> &elems) = 0;
};

#endif // STNSUM_H
