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
    if(!parent.isValid())
    {
        return orderTable_.rowCount;
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
    const int row = index.row();
    const int day = row / orderTable_.numStorages + 1;
    const int storageIndex = row % orderTable_.numStorages;
    QList<QString> storages = orderTable_.keys();
    qSort(storages.begin(), storages.end());
    QString storage = storages[storageIndex];
    if(role == Qt::DisplayRole || role == Qt::EditRole)
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
    emit layoutChanged();
}

void TableModelOrder::setOrderTable(const TreeOrderTable &orderTable)
{
    orderTable_ = orderTable;
    orders_ = TreeOrderTable().toList(orderTable);
    emit layoutChanged();
}

void TableModelOrder::sort(int column, Qt::SortOrder order)
{
    QList< QPair<Order, QVariant> > modelOrder;

    for(int i = 0; i < rowCount(); i++)
    {
        modelOrder << QPair<Order, QVariant>(rowID(i), data(index(i, column), Qt::EditRole));
    }
    if(order == Qt::AscendingOrder)
    {
        std::sort(modelOrder.begin(), modelOrder.end(), greaterThan);
    }
    else
    {
        std::sort(modelOrder.begin(), modelOrder.end(), lessThan);
    }

    orders_.clear();

    for(int i = 0; i < modelOrder.size(); i++)
    {
        orders_ << modelOrder.at(i).first;
    }
    emit layoutChanged();
}

Order TableModelOrder::rowID(const int row) const
{
    Order order = Order(orders_.at(row).from(),
                        orders_.at(row).to(),
                        orders_.at(row).orderTime(),
                        orders_.at(row).deliveryTime());
    return order;
}

Order TableModelOrder::columnID(const int column) const
{
    Order order = Order(orders_.at(column).from(),
                        orders_.at(column).to(),
                        orders_.at(column).orderTime(),
                        orders_.at(column).deliveryTime());
    return order;
}

bool TableModelOrder::setData(const QModelIndex &index, const QVariant &value, int role)
{
    Q_UNUSED(value)
    if(index.isValid() && role == Qt::EditRole)
    {
        emit dataChanged(index, index);
        return true;
    }
    return false;
}

Qt::ItemFlags TableModelOrder::flags(const QModelIndex &index) const
{
    Qt::ItemFlags flags = QAbstractItemModel::flags(index);
    if(index.isValid())
    {
        flags |= Qt::ItemIsEditable;
    }
    return flags;
}

bool TableModelOrder::greaterThan(const QPair<Order, QVariant> &pair1,
                                  const QPair<Order, QVariant> &pair2)
{
    return pair1.second > pair2.second;
}

bool TableModelOrder::lessThan(const QPair<Order, QVariant> &pair1,
                               const QPair<Order, QVariant> &pair2)
{
    return pair1.second < pair2.second;
}
