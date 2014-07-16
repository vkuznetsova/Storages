#include "OrderGenerator.h"

OrderGenerator::OrderGenerator()
{
}

void OrderGenerator::calcOrderPlan(TreeOrderTable &orderTable,
                                   const StorageTree &tree,
                                   const QString &storage, const int days)
{
    if(storage.isNull())
    {
        return;
    }
    StorageTreeNode node = tree.node(storage);
    int balance = node.getBalance();
    int expense = node.getExpence();
    int deliveryTime = node.getDeliveryTime();
    int currentBalance = balance;
    Order order;
    OrderPlan orderPlan;
    QString from;
    QString to;
    int volumeOrder = 0;
    for(int i = 1; i <= days; i++)
    {
        currentBalance -= expense;
        qDebug()<<i<<currentBalance;
        if(currentBalance < 0)
        {
            currentBalance = 0;
        }
        if(currentBalance < expense || currentBalance == 0)
        {
            QStringList childs = tree.childrenIDs(storage);
            if(childs.size() == 0)
            {
                from = node.getParent();
                to = node.id();
                qDebug()<< currentBalance;
                volumeOrder = deliveryTime * expense - currentBalance;
                currentBalance = volumeOrder;
                if(i - deliveryTime <= 0)
                {
                    continue;
                }
                order = Order(i, i - deliveryTime, volumeOrder, from, to);
                orderPlan = orderPlan.insertInc(i - deliveryTime, order);
            }
            //            else
            //            {
            //                int expensesChilds = 0;
            //                for(int j = 0; j < childs.size(); j++)
            //                {
            //                    from = node.getParent();
            //                    to = node.id();
            //                    expensesChilds += tree.node(childs[j]).getExpence();
            //                }
            //                volumeOrder = deliveryTime * expense + expensesChilds;
            //                order = Order(i, i - deliveryTime, volumeOrder, from, to);
            //                orderPlan = OrderPlan().insertInc(i - deliveryTime, order);
            //            }
        }
        if(order.deliveryTime() == node.getDeliveryTime() + order.orderTime())
        {
            node.setBalance(order.volumeOrder());
        }
    }
    if(orderPlan.keys().size() == 0)
    {
        return;
    }

    orderTable.insertInc(storage, orderPlan);

    qDebug()<< orderTable.keys();
    foreach (const int it, orderPlan.keys())
    {
        qDebug()<< it
                << order.deliveryTime()
                << order.orderTime()
                << order.volumeOrder()
                << order.from()
                << order.to();
    }
}
