#ifndef STNTOSTRINGFOLD_H

#define STNTOSTRINGFOLD_H

#include "STNFold.h"

class STNToStringFold : public STNFold
{
public:
    QString fold(const QString &acc, const StorageTreeNode &node)
    {
        return acc + " " + node.id();
    }

    QString left(const QString &acc, const StorageTreeNode &node)
    {
        return "(" + node.id() + acc + ")";
    }
};

#endif // STNTOSTRINGFOLD_H
