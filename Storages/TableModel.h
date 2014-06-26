#ifndef TABLEMODEL_H

#define TABLEMODEL_H

#include <QAbstractItemModel>
#include <QColor>
#include <QBrush>
#include <QTableView>

#include "StorageTree.h"
#include "StorageTreeNode.h"
#include "StorageDatabaseWriter.h"

class TableModel : public QAbstractTableModel
{
public:
    TableModel(const StorageTree tree = StorageTree());

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

    void setTree(const StorageTree &tree);

    QString columnID(const int column) const;

    static const int columnNode;
    static const int columnParent;
    static const int columnBalance;
    static const int columnExpense;
private:
   static bool greaterThan(const QPair<QString, QVariant> &pair1,
                           const QPair<QString, QVariant> &pair2);
   static bool lessThan(const QPair<QString, QVariant> &pair1,
                           const QPair<QString, QVariant> &pair2);

    StorageTree tree_;
    QVariant recursiveData(const StorageTreeNode &parent, const QModelIndex &index) const;

    QStringList nodeOrder_;

    StorageDatabaseWriter writer_;


};

#endif // TABLEMODEL_H
