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

void TTableModelOrder::TestRowCount_data()
{
    QTest::addColumn<TreeOrderTable>("orderTable");
    QTest::addColumn<int>("rowCount");

    QTest::newRow("empty")<< TreeOrderTable()
                          << 0;

    QTest::newRow("single1")<< (TreeOrderTable()
                                .insertInc("s1", OrderPlan()
                                           .insertInc(1, Order(1, 1, 0, QString(), "s1"))))
                            << 1;

    QTest::newRow("two1")
            << (TreeOrderTable()
                .insertInc("s1", OrderPlan()
                           .insertInc(1, Order(2, 1, 1, QString(), "s1"))
                           .insertInc(2, Order(3, 2, 1, QString(), "s1"))))
            << 2;

    QTest::newRow("two2")
            << (TreeOrderTable()
                .insertInc("s1", OrderPlan()
                           .insertInc(1, Order(2, 1, 2, QString(), "s1")))
                .insertInc("s2", OrderPlan()
                           .insertInc(1, Order(3, 2, 1, "s1", "s2"))))
            << 2;


    QTest::newRow("three1")
            << (TreeOrderTable()
                .insertInc("s1", OrderPlan()
                           .insertInc(1, Order(2, 1, 1, QString(), "s1"))
                           .insertInc(2, Order(3, 2, 5, QString(), "s1"))
                           .insertInc(3, Order(4, 3, 5, QString(), "s1"))))
            << 3;

    QTest::newRow("three2")
            << (TreeOrderTable()
                .insertInc("s1", OrderPlan()
                           .insertInc(1, Order(3, 1, 2, QString(), "s1")))
                .insertInc("s2", OrderPlan()
                           .insertInc(1, Order(2, 1, 1, "s1", "s2"))
                           .insertInc(2, Order(3, 2, 1, "s1", "s2"))))
            << 3;


    QTest::newRow("four")
            << (TreeOrderTable()
                .insertInc("s1", OrderPlan()
                           .insertInc(1, Order(2, 1, 1, QString(), "s1"))
                           .insertInc(2, Order(3, 2, 5, QString(), "s1"))
                           .insertInc(3, Order(4, 3, 5, QString(), "s1"))
                           .insertInc(4, Order(5, 4, 5, QString(), "s1"))))
            << 4;

    QTest::newRow("five")
            << (TreeOrderTable()
                .insertInc("s1", OrderPlan()
                           .insertInc(1, Order(2, 1, 1, QString(), "s1"))
                           .insertInc(2, Order(3, 2, 5, QString(), "s1"))
                           .insertInc(3, Order(4, 3, 5, QString(), "s1"))
                           .insertInc(4, Order(5, 4, 5, QString(), "s1"))
                           .insertInc(5, Order(6, 5, 5, QString(), "s1"))))
            << 5;
}

void TTableModelOrder::TestRowCount()
{
    QFETCH(TreeOrderTable, orderTable);
    QFETCH(int, rowCount);

    TableModelOrder model(orderTable);

    QCOMPARE(model.rowCount(QModelIndex()), rowCount);

}
