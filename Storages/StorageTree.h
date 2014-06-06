#ifndef STORAGETREE_H

#define STORAGETREE_H

#include <QtCore>
#include <QList>
#include <QSet>
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

    StorageTree(const QString id);

    QString id()const;

    void setID(const QString &idTrees);

    StorageTree& setRoot(const StorageTreeNode &root);

    StorageTreeNode root()const;

    StorageTreeNode node(const QString &id) const;

    StorageTree& addChild(const QString &parent, const StorageTreeNode &child);\

    StorageTree& addChild(const QString &parent, const QString &child);

    QStringList childrenIDs(const QString &id) const;

    QList<StorageTreeNode> children(const QString &id) const;

    int level(const QString &node) const;

    QString parent(const QString &child) const;

    StorageTree subTree(const QString &root) const;

    QString toString() const;

    bool operator ==(const StorageTree &structure) const;

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
    QString nodeForNum(const int num);

    QStringList order() const;

    void removeNode(const QString &subTreeRoot);

    StorageTree &setBalance(const QString &nodeID, const int balance);

    StorageTree &setExpense(const QString &nodeID, const int expense);

    void autoSetRoot();

    QHash<QString, QSet<QString> > structure() const;

    QHash<QString, StorageTreeNode> structureData() const;


protected:
    StorageTree(const QString &rootID, const QHash<QString, StorageTreeNode> &nodes, const QHash<QString, QSet<QString> > &tree);

    int level(const QString &node, const QString &find, const int l) const;

    QStringList order(const QString &nodeID) const;

private:
    QString rootID_;
    QHash<QString, QSet<QString> > tree_;
    QHash<QString, StorageTreeNode> nodes_;
    QString id_;

    void recursiveToString(const StorageTreeNode &parent, QString &sRecord) const;

    // bool recursiveISBoolean(const StorageTreeNode &parent) const;

    void recursiveSubTree(const StorageTreeNode &parent, StorageTree &structure) const;
    static void recursiveIns(StorageTree &structure,const StorageTreeNode &parent, const int maxLvl, int lvl);

    void recursiveLeafs(const StorageTreeNode &parent, QStringList &childrenIDs) const;

    // bool recursiveIsBalanced(const StorageTreeNode &parent) const;

    int recursiveAccumBalance(const QString &id);

    StorageTreeNode recursiveNodeForNum(const StorageTreeNode &parent, const int num, int &findNum);
};

Q_DECLARE_METATYPE(StorageTree)


#endif // STORAGETREE_H
