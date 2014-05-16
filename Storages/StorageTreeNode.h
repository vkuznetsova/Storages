#ifndef STORAGETREENODE_H
#define STORAGETREENODE_H

#include <QtCore>
#include"StorageUtils.h"

class StorageTreeNode
{
public:
    int (*expense_)();
    StorageTreeNode(const QString &id = QString(),
                    QList<StorageTreeNode> children = QList<StorageTreeNode>(),
                    const int level = 0, const int balance = 0, int (*expense)()=0) :
        id_(id),
        children_(children),
        level_(level),
        balance_(balance),
        expense_(expense)
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

    void setLeaf(const bool &value)
    {
        isLeaf_ = value;
    }

    bool isLeaf() const
    {
        return isLeaf_;
    }

    void setLevel(const int level)
    {
        level_ = level;
    }

    int level() const
    {
        return level_;
    }

    void setBalance(const int balance)
    {
        balance_ = balance;
    }

    int getBalance()const
    {
        return balance_;
    }

private:
    QString id_;
    QList<StorageTreeNode> children_;
    QString parent_;
    bool isLeaf_;
    int level_;
    int balance_;
};

#endif // STORAGETREENODE_H
