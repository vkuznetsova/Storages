#ifndef ORDER_H

#define ORDER_H

#include <QtCore>

class Order
{
public:
    Order();
    Order(const int deliveryTime,
          const int orderTime,
          const int volumeOrder,
          const QString &from,
          const QString &to);

    Order(const QString &from,
          const QString &to,
          const int orderTime,
          const int deliveryTime);

    int deliveryTime() const;

    int orderTime() const;

    int volumeOrder() const;

    QString from() const;

    QString to() const;

    bool operator ==(const Order &order) const;

private:
    int deliveryTime_;
    int orderTime_;
    int volumeOrder_;
    QString from_;
    QString to_;
};

class OrderPlan : public QHash<int, Order>
{
public:
    OrderPlan& insertInc(const int time,
                         const Order &order)
    {
        insert(time, order);
        return *this;
    }
};

class TreeOrderTable : public QHash<QString, OrderPlan>
{
public:
    int numStorages;
    int rowCount = 0;
    TreeOrderTable& insertInc(const QString &storage,
                              const OrderPlan &plan)
    {
        insert(storage, plan);
        numStorages = this->keys().count();
        rowCount += plan.keys().count();
        return *this;
    }
    QList<Order> toList(const TreeOrderTable &orderTable) const;
};

Q_DECLARE_METATYPE(Order)
Q_DECLARE_METATYPE(OrderPlan)
Q_DECLARE_METATYPE(TreeOrderTable)

#endif // ORDER_H
