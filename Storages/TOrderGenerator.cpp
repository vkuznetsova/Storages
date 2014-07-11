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

    QTest::newRow("single")
            << TreeOrderTable()
            << (StorageTree().setRoot("s1")
                .setBalance("s1", 0)
                .setExpense("s1", 1)
                .setDeliveryTime("s1", 1))
            << "s1"
            << 1
            << (TreeOrderTable()
                .insertInc("s1", OrderPlan()
                           .insertInc(1, Order(2, 1, 1, QString(), "s1"))));

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
