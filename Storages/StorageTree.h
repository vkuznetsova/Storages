#ifndef STORAGETREE_H

#define STORAGETREE_H

#include <QtCore>
#include<QList>
#include"StorageTreeNode.h"
#include"StorageTreeNodeMap.h"


class StorageTreePredicat;


class StorageTree
{
public:
    StorageTree();

    StorageTree(const StorageTreeNode &root);

    StorageTree& setRoot(const StorageTreeNode &root);

    StorageTreeNode root()const;

    StorageTreeNode node(const QString &id) const;

    StorageTree& addChild(const QString &parent, const StorageTreeNode &child);

    QStringList children(const QString &id) const;

    int level(const QString &node) const;

    QString parent(const QString &child) const;

    StorageTree subTree(const QString &root) const;

    QString toString() const;

    bool operator ==(const StorageTree &tree) const;

    bool isLeaf(const QString &node) const;

    bool isBoolean();

    bool isBalanced();

    QStringList leafs(const QString &node);

    bool all(StorageTreePredicat *predicat) const;

    bool any(StorageTreePredicat *predicat) const;

    bool idSize(const int size) const;

    bool moreNSuns(const int count) const;

    bool nSuns(const int count) const;

    //int run(QString &node);

protected:
    int level(const QString &node, const QString &find, const int l) const;


private:
    QString rootID_;
    QHash<QString, StorageTreeNode> nodes_;

    void recursive(const StorageTreeNode &parent, QString &sRecord) const;

    // bool recursiveISBoolean(const StorageTreeNode &parent) const;

    void recursiveSubTree(const StorageTreeNode &parent, StorageTree &tree) const;

    void recursiveLeafs(const StorageTreeNode &parent, QStringList &children) const;

    // bool recursiveIsBalanced(const StorageTreeNode &parent) const;
};
Q_DECLARE_METATYPE(StorageTree)





/*class OnlyNSunsStorageTreePredicat: public StorageTreePredicat
{
public:
    bool (*equal_)(int, int);
    OnlyNSunsStorageTreePredicat(const int count, bool (*equal)(int, int)):
        count_(count), equal_(equal)
    {}
    bool check(const StorageTree &tree, const QString &nodeID) const
    {

        return equal_(tree.node(nodeID).childrenIDs().size(), count_) && !tree.isLeaf(nodeID);

    }
private:
    int count_;
};*/

#endif // STORAGETREE_H
