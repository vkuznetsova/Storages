#ifndef STORAGETREENODE_H
#define STORAGETREENODE_H

#include <QtCore>
#include <QJsonObject>
#include <QJsonValue>

#include "StorageUtils.h"


class STNConsumptionMap;

class StorageTreeNode
{
public:

    StorageTreeNode(const QString &id = QString(),
                    const int level = 0,
                    const int expense = 0,
                    int balance = 0) :
        id_(id),
        level_(level),
        balance_(balance),
        expense_(expense)
    {
    }

    QString id() const
    {
        return id_;
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

    void expend(const int consumption)
    {
        balance_ = balance_ - expense_;
        Q_UNUSED(consumption)
    }

    int getBalance()const
    {
        return balance_;
    }

    void setExpence(const int expense)
    {
        expense_ = expense;
    }

    int getExpence() const
    {
        return expense_;
    }

    bool operator ==(const StorageTreeNode &node) const
    {
        return id_ == node.id_
                && parent_ == node.parent_
                && level_ == node.level_
                && balance_ == node.balance_
                && expense_ == node.expense_ ;
    }

    bool operator >= (const StorageTreeNode &node) const;
    QJsonObject toJSON() const;

    static const QString idKey;
    static const QString balanceKey;
    static const QString expenseKey;

private:
    QString id_;
    QString parent_;
    bool isLeaf_;
    int level_;
    int balance_;
    int expense_;
};

Q_DECLARE_METATYPE(StorageTreeNode)

#endif // STORAGETREENODE_H

