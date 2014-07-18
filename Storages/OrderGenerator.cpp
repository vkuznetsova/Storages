#include "OrderGenerator.h"

OrderGenerator::OrderGenerator()
{
}

void OrderGenerator::calcOrderPlan(TreeOrderTable &orderTable,
                                   const StorageTree &tree,
                                   const QString &storage, const int days)
{
    qWarning()<< "input:";
    foreach (const QString &stor, orderTable.keys())
    {
        foreach (const int it, orderTable.value(stor).keys())
        {
            qWarning()<< orderTable.value(stor).value(it).deliveryTime()
                      << orderTable.value(stor).value(it).orderTime()
                      << orderTable.value(stor).value(it).volumeOrder()
                      << orderTable.value(stor).value(it).from()
                      << orderTable.value(stor).value(it).to();
        }
    }
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
    int countOrder = 0;
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
                countOrder++;
                currentBalance += volumeOrder;
                qWarning()<<"currentBalance"<<currentBalance;
            }
            else
            {
                qWarning()<<"children = "<< children.size();
                int volumeOrderChild = 0;
                for(int j = 0; j < children.size(); j++)
                {
                    qWarning()<< children[j];
                    qWarning()<< "order of children"
                              << orderTable.keys()
                              << orderPlan.keys()
                              << order.deliveryTime()
                              << order.orderTime()
                              << order.volumeOrder()
                              << order.from()
                              << order.to();
                    from = node.getParent();
                    to = node.id();
                    volumeOrderChild = orderTable.value(children[j]).value(i).volumeOrder();
                }
                volumeOrder = deliveryTime * expense + volumeOrderChild - currentBalance;
                currentBalance = volumeOrder;
                order = Order(i, i - deliveryTime, volumeOrder, from, to);
                orderPlan = OrderPlan().insertInc(i - deliveryTime, order);
            }
        }
        else
        {
            from = node.getParent();
            to = node.id();
            int deliveryDate = i;
            int orderDate = i - deliveryTime;
            order = Order(deliveryDate, orderDate, 0, from, to);
            orderPlan = orderPlan.insertInc(i - deliveryTime, order);
            qWarning()<<"from"<<from
                     <<"to"<<to
                    <<"deliveryDate"<<deliveryDate
                   <<"orderDate"<<orderDate
                  <<"volumeOrder"<<order.volumeOrder();
            currentBalance += volumeOrder;
            qWarning()<<"current balance"<<currentBalance;
        }
        volumeOrder = 0;
        if(order.deliveryTime() == node.getDeliveryTime() + order.orderTime())
        {
            qWarning()<<"orderDate"<<order.deliveryTime();
            node.setBalance(currentBalance);
            qWarning()<<"balance"<<node.getBalance()
                     <<"currentBalance"<<currentBalance;
        }
        qWarning()<<"the end day number"<<i;
        currentBalance -= expense;
        qWarning()<<currentBalance;
    }
    if(countOrder == 0)
    {
        qWarning()<<"not exist order"<<orderPlan.keys().size();
        return;
    }
    orderTable.insertInc(storage, orderPlan);
}
