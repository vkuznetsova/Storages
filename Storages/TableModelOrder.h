#ifndef TABLEMODELORDER_H

#define TABLEMODELORDER_H


#include <QAbstractItemModel>

class TableModelOrder : public QAbstractTableModel
{
public:
    TableModelOrder();

    virtual QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const;
    virtual QModelIndex parent(const QModelIndex &child) const;
    virtual int rowCount(const QModelIndex &parent = QModelIndex()) const;
    virtual int columnCount(const QModelIndex &parent = QModelIndex()) const;
    virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    virtual QVariant headerData(int section,
                                Qt::Orientation orientation,
                                int role = Qt::DisplayRole) const;

    static const int columnFrom;
    static const int columnTo;
    static const int columnOrderDate;
    static const int columnDeliveryDate;
};

#endif // TABLEMODELORDER_H
