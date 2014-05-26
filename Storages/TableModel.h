#ifndef TABLEMODEL_H

#define TABLEMODEL_H

#include <QAbstractItemModel>
#include <QColor>
#include<QBrush>

#include "StorageTree.h"
#include"StorageTreeNode.h"

class TableModel : public QAbstractTableModel
{
    // QAbstractItemModel interface
public:
    TableModel(const StorageTree &tree = StorageTree());

    virtual QModelIndex index(int row, int column, const QModelIndex &parent) const;
    virtual QModelIndex parent(const QModelIndex &child) const;
    virtual int rowCount(const QModelIndex &parent) const;
    virtual int columnCount(const QModelIndex &parent) const;
    virtual QVariant data(const QModelIndex &index, int role) const;
    virtual QVariant headerData(int section,
                                Qt::Orientation orientation,
                                int role = Qt::DisplayRole) const;

    bool setData(const QModelIndex &index, const QVariant &value, int role);

    //void sort(int column, Qt::SortOrder order);

    void addNewChild(const QString &parentID, const QString &childID);

    QString rowID(const int row) const;

private:
    StorageTree tree_;
    QVariant recursiveData(const StorageTreeNode &parent, const QModelIndex &index) const;

    QStringList nodeOrder_;
};



#endif // TABLEMODEL_H
