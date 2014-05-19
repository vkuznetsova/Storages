#ifndef STORAGETREENODE_H
#define STORAGETREENODE_H

#include <QtCore>
#include"StorageUtils.h"

class STNConsumptionMap;

class StorageTreeNode
{
public:
    StorageTreeNode(const QString &id = QString(),
                    QList<QString> childrenID = QList<QString>(),
                    const int level = 0,
                    const int expense = 0,
                    int balance = 0) :
        id_(id),
        childrenID_(childrenID),
        level_(level),
        balance_(balance),
        expense_(expense)
    {
    }

    QString id() const
    {
        return id_;
    }

    QStringList childrenID() const
    {
        return childrenID_;
    }

    void addChild(const QString &childID)
    {
        childrenID_ << childID;
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
        balance_ = balance_ - consumption;
    }

    int getBalance()const
    {
        return balance_;
    }

   /* static int expense()
    {
        int exp = 7;
        return exp;
    }*/

    void setExpence(const int expense)
    {
        expense_ = expense;
    }

    int getExpence() const
    {
        return expense_;
    }

private:
    QString id_;
    QList<QString> childrenID_;
    QString parent_;
    bool isLeaf_;
    int level_;
    int balance_;
    int expense_;
};

#endif // STORAGETREENODE_H
