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
