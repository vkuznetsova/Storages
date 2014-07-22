#include "TTableModelOrder.h"

TTableModelOrder::TTableModelOrder()
{
}

void TTableModelOrder::TestColumnCount()
{
    TableModelOrder modelOrder;
    QCOMPARE(modelOrder.columnCount(QModelIndex()), 4);
}

void TTableModelOrder::TestHorizontalHeader()
{
    TableModelOrder modelOrder;
    QCOMPARE(modelOrder.headerData(TTableModelOrder::headerColumnFrom, Qt::Horizontal), QVariant("Откуда"));
    QCOMPARE(modelOrder.headerData(TTableModelOrder::headerColumnTo, Qt::Horizontal), QVariant("Куда"));
    QCOMPARE(modelOrder.headerData(TTableModelOrder::headerColumnOrderDate, Qt::Horizontal), QVariant("Дата заказа"));
    QCOMPARE(modelOrder.headerData(TTableModelOrder::headerColumnDeliveryDate, Qt::Horizontal), QVariant("Дата доставки"));
}
