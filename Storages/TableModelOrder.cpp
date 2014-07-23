#include "TableModelOrder.h"

const int TableModelOrder::columnFrom = 0;
const int TableModelOrder::columnTo = 1;
const int TableModelOrder::columnOrderDate = 2;
const int TableModelOrder::columnDeliveryDate = 3;

TableModelOrder::TableModelOrder()
{
}

QModelIndex TableModelOrder::index(int row, int column, const QModelIndex &parent) const
{
    if (!hasIndex(row, column, parent))
    {
        return QModelIndex();
    }

    if (!parent.isValid())
    {
        return createIndex(row, column);
    }

    return QModelIndex();
}

QModelIndex TableModelOrder::parent(const QModelIndex &child) const
{
    if (!child.isValid())
    {
        return QModelIndex();
    }

    return QModelIndex();
}

int TableModelOrder::rowCount(const QModelIndex &parent) const
{
    return 0;
}

int TableModelOrder::columnCount(const QModelIndex &parent) const
{
    return 4;
}

QVariant TableModelOrder::data(const QModelIndex &index, int role) const
{
    return QVariant();
}

QVariant TableModelOrder::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(role == Qt::DisplayRole)
    {
        if(orientation == Qt::Horizontal)
        {
            if(section == columnFrom)
            {
                return "Откуда";
            }
            if(section == columnTo)
            {
                return "Куда";
            }
            if(section == columnOrderDate)
            {
                return "Дата заказа";
            }
            if(section == columnDeliveryDate)
            {
                return "Дата доставки";
            }
        }
    }
    return QVariant();
}
