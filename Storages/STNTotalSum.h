#ifndef STNTOTALSUM_H

#define STNTOTALSUM_H

#include"STNSum.h"

class STNTotalSum : public STNSum
{
public:
    virtual int map(const StorageTreeNode &node)
    {
        return node.getBalance();
    }

    virtual int sum(const QList<int> &elems)
    {
        int s = 0;

        foreach(const int e, elems)
        {
            s += e;
        }

        return s;
    }
};


#endif // STNTOTALSUM_H
