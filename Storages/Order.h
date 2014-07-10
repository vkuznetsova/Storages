#ifndef ORDER_H

#define ORDER_H

#include <QtCore>

class Order
{
public:
    Order();
    Order(const int deliveryTime = 0, const int orderTime = 0,
          const int volumeOrder = 0, const QString &from = QString(), const QString &to = QString());

    void setDeliveryTime(const int deliveryTime);
    int getDeliveryTime() const;

    void setOrderTime(const int orderTime);
    int getOrderTime() const;

    void setVolumeOrder(const int volumeOrder);
    int getVolumeOrder() const;

    void setFrom(const QString &from = QString());
    QString getFrom();

    void setTo(const QString &to = QString());
    QString getTo();

private:
    int deliveryTime_;
    int orderTime_;
    int volumeOrder_;
    QString from_;
    QString to_;
};

#endif // ORDER_H
