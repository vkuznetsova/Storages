#include "OrderGenerator.h"

OrderGenerator::OrderGenerator()
{
}

void OrderGenerator::calcOrderPlan(TreeOrderTable &orderTable,
                                   const StorageTree &tree,
                                   const QString &storage, const int days)
{
    StorageTreeNode node = tree.node(storage);
    int balance = node.getBalance();
    int expense = node.getExpence();
    int deliveryTime = node.getDeliveryTime();
    int currentBalance = balance;
    Order order;
    OrderPlan orderPlan;
    for(int i = 1; i <= days; i++)
    {
        currentBalance -= expense;
        if(currentBalance < 0)
        {
            currentBalance = 0;
        }
        if(currentBalance == 0)
        {
            const QString from = node.getParent();
            const QString to = node.id();
            const int volumeOrder = deliveryTime * expense;
            if((i - deliveryTime) < 0)
            {
                continue;
            }
            order = Order(i, i - deliveryTime, volumeOrder, from, to);
            orderPlan = OrderPlan().insertInc(i - deliveryTime, order);
            orderTable.insertInc(storage, orderPlan);
        }
        if(order.deliveryTime() == node.getDeliveryTime() + order.orderTime())
        {
            node.setBalance(currentBalance + order.volumeOrder());
        }
    }
}
