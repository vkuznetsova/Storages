#ifndef STORAGETREE_H

#define STORAGETREE_H

#include <QtCore>
#include<QList>
#include"StorageTreeNode.h"
#include"StorageTreeNodeMap.h"
#include"StorageUtils.h"
#include"STNFold.h"
#include"STNTotalSum.h"

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

    QStringList childrenIDs(const QString &id) const;

    QList<StorageTreeNode> children(const QString &id) const;

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
    StorageTree map(StorageTreeNodeMap *map) const;
    int sum(STNTotalSum *sum) const;
    QString fold(const QString &init, const QString &nodeID, STNFold *f) const;

    bool idSize(const int size) const;

    bool moreNSuns(const int count) const;

    bool nSuns(const int count) const;

    StorageTree run() const;

    int totalSum();

    int PositiveElemsSum();

    int euclidMetric();

    StorageTree accumBalance() const;

    static StorageTree generateTree(const int level);

    int count() const;
    //QString nodeForNum(const int num) const;

protected:
    StorageTree(const QString &rootID, const QHash<QString, StorageTreeNode> &nodes);

    int level(const QString &node, const QString &find, const int l) const;


private:
    QString rootID_;
    QHash<QString, StorageTreeNode> nodes_;

    void recursiveToString(const StorageTreeNode &parent, QString &sRecord) const;

    // bool recursiveISBoolean(const StorageTreeNode &parent) const;

    void recursiveSubTree(const StorageTreeNode &parent, StorageTree &tree) const;
    static void recursiveIns(StorageTree &tree,const StorageTreeNode &parent, const int maxLvl, int lvl);

    void recursiveLeafs(const StorageTreeNode &parent, QStringList &childrenIDs) const;

    // bool recursiveIsBalanced(const StorageTreeNode &parent) const;

    StorageTree recursiveAccumBalance(const StorageTreeNode &parent) const;

    //void recursiveNodeForNum(const StorageTreeNode &parent, const int num, int findNum) const;


};
Q_DECLARE_METATYPE(StorageTree)


#endif // STORAGETREE_H
