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
            from = node.getParent();
            to = node.id();
            volumeOrder = deliveryTime * expense - currentBalance;
            int deliveryDate = i;
            int orderDate = deliveryDate - deliveryTime;
            qWarning()<<"data of children";
            foreach (const QString &stor, orderTable.keys())
            {
                foreach (const int it, orderTable.value(stor).keys())
                {
                    if(deliveryDate == orderTable.value(stor).value(it).orderTime()
                            && orderTable.value(stor).value(it).from() == storage)
                    {
                        volumeOrder += orderTable.value(stor).value(it).volumeOrder();
                        qWarning()<< orderTable.value(stor).value(it).deliveryTime()
                                  << orderTable.value(stor).value(it).orderTime()
                                  << orderTable.value(stor).value(it).volumeOrder()
                                  << orderTable.value(stor).value(it).from()
                                  << orderTable.value(stor).value(it).to()
                                  << volumeOrder;
                        currentBalance = currentBalance - orderTable.value(stor).value(it).volumeOrder();
                    }
                }
            }
            order = Order(deliveryDate, orderDate, volumeOrder, from, to);
            orderPlan = orderPlan.insertInc(orderDate, order);
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
            from = node.getParent();
            to = node.id();
            int deliveryDate = i;
            int orderDate = deliveryDate - deliveryTime;
            qWarning()<<"data of children";
            foreach (const QString &stor, orderTable.keys())
            {
                foreach (const int it, orderTable.value(stor).keys())
                {
                    if(deliveryDate == orderTable.value(stor).value(it).orderTime())
                    {
                        volumeOrder += orderTable.value(stor).value(it).volumeOrder();
                        qWarning()<< orderTable.value(stor).value(it).deliveryTime()
                                  << orderTable.value(stor).value(it).orderTime()
                                  << orderTable.value(stor).value(it).volumeOrder()
                                  << orderTable.value(stor).value(it).from()
                                  << orderTable.value(stor).value(it).to()
                                  << volumeOrder;
                        currentBalance = currentBalance - orderTable.value(stor).value(it).volumeOrder();
                        countOrder++;
                    }
                }
            }
            order = Order(deliveryDate, orderDate, 0, from, to);
            orderPlan = orderPlan.insertInc(orderDate, order);
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
        currentBalance -= expense;
        qWarning()<<"the end day number"<<i;
        qWarning()<<"balance in the end day"<<currentBalance;
    }
    if(countOrder == 0)
    {
        qWarning()<<"not exist order"<<orderPlan.keys().size();
        return;
    }
    orderTable.insertInc(storage, orderPlan);
}

void OrderGenerator::calcOrderPlans(TreeOrderTable &orderTable,
                                    const StorageTree &tree,
                                    const int days)
{
    QList<QString> nodes = tree.walkUpTree();
    qWarning()<<"nodes"<<nodes;
    for(int i = 0; i < nodes.size(); i++)
    {
        qWarning()<<"nodes[i]"<<nodes[i];
        calcOrderPlan(orderTable, tree, nodes[i], days);
    }

}
