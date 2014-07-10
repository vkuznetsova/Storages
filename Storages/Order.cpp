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

void Order::setDeliveryTime(const int deliveryTime)
{
    deliveryTime_ = deliveryTime;
}

int Order::getDeliveryTime() const
{
    return deliveryTime_;
}

void Order::setOrderTime(const int orderTime)
{
    orderTime_ = orderTime;
}

int Order::getOrderTime() const
{
    return orderTime_;
}

void Order::setVolumeOrder(const int volumeOrder)
{
    volumeOrder_ = volumeOrder;
}

int Order::getVolumeOrder() const
{
    return volumeOrder_;
}

void Order::setFrom(const QString &from)
{
    from_ = from;
}

QString Order::getFrom()
{
    return from_;
}

void Order::setTo(const QString &to)
{
    to_ = to;
}

QString Order::getTo()
{
    return to_;
}
