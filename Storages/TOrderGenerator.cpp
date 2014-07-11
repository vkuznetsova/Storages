#include "TOrderGenerator.h"

TOrderGenerator::TOrderGenerator()
{
}

void TOrderGenerator::TestCalcOrderPlan_data()
{
    QTest::addColumn<TreeOrderTable>("orderTable");
    QTest::addColumn<StorageTree>("tree");
    QTest::addColumn<QString>("storage");
    QTest::addColumn<int>("days");
    QTest::addColumn<TreeOrderTable>("expected");

    QTest::newRow("empty") << TreeOrderTable()
                           << StorageTree()
                           << QString()
                           << 0
                           << TreeOrderTable();

    QTest::newRow("single1")
            << TreeOrderTable()
            << (StorageTree().setRoot("s1")
                .setBalance("s1", 0)
                .setExpense("s1", 1)
                .setDeliveryTime("s1", 0))
            << "s1"
            << 1
            << (TreeOrderTable()
                .insertInc("s1", OrderPlan()
                           .insertInc(1, Order(1, 1, 0, QString(), "s1"))));

    QTest::newRow("single2")
            << TreeOrderTable()
            << (StorageTree().setRoot("s1")
                .setBalance("s1", 0)
                .setExpense("s1", 1)
                .setDeliveryTime("s1", 1))
            << "s1"
            << 2
            << (TreeOrderTable()
                .insertInc("s1", OrderPlan()
                           .insertInc(1, Order(2, 1, 1, QString(), "s1"))));

    QTest::newRow("single3")
            << TreeOrderTable()
            << (StorageTree().setRoot("s1")
                .setBalance("s1", 0)
                .setExpense("s1", 1)
                .setDeliveryTime("s1", 1))
            << "s1"
            << 3
            << (TreeOrderTable()
                .insertInc("s1", OrderPlan()
                           .insertInc(1, Order(2, 1, 1, QString(), "s1")))
                .insertInc("s1", OrderPlan()
                           .insertInc(2, Order(3, 2, 1, QString(), "s1"))));

    QTest::newRow("single4")
            << TreeOrderTable()
            << (StorageTree().setRoot("s1")
                .setBalance("s1", 2)
                .setExpense("s1", 1)
                .setDeliveryTime("s1", 1))
            << "s1"
            << 3
            << (TreeOrderTable()
                .insertInc("s1", OrderPlan()
                           .insertInc(1, Order(2, 1, 1, QString(), "s1")))
                .insertInc("s1", OrderPlan()
                           .insertInc(2, Order(3, 2, 1, QString(), "s1"))));

    QTest::newRow("single5")
            << TreeOrderTable()
            << (StorageTree().setRoot("s1")
                .setBalance("s1", 2)
                .setExpense("s1", 3)
                .setDeliveryTime("s1", 1))
            << "s1"
            << 3
            << (TreeOrderTable()
                .insertInc("s1", OrderPlan()
                           .insertInc(1, Order(2, 1, 3, QString(), "s1")))
                .insertInc("s1", OrderPlan()
                           .insertInc(2, Order(3, 2, 3, QString(), "s1"))));

    QTest::newRow("single6")
            << TreeOrderTable()
            << (StorageTree().setRoot("s1")
                .setBalance("s1", 2)
                .setExpense("s1", 3)
                .setDeliveryTime("s1", 2))
            << "s1"
            << 3
            << (TreeOrderTable()
                .insertInc("s1", OrderPlan()
                           .insertInc(1, Order(3, 1, 6, QString(), "s1"))));
}

void TOrderGenerator::TestCalcOrderPlan()
{
    QFETCH(TreeOrderTable, orderTable);
    QFETCH(StorageTree, tree);
    QFETCH(QString, storage);
    QFETCH(int, days);
    QFETCH(TreeOrderTable, expected);

    OrderGenerator::calcOrderPlan(orderTable, tree, storage, days);

    QCOMPARE(orderTable, expected);
}
