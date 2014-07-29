#include "Order.h"

Order::Order()
{
}

Order::Order(const int deliveryTime, const int orderTime, const int volumeOrder,
             const QString &from, const QString &to):
    deliveryTime_(deliveryTime),
    orderTime_(orderTime),
    volumeOrder_(volumeOrder),
    from_(from),
    to_(to)
{
}

Order::Order(const QString &from, const QString &to, const int orderTime, const int deliveryTime, const int volumeOrder)
{
    from_ = from;
    to_ = to;
    orderTime_ = orderTime;
    deliveryTime_ = deliveryTime;
    volumeOrder_ = volumeOrder;
}

int Order::deliveryTime() const
{
    return deliveryTime_;
}

int Order::orderTime() const
{
    return orderTime_;
}

int Order::volumeOrder() const
{
    return volumeOrder_;
}

QString Order::from() const
{
    return from_;
}

QString Order::to() const
{
    return to_;
}

bool Order::operator ==(const Order &order) const
{
    return deliveryTime_ == order.deliveryTime_
            && orderTime_ == order.orderTime_
            && volumeOrder_ == order.volumeOrder_
            && from_ == order.from_
            && to_ == order.to_;
}


QList<Order> TreeOrderTable::toList(const TreeOrderTable &orderTable) const
{
    QList<Order> listOrders;
    foreach (const QString &stor, orderTable.keys())
    {
        foreach (const int day, orderTable.value(stor).keys())
        {
            listOrders<<orderTable.value(stor).value(day);
        }
    }

    return listOrders;
}
