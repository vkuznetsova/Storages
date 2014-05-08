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

private:
    QString id_;
    QList<StorageTreeNode> children_;
};

class StorageTree
{
public:
    StorageTree();

    StorageTree(const StorageTreeNode &root);

    StorageTree& setRoot(const StorageTreeNode &root);
    StorageTree& addChild(const QString &parent, const StorageTreeNode &child);

    QStringList children(const QString &id) const;

    int level(const QString &node) const;

protected:
    int level(const QString &node, const QString &find, const int l) const;

private:
    QString rootID_;
    QHash<QString, StorageTreeNode> nodes_;
};

Q_DECLARE_METATYPE(StorageTree)

#endif // STORAGETREE_H
