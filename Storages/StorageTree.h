#ifndef STORAGETREE_H

#define STORAGETREE_H

#include <QtCore>

class StorageTreeNode
{
public:
    StorageTreeNode(const QString &id = QString(),
                    QList<StorageTreeNode> children = QList<StorageTreeNode>()) :
    id_(id),
    children_(children)
    {
    }

    QString id() const
    {
        return id_;
    }

    QStringList childrenIDs() const
    {
        QStringList ids;
        foreach(StorageTreeNode child, children_)
        {
            ids << child.id();
        }
        return ids;
    }

    void addChild(const StorageTreeNode &child)
    {
        children_ << child;
    }

    QList<StorageTreeNode> children() const
    {
        return children_;
    }

    void setParent(const QString &parent = QString())
    {
        parent_ = parent;
    }

    QString getParent() const
    {
        return parent_;
    }

private:
    QString id_;
    QList<StorageTreeNode> children_;
    QString parent_;
};

class StorageTree
{
public:
    StorageTree();

    StorageTree(const StorageTreeNode &root);

    StorageTree& setRoot(const StorageTreeNode &root);

    StorageTreeNode root()const;

    StorageTree& addChild(const QString &parent, const StorageTreeNode &child);

    QStringList children(const QString &id) const;

    int level(const QString &node) const;

    QString parent(const QString &child) const;

    StorageTree subTree(const QString &root) const;

    QString toString() const;

    bool operator ==(const StorageTree &tree) const;

    bool isLeaf(const QString &node);

    bool isBoolean();

   // bool isBalanced();

    QStringList leafs(const QString &node);

protected:
    int level(const QString &node, const QString &find, const int l) const;


private:
    QString rootID_;
    QHash<QString, StorageTreeNode> nodes_;

    void recursive(const StorageTreeNode &parent, QString &sRecord) const;

    bool recursiveISBoolean(const StorageTreeNode &parent) const;

    void recursiveSubTree(const StorageTreeNode &parent, StorageTree &tree) const;

    void recursiveLeafs(const StorageTreeNode &parent, QStringList &children) const;
};
Q_DECLARE_METATYPE(StorageTree)

#endif // STORAGETREE_H
