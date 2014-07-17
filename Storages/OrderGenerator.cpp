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
        qWarning()<<i;
        if(i - deliveryTime <= 0)
        {
            qWarning()<< "invalid dateOrder: "<< i - deliveryTime;
            currentBalance -= expense;
            qWarning()<<"current balance = "<< currentBalance;
            continue;
        }
        if(currentBalance < 0)
        {
            qWarning()<<"negative balance"<< currentBalance;
            currentBalance = 0;
        }
        qDebug()<<"balance before order"<<currentBalance;
        if(currentBalance == 0 || currentBalance < expense)
        {
            qWarning()<<"order"<< currentBalance;
            QStringList children = tree.childrenIDs(storage);
            if(children.size() == 0)
            {
                qWarning()<<"is leaf"<< children.size();
                from = node.getParent();
                to = node.id();
                volumeOrder = deliveryTime * expense - currentBalance;
                int deliveryDate = i;
                int orderDate = i - deliveryTime;
                order = Order(deliveryDate, orderDate, volumeOrder, from, to);
                orderPlan = orderPlan.insertInc(i - deliveryTime, order);
                qWarning()<<"from"<<from
                         <<"to"<<to
                        <<"deliveryDate"<<deliveryDate
                       <<"orderDate"<<orderDate
                      <<"volumeOrder"<<order.volumeOrder();

                currentBalance = volumeOrder;
                qWarning()<<"currentBalance"<<currentBalance;
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
            //                volumeOrder = deliveryTime * expense + expensesChilds - currentBalance;
            //                currentBalance = volumeOrder;
            //                order = Order(i, i - deliveryTime, volumeOrder, from, to);
            //                orderPlan = OrderPlan().insertInc(i - deliveryTime, order);
            //            }
        }
        volumeOrder = 0;
        if(order.deliveryTime() == node.getDeliveryTime() + order.orderTime())
        {
            qWarning()<<"orderDate"<<order.deliveryTime();
            node.setBalance(currentBalance);
            qWarning()<<"balance"<<node.getBalance()
                     <<"currentBalance"<<currentBalance;
        }
        currentBalance -= expense;
    }
    if(orderPlan.keys().size() == 0)
    {
        qWarning()<<"not exist order"<<orderPlan.keys().size();
        return;
    }

    orderTable.insertInc(storage, orderPlan);
    qWarning()<<"result";
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
