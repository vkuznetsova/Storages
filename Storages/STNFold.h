#ifndef STNFOLD_H

#define STNFOLD_H


class STNFold
{
public:
    virtual QString fold(const QString &acc, const StorageTreeNode &node) = 0;
    virtual QString left(const QString &acc, const StorageTreeNode &node) = 0;
};

#endif // STNFOLD_H
