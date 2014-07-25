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

     QString rowID(const int row) const;

     QString columnID(const int column) const;

    // virtual void sort( int column, Qt::SortOrder order = Qt::AscendingOrder );

    static const int columnFrom;
    static const int columnTo;
    static const int columnOrderDate;
    static const int columnDeliveryDate;

private:

//    static bool greaterThan(const QPair<QString, QVariant> &pair1,
//                            const QPair<QString, QVariant> &pair2);
//    static bool lessThan(const QPair<QString, QVariant> &pair1,
//                            const QPair<QString, QVariant> &pair2);

    StorageDatabaseReader reader_;

    TreeOrderTable orderTable_;

   // QStringList nodes_;

};

#endif // TABLEMODELORDER_H
