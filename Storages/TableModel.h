#ifndef TABLEMODEL_H

#define TABLEMODEL_H

#include <QAbstractItemModel>

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

private:
    StorageTree tree_;
    QVariant recursiveData(const StorageTreeNode &parent, const QModelIndex &index) const;

    QStringList nodeOrder_;
};



#endif // TABLEMODEL_H
