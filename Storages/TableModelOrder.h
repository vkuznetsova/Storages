#ifndef TABLEMODELORDER_H

#define TABLEMODELORDER_H


#include <QAbstractItemModel>

#include "OrderGenerator.h"
#include "StorageDatabaseReader.h"

class TableModelOrder : public QAbstractTableModel
{
public:
    TableModelOrder(const TreeOrderTable orderTable = TreeOrderTable());

    virtual QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const;
    virtual QModelIndex parent(const QModelIndex &child) const;
    virtual int rowCount(const QModelIndex &parent = QModelIndex()) const;
    virtual int columnCount(const QModelIndex &parent = QModelIndex()) const;
    virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    virtual QVariant headerData(int section,
                                Qt::Orientation orientation,
                                int role = Qt::DisplayRole) const;


    void calcOrderPlans(TreeOrderTable &orderTable, const StorageTree &tree, const int days);

    void setOrderTable(const TreeOrderTable &orderTable);

     virtual void sort( int column, Qt::SortOrder order = Qt::AscendingOrder );

    Order rowID(const int row) const;

    Order columnID(const int column) const;

    bool setData(const QModelIndex &index, const QVariant &value, int role);

    Qt::ItemFlags flags(const QModelIndex &index) const;

    static const int columnFrom;
    static const int columnTo;
    static const int columnOrderDate;
    static const int columnDeliveryDate;

private:

    static bool greaterThan(const QPair<Order, QVariant> &pair1,
                            const QPair<Order, QVariant> &pair2);
    static bool lessThan(const QPair<Order, QVariant> &pair1,
                            const QPair<Order, QVariant> &pair2);

    StorageDatabaseReader reader_;

    TreeOrderTable orderTable_;

    QList<Order> orders_;

};

#endif // TABLEMODELORDER_H
