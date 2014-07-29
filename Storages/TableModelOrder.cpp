#include "TableModelOrder.h"

const int TableModelOrder::columnFrom = 0;
const int TableModelOrder::columnTo = 1;
const int TableModelOrder::columnOrderDate = 2;
const int TableModelOrder::columnDeliveryDate = 3;
const int TableModelOrder::columnVolumeOrder = 4;

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
        return orders_.count();
    }
    return 0;
}

int TableModelOrder::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return 5;
}

QVariant TableModelOrder::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
    {
        return QVariant();
    }
    if(role == Qt::DisplayRole || role == Qt::EditRole)
    {
        if(index.column() == columnFrom)
        {
            return orders_[index.row()].from();
        }
        if(index.column() == columnTo)
        {
            return orders_[index.row()].to();
        }
        if(index.column() == columnDeliveryDate)
        {
            return orders_[index.row()].deliveryTime();
        }
        if(index.column() == columnOrderDate)
        {
            return orders_[index.row()].orderTime();
        }
        if(index.column() == columnVolumeOrder)
        {
            return orders_[index.row()].volumeOrder();
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
            if(section == columnVolumeOrder)
            {
                return "Объем заказа";
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
    layoutChanged();
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
                        orders_.at(row).deliveryTime(),
                        orders_.at(row).volumeOrder());
    return order;
}

Order TableModelOrder::columnID(const int column) const
{
    Order order = Order(orders_.at(column).from(),
                        orders_.at(column).to(),
                        orders_.at(column).orderTime(),
                        orders_.at(column).deliveryTime(),
                        orders_.at(column).volumeOrder());
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

void TableModelOrder::writeOrdersToFile(const QString &fileName) const
{
    QFile file(fileName + QString(".csv"));

    if(!file.open(QIODevice::WriteOnly))
    {
        qWarning() << QObject::tr("Ошибка открытия файла для записи..");
        return;
    }
    QString data;
    for(int i = 0; i < orders_.size(); i++)
    {
        data = orders_[i].from() + QString(";") + orders_[i].to() + QString(";")
                + QString::number(orders_[i].orderTime()) + QString(";")
                + QString::number(orders_[i].deliveryTime()) + QString(";")
                + QString::number(orders_[i].volumeOrder()) + QString(";");
        data += QString("\n");
        QByteArray dataForWriting = QByteArray().append(data);
        file.write(dataForWriting);
    }
    file.close();

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
