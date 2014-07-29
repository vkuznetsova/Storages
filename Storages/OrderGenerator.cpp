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
        if(i - deliveryTime <= 0)
        {
            currentBalance -= expense;
            continue;
        }
        if(currentBalance < 0)
        {
            currentBalance = 0;
        }
        if(currentBalance == 0 || currentBalance < expense)
        {
            from = node.getParent();
            to = node.id();
            volumeOrder = deliveryTime * expense - currentBalance;
            int deliveryDate = i;
            int orderDate = deliveryDate - deliveryTime;
            //            qWarning()<<"data of children";
            foreach (const QString &stor, orderTable.keys())
            {
                foreach (const int it, orderTable.value(stor).keys())
                {
                    if(deliveryDate == orderTable.value(stor).value(it).orderTime()
                            && orderTable.value(stor).value(it).from() == storage)
                    {
                        volumeOrder += orderTable.value(stor).value(it).volumeOrder();
                        //                        qWarning()<< orderTable.value(stor).value(it).deliveryTime()
                        //                                  << orderTable.value(stor).value(it).orderTime()
                        //                                  << orderTable.value(stor).value(it).volumeOrder()
                        //                                  << orderTable.value(stor).value(it).from()
                        //                                  << orderTable.value(stor).value(it).to()
                        //                                  << volumeOrder;
                        currentBalance = currentBalance - orderTable.value(stor).value(it).volumeOrder();
                    }
                }
            }
            order = Order(deliveryDate, orderDate, volumeOrder, from, to);
            orderPlan = orderPlan.insertInc(orderDate, order);
            //            qWarning()<<"from"<<from
            //                     <<"to"<<to
            //                    <<"deliveryDate"<<deliveryDate
            //                   <<"orderDate"<<orderDate
            //                  <<"volumeOrder"<<order.volumeOrder();
            countOrder++;
            currentBalance += volumeOrder;
            //            qWarning()<<"currentBalance"<<currentBalance;
        }
        else
        {
            from = node.getParent();
            to = node.id();
            int deliveryDate = i;
            int orderDate = deliveryDate - deliveryTime;
            foreach (const QString &stor, orderTable.keys())
            {
                foreach (const int it, orderTable.value(stor).keys())
                {
                    if(deliveryDate == orderTable.value(stor).value(it).orderTime())
                    {
                        volumeOrder += orderTable.value(stor).value(it).volumeOrder();
                        currentBalance = currentBalance - orderTable.value(stor).value(it).volumeOrder();
                        countOrder++;
                    }
                }
            }
            order = Order(deliveryDate, orderDate, 0, from, to);
            orderPlan = orderPlan.insertInc(orderDate, order);
            currentBalance += volumeOrder;
        }
        volumeOrder = 0;
        if(order.deliveryTime() == node.getDeliveryTime() + order.orderTime())
        {
            node.setBalance(currentBalance);
        }
        currentBalance -= expense;
    }
    if(countOrder == 0)
    {
        return;
    }
    orderTable.insertInc(storage, orderPlan);
}

void OrderGenerator::calcOrderPlans(TreeOrderTable &orderTable,
                                    const StorageTree &tree,
                                    const int days)
{
    QList<QString> nodes = tree.walkUpTree();
    for(int i = 0; i < nodes.size(); i++)
    {
        calcOrderPlan(orderTable, tree, nodes[i], days);
    }

}
