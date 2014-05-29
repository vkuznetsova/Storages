#ifndef TABLEMODEL_H

#define TABLEMODEL_H

#include <QAbstractItemModel>
#include <QColor>
#include <QBrush>
#include <QTableView>

#include "StorageTree.h"
#include "StorageTreeNode.h"


class TableModel : public QAbstractTableModel
{
    // QAbstractItemModel interface
public:
    TableModel(const StorageTree &tree = StorageTree());

    virtual QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const;
    virtual QModelIndex parent(const QModelIndex &child) const;
    virtual int rowCount(const QModelIndex &parent = QModelIndex()) const;
    virtual int columnCount(const QModelIndex &parent = QModelIndex()) const;
    virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    virtual QVariant headerData(int section,
                                Qt::Orientation orientation,
                                int role = Qt::DisplayRole) const;

    void addNewChild(const QString &parentID, const QString &childID);

    QString rowID(const int row) const;

    Qt::ItemFlags flags(const QModelIndex &index) const;

    bool setData(const QModelIndex &index, const QVariant &value, int role);

    virtual void sort( int column, Qt::SortOrder order = Qt::AscendingOrder );

    void removeNode(QString &parentID);

    QString columnID(const int column) const;

private:
   static bool greaterThan(const QPair<QString, QVariant> &pair1,
                           const QPair<QString, QVariant> &pair2);
   static bool lessThan(const QPair<QString, QVariant> &pair1,
                           const QPair<QString, QVariant> &pair2);

    StorageTree tree_;
    QVariant recursiveData(const StorageTreeNode &parent, const QModelIndex &index) const;

    QStringList nodeOrder_;
};



#endif // TABLEMODEL_H
