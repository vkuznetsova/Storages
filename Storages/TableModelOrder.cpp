#include "TableModelOrder.h"

const int TableModelOrder::columnFrom = 0;
const int TableModelOrder::columnTo = 1;
const int TableModelOrder::columnOrderDate = 2;
const int TableModelOrder::columnDeliveryDate = 3;

TableModelOrder::TableModelOrder(const TreeOrderTable orderTable)
{
    reader_ = StorageDatabaseReader("dataBaseName");
    setOrderTable(orderTable);
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
    int rowCount = 0;
    if(!parent.isValid())
    {
        foreach (const QString &storage, orderTable_.keys())
        {
            foreach (const int day, orderTable_.value(storage).keys())
            {
                rowCount++;
                Q_UNUSED(day)
            }
        }
        return rowCount;
    }
    return 0;
}

int TableModelOrder::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return 4;
}

QVariant TableModelOrder::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
    {
        return QVariant();
    }
    foreach (const QString &storage, orderTable_.keys())
    {
        foreach (const int day, orderTable_.value(storage).keys())
        {
            if(role == Qt::DisplayRole)
            {
                if(index.column() == columnFrom)
                {
                    return orderTable_.value(storage).value(day).from();
                }
                if(index.column() == columnTo)
                {
                    return orderTable_.value(storage).value(day).to();
                }
                if(index.column() == columnDeliveryDate)
                {
                    return orderTable_.value(storage).value(day).deliveryTime();
                }
                if(index.column() == columnOrderDate)
                {
                    return orderTable_.value(storage).value(day).orderTime();
                }
            }
        }
    }
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

void TableModelOrder::calcOrderPlans(TreeOrderTable &orderTable, const StorageTree &tree, const int days)
{
    OrderGenerator::calcOrderPlans(orderTable, tree, days);
    layoutChanged();
}

void TableModelOrder::setOrderTable(const TreeOrderTable &orderTable)
{
    orderTable_ = orderTable;
    emit layoutChanged();
}

void TableModelOrder::sort(int column, Qt::SortOrder order)
{
    QList< QPair<QString, QVariant> > modelDataOrder;

    for(int i = 0; i < rowCount(); i++)
    {
        modelDataOrder << QPair<QString, QVariant>(rowID(i), data(index(i, column), Qt::EditRole));
    }
    if(order == Qt::AscendingOrder)
    {
        std::sort(modelDataOrder.begin(), modelDataOrder.end(), greaterThan);
    }
    else
    {
        std::sort(modelDataOrder.begin(), modelDataOrder.end(), lessThan);
    }

    nodes_.clear();

    for(int i = 0; i < modelDataOrder.size(); i++)
    {
        nodes_ << modelDataOrder.at(i).first;
    }
    emit layoutChanged();

}

QString TableModelOrder::rowID(const int row) const
{
    return nodes_.at(row);
}

QString TableModelOrder::columnID(const int column) const
{
    return nodes_.at(column);
}

bool TableModelOrder::greaterThan(const QPair<QString, QVariant> &pair1, const QPair<QString, QVariant> &pair2)
{
    return pair1.second > pair2.second;
}

bool TableModelOrder::lessThan(const QPair<QString, QVariant> &pair1, const QPair<QString, QVariant> &pair2)
{
    return pair1.second < pair2.second;
}
