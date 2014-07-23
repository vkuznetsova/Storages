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
                           .insertInc(1, Order(2, 1, 1, QString(), "s1"))
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
                           .insertInc(1, Order(2, 1, 0, QString(), "s1"))
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
                           .insertInc(1, Order(2, 1, 3, QString(), "s1"))
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

    QTest::newRow("single7")
            << TreeOrderTable()
            << (StorageTree().setRoot("s1")
                .setBalance("s1", 12)
                .setExpense("s1", 3)
                .setDeliveryTime("s1", 2))
            << "s1"
            << 3
            << TreeOrderTable();

    QTest::newRow("single8")
            << TreeOrderTable()
            << (StorageTree().setRoot("s1")
                .setBalance("s1", 6)
                .setExpense("s1", 3)
                .setDeliveryTime("s1", 2))
            << "s1"
            << 3
            << TreeOrderTable()
               .insertInc("s1", OrderPlan()
                          .insertInc(1, Order(3, 1, 6, QString(), "s1")));

    QTest::newRow("single9")
            << TreeOrderTable()
            << (StorageTree().setRoot("s1")
                .setBalance("s1", 7)
                .setExpense("s1", 3)
                .setDeliveryTime("s1", 2))
            << "s1"
            << 3
            << TreeOrderTable()
               .insertInc("s1", OrderPlan()
                          .insertInc(1, Order(3, 1, 5, QString(), "s1")));

    QTest::newRow("single10")
            << TreeOrderTable()
            << (StorageTree().setRoot("s1")
                .setBalance("s1", 9)
                .setExpense("s1", 5)
                .setDeliveryTime("s1", 1))
            << "s1"
            << 6
            << (TreeOrderTable()
                .insertInc("s1", OrderPlan()
                           .insertInc(1, Order(2, 1, 1, QString(), "s1"))
                           .insertInc(2, Order(3, 2, 5, QString(), "s1"))
                           .insertInc(3, Order(4, 3, 5, QString(), "s1"))
                           .insertInc(4, Order(5, 4, 5, QString(), "s1"))
                           .insertInc(5, Order(6, 5, 5, QString(), "s1"))));

    QTest::newRow("single11")
            << TreeOrderTable()
            << (StorageTree().setRoot("s1")
                .setBalance("s1", 9)
                .setExpense("s1", 5)
                .setDeliveryTime("s1", 2))
            << "s1"
            << 6
            << (TreeOrderTable()
                .insertInc("s1", OrderPlan()
                           .insertInc(1, Order(3, 1, 10, QString(), "s1"))
                           .insertInc(2, Order(4, 2, 0, QString(), "s1"))
                           .insertInc(3, Order(5, 3, 10, QString(), "s1"))
                           .insertInc(4, Order(6, 4, 0, QString(), "s1"))));

    QTest::newRow("single12")
            << TreeOrderTable()
            << (StorageTree().setRoot("s1")
                .setBalance("s1", 13)
                .setExpense("s1", 5)
                .setDeliveryTime("s1", 2))
            << "s1"
            << 6
            << (TreeOrderTable()
                .insertInc("s1", OrderPlan()
                           .insertInc(1, Order(3, 1, 7, QString(), "s1"))
                           .insertInc(2, Order(4, 2, 0, QString(), "s1"))
                           .insertInc(3, Order(5, 3, 10, QString(), "s1"))
                           .insertInc(4, Order(6, 4, 0, QString(), "s1"))));

    QTest::newRow("two-nodes1")
            << (TreeOrderTable()
                .insertInc("s2", OrderPlan()
                           .insertInc(1, Order(3, 2, 1, "s1", "s2"))))
            << (StorageTree().setRoot("s1")
                .addChild("s1", "s2"))
               .setBalance("s1", 0)
               .setExpense("s1", 1)
               .setDeliveryTime("s1", 1)
               .setBalance("s2", 0)
               .setExpense("s2", 1)
               .setDeliveryTime("s2", 1)
            << "s1"
            << 2
            << (TreeOrderTable()
                .insertInc("s1", OrderPlan()
                           .insertInc(1, Order(2, 1, 2, QString(), "s1")))
                .insertInc("s2", OrderPlan()
                           .insertInc(1, Order(3, 2, 1, "s1", "s2"))));

    QTest::newRow("two-nodes2")
            << (TreeOrderTable()
                .insertInc("s2", OrderPlan()
                           .insertInc(1, Order(2, 1, 1, "s1", "s2"))
                           .insertInc(2, Order(3, 2, 1, "s1", "s2"))))
            << (StorageTree().setRoot("s1")
                .addChild("s1", "s2"))
               .setBalance("s1", 1)
               .setExpense("s1", 1)
               .setDeliveryTime("s1", 2)
               .setBalance("s2", 0)
               .setExpense("s2", 1)
               .setDeliveryTime("s2", 1)
            << "s1"
            << 3
            << (TreeOrderTable()
                .insertInc("s1", OrderPlan()
                           .insertInc(1, Order(3, 1, 2, QString(), "s1")))
                .insertInc("s2", OrderPlan()
                           .insertInc(1, Order(2, 1, 1, "s1", "s2"))
                           .insertInc(2, Order(3, 2, 1, "s1", "s2"))));

    QTest::newRow("two-nodes3")
            << (TreeOrderTable()
                .insertInc("s2", OrderPlan()
                           .insertInc(1, Order(4, 1, 3, "s1", "s2"))
                           .insertInc(2, Order(5, 2, 0, "s1", "s2"))))
            << (StorageTree().setRoot("s1")
                .addChild("s1", "s2"))
               .setBalance("s1", 3)
               .setExpense("s1", 1)
               .setDeliveryTime("s1", 2)
               .setBalance("s2", 2)
               .setExpense("s2", 1)
               .setDeliveryTime("s2", 3)
            << "s1"
            << 5
            << (TreeOrderTable()
                .insertInc("s1", OrderPlan()
                           .insertInc(1, Order(3, 1, 0, QString(), "s1"))
                           .insertInc(2, Order(4, 2, 2, QString(), "s1"))
                           .insertInc(3, Order(5, 3, 0, QString(), "s1")))
                .insertInc("s2", OrderPlan()
                           .insertInc(1, Order(4, 1, 3, "s1", "s2"))
                           .insertInc(2, Order(5, 2, 0, "s1", "s2"))));

    QTest::newRow("two-nodes4")
            << (TreeOrderTable()
                .insertInc("s2", OrderPlan()
                           .insertInc(1, Order(4, 1, 30, "s1", "s2"))
                           .insertInc(2, Order(5, 2, 0, "s1", "s2"))))
            << (StorageTree().setRoot("s1")
                .addChild("s1", "s2"))
               .setBalance("s1", 3)
               .setExpense("s1", 5)
               .setDeliveryTime("s1", 3)
               .setBalance("s2", 2)
               .setExpense("s2", 10)
               .setDeliveryTime("s2", 3)
            << "s1"
            << 5
            << (TreeOrderTable()
                .insertInc("s1", OrderPlan()
                           .insertInc(1, Order(4, 1, 15, QString(), "s1"))
                           .insertInc(2, Order(5, 2, 0, QString(), "s1")))
                .insertInc("s2", OrderPlan()
                           .insertInc(1, Order(4, 1, 30, "s1", "s2"))
                           .insertInc(2, Order(5, 2, 0, "s1", "s2"))));

    QTest::newRow("two-nodes5")
            << (TreeOrderTable()
                .insertInc("s2", OrderPlan()
                           .insertInc(1, Order(6, 1, 50, "s1", "s2"))
                           .insertInc(2, Order(7, 2, 0, "s1", "s2"))))
            << (StorageTree().setRoot("s1")
                .addChild("s1", "s2"))
               .setBalance("s1", 5)
               .setExpense("s1", 3)
               .setDeliveryTime("s1", 1)
               .setBalance("s2", 1)
               .setExpense("s2", 10)
               .setDeliveryTime("s2", 5)
            << "s1"
            << 7
            << (TreeOrderTable()
                .insertInc("s1", OrderPlan()
                           .insertInc(1, Order(2, 1, 1, QString(), "s1"))
                           .insertInc(2, Order(3, 2, 3, QString(), "s1"))
                           .insertInc(3, Order(4, 3, 3, QString(), "s1"))
                           .insertInc(4, Order(5, 4, 3, QString(), "s1"))
                           .insertInc(5, Order(6, 5, 3, QString(), "s1"))
                           .insertInc(6, Order(7, 6, 3, QString(), "s1")))
                .insertInc("s2", OrderPlan()
                           .insertInc(1, Order(6, 1, 50, "s1", "s2"))
                           .insertInc(2, Order(7, 2, 0, "s1", "s2"))));

    QTest::newRow("two-nodes6")
            << (TreeOrderTable()
                .insertInc("s2", OrderPlan()
                           .insertInc(1, Order(4, 1, 30, "s1", "s2"))
                           .insertInc(2, Order(5, 2, 0, "s1", "s2"))
                           .insertInc(3, Order(6, 3, 0, "s1", "s2"))
                           .insertInc(4, Order(7, 4, 30, "s1", "s2"))))
            << (StorageTree().setRoot("s1")
                .addChild("s1", "s2"))
               .setBalance("s1", 5)
               .setExpense("s1", 5)
               .setDeliveryTime("s1", 1)
               .setBalance("s2", 1)
               .setExpense("s2", 10)
               .setDeliveryTime("s2", 3)
            << "s1"
            << 7
            << (TreeOrderTable()
                .insertInc("s1", OrderPlan()
                           .insertInc(1, Order(2, 1, 5, QString(), "s1"))
                           .insertInc(2, Order(3, 2, 5, QString(), "s1"))
                           .insertInc(3, Order(4, 3, 35, QString(), "s1"))
                           .insertInc(4, Order(5, 4, 5, QString(), "s1"))
                           .insertInc(5, Order(6, 5, 5, QString(), "s1"))
                           .insertInc(6, Order(7, 6, 5, QString(), "s1")))
                .insertInc("s2", OrderPlan()
                           .insertInc(1, Order(4, 1, 30, "s1", "s2"))
                           .insertInc(2, Order(5, 2, 0, "s1", "s2"))
                           .insertInc(3, Order(6, 3, 0, "s1", "s2"))
                           .insertInc(4, Order(7, 4, 30, "s1", "s2"))));

    QTest::newRow("two-nodes7")
            << (TreeOrderTable()
                .insertInc("s2", OrderPlan()
                           .insertInc(1, Order(6, 1, 50, "s1", "s2"))
                           .insertInc(2, Order(7, 2, 0, "s1", "s2"))))
            << (StorageTree().setRoot("s1")
                .addChild("s1", "s2"))
               .setBalance("s1", 0)
               .setExpense("s1", 1)
               .setDeliveryTime("s1", 3)
               .setBalance("s2", 0)
               .setExpense("s2", 10)
               .setDeliveryTime("s2", 5)
            << "s1"
            << 7
            << (TreeOrderTable()
                .insertInc("s1", OrderPlan()
                           .insertInc(1, Order(4, 1, 3, QString(), "s1"))
                           .insertInc(2, Order(5, 2, 0, QString(), "s1"))
                           .insertInc(3, Order(6, 3, 0, QString(), "s1"))
                           .insertInc(4, Order(7, 4, 3, QString(), "s1")))
                .insertInc("s2", OrderPlan()
                           .insertInc(1, Order(6, 1, 50, "s1", "s2"))
                           .insertInc(2, Order(7, 2, 0, "s1", "s2"))));

    QTest::newRow("two-nodes8")
            << (TreeOrderTable()
                .insertInc("s2", OrderPlan()
                           .insertInc(1, Order(2, 1, 5, "s1", "s2"))
                           .insertInc(2, Order(3, 2, 5, "s1", "s2"))
                           .insertInc(3, Order(4, 3, 5, "s1", "s2"))
                           .insertInc(4, Order(5, 4, 5, "s1", "s2"))
                           .insertInc(5, Order(6, 5, 5, "s1", "s2"))
                           .insertInc(6, Order(7, 6, 5, "s1", "s2"))))
            << (StorageTree().setRoot("s1")
                .addChild("s1", "s2"))
               .setBalance("s1", 100)
               .setExpense("s1", 1)
               .setDeliveryTime("s1", 3)
               .setBalance("s2", 0)
               .setExpense("s2", 5)
               .setDeliveryTime("s2", 1)
            << "s1"
            << 7
            << (TreeOrderTable()
                .insertInc("s1", OrderPlan()
                           .insertInc(1, Order(4, 1, 0, QString(), "s1"))
                           .insertInc(2, Order(5, 2, 0, QString(), "s1"))
                           .insertInc(3, Order(6, 3, 0, QString(), "s1"))
                           .insertInc(4, Order(7, 4, 0, QString(), "s1")))
                .insertInc("s2", OrderPlan()
                           .insertInc(1, Order(2, 1, 5, "s1", "s2"))
                           .insertInc(2, Order(3, 2, 5, "s1", "s2"))
                           .insertInc(3, Order(4, 3, 5, "s1", "s2"))
                           .insertInc(4, Order(5, 4, 5, "s1", "s2"))
                           .insertInc(5, Order(6, 5, 5, "s1", "s2"))
                           .insertInc(6, Order(7, 6, 5, "s1", "s2"))));

    QTest::newRow("three-nodes1")
            << (TreeOrderTable()
                .insertInc("s2", OrderPlan()
                           .insertInc(1, Order(6, 1, 50, "s1", "s2"))
                           .insertInc(2, Order(7, 2, 0, "s1", "s2")))
                .insertInc("s3", OrderPlan()
                           .insertInc(1, Order(4, 1, 18, "s1", "s3"))
                           .insertInc(2, Order(5, 2, 0, "s1", "s3"))
                           .insertInc(3, Order(6, 3, 0, "s1", "s3"))
                           .insertInc(4, Order(7, 4, 18, "s1", "s3"))))
            << (StorageTree().setRoot("s1")
                .addChild("s1", "s2")
                .addChild("s1", "s3"))
               .setBalance("s1", 0)
               .setExpense("s1", 1)
               .setDeliveryTime("s1", 3)
               .setBalance("s2", 0)
               .setExpense("s2", 10)
               .setDeliveryTime("s2", 5)
               .setBalance("s3", 0)
               .setExpense("s3", 6)
               .setDeliveryTime("s3", 3)
            << "s1"
            << 7
            << (TreeOrderTable()
                .insertInc("s1", OrderPlan()
                           .insertInc(1, Order(4, 1, 21, QString(), "s1"))
                           .insertInc(2, Order(5, 2, 0, QString(), "s1"))
                           .insertInc(3, Order(6, 3, 0, QString(), "s1"))
                           .insertInc(4, Order(7, 4, 3, QString(), "s1")))
                .insertInc("s2", OrderPlan()
                           .insertInc(1, Order(6, 1, 50, "s1", "s2"))
                           .insertInc(2, Order(7, 2, 0, "s1", "s2")))
                .insertInc("s3", OrderPlan()
                           .insertInc(1, Order(4, 1, 18, "s1", "s3"))
                           .insertInc(2, Order(5, 2, 0, "s1", "s3"))
                           .insertInc(3, Order(6, 3, 0, "s1", "s3"))
                           .insertInc(4, Order(7, 4, 18, "s1", "s3"))));

    QTest::newRow("three-nodes2")
            << (TreeOrderTable()
                .insertInc("s2", OrderPlan()
                           .insertInc(1, Order(2, 1, 10, "s1", "s2"))
                           .insertInc(2, Order(3, 2, 10, "s1", "s2"))
                           .insertInc(3, Order(4, 3, 10, "s1", "s2"))
                           .insertInc(4, Order(5, 4, 10, "s1", "s2"))
                           .insertInc(5, Order(6, 5, 10, "s1", "s2"))
                           .insertInc(6, Order(7, 6, 10, "s1", "s2")))
                .insertInc("s3", OrderPlan()
                           .insertInc(1, Order(2, 1, 5, "s1", "s3"))
                           .insertInc(2, Order(3, 2, 5, "s1", "s3"))
                           .insertInc(3, Order(4, 3, 5, "s1", "s3"))
                           .insertInc(4, Order(5, 4, 5, "s1", "s3"))
                           .insertInc(5, Order(6, 5, 5, "s1", "s3"))
                           .insertInc(6, Order(7, 6, 5, "s1", "s3"))))
            << (StorageTree().setRoot("s1")
                .addChild("s1", "s2")
                .addChild("s1", "s3"))
               .setBalance("s1", 100)
               .setExpense("s1", 1)
               .setDeliveryTime("s1", 3)
               .setBalance("s2", 0)
               .setExpense("s2", 10)
               .setDeliveryTime("s2", 1)
               .setBalance("s3", 0)
               .setExpense("s3", 5)
               .setDeliveryTime("s3", 1)
            << "s1"
            << 7
            << (TreeOrderTable()
                .insertInc("s1", OrderPlan()
                           .insertInc(1, Order(4, 1, 0, QString(), "s1"))
                           .insertInc(2, Order(5, 2, 0, QString(), "s1"))
                           .insertInc(3, Order(6, 3, 0, QString(), "s1"))
                           .insertInc(4, Order(7, 4, 0, QString(), "s1")))
                .insertInc("s2", OrderPlan()
                           .insertInc(1, Order(2, 1, 10, "s1", "s2"))
                           .insertInc(2, Order(3, 2, 10, "s1", "s2"))
                           .insertInc(3, Order(4, 3, 10, "s1", "s2"))
                           .insertInc(4, Order(5, 4, 10, "s1", "s2"))
                           .insertInc(5, Order(6, 5, 10, "s1", "s2"))
                           .insertInc(6, Order(7, 6, 10, "s1", "s2")))
                .insertInc("s3", OrderPlan()
                           .insertInc(1, Order(2, 1, 5, "s1", "s3"))
                           .insertInc(2, Order(3, 2, 5, "s1", "s3"))
                           .insertInc(3, Order(4, 3, 5, "s1", "s3"))
                           .insertInc(4, Order(5, 4, 5, "s1", "s3"))
                           .insertInc(5, Order(6, 5, 5, "s1", "s3"))
                           .insertInc(6, Order(7, 6, 5, "s1", "s3"))));
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

void TOrderGenerator::TestCalcOrderPlans_data()
{
    QTest::addColumn<TreeOrderTable>("orderTable");
    QTest::addColumn<StorageTree>("tree");
    QTest::addColumn<int>("days");
    QTest::addColumn<TreeOrderTable>("expected");

    QTest::newRow("empty") << TreeOrderTable()
                           << StorageTree()
                           << 1
                           << TreeOrderTable();

    QTest::newRow("single")
            << TreeOrderTable()
            << (StorageTree().setRoot("s1")
                .setBalance("s1", 0)
                .setExpense("s1", 1)
                .setDeliveryTime("s1", 0))
            << 1
            << (TreeOrderTable()
                .insertInc("s1", OrderPlan()
                           .insertInc(1, Order(1, 1, 0, QString(), "s1"))));

    QTest::newRow("two-nodes")
            << TreeOrderTable()
            << (StorageTree().setRoot("s1")
                .addChild("s1", "s2"))
               .setBalance("s1", 0)
               .setExpense("s1", 1)
               .setDeliveryTime("s1", 3)
               .setBalance("s2", 0)
               .setExpense("s2", 10)
               .setDeliveryTime("s2", 5)
            << 7
            << (TreeOrderTable()
                .insertInc("s1", OrderPlan()
                           .insertInc(1, Order(4, 1, 3, QString(), "s1"))
                           .insertInc(2, Order(5, 2, 0, QString(), "s1"))
                           .insertInc(3, Order(6, 3, 0, QString(), "s1"))
                           .insertInc(4, Order(7, 4, 3, QString(), "s1")))
                .insertInc("s2", OrderPlan()
                           .insertInc(1, Order(6, 1, 50, "s1", "s2"))
                           .insertInc(2, Order(7, 2, 0, "s1", "s2"))));

    QTest::newRow("three-nodes")
            << TreeOrderTable()
            << (StorageTree().setRoot("s1")
                .addChild("s1", "s2")
                .addChild("s1", "s3"))
               .setBalance("s1", 100)
               .setExpense("s1", 1)
               .setDeliveryTime("s1", 3)
               .setBalance("s2", 0)
               .setExpense("s2", 10)
               .setDeliveryTime("s2", 1)
               .setBalance("s3", 0)
               .setExpense("s3", 5)
               .setDeliveryTime("s3", 1)
            << 7
            << (TreeOrderTable()
                .insertInc("s1", OrderPlan()
                           .insertInc(1, Order(4, 1, 0, QString(), "s1"))
                           .insertInc(2, Order(5, 2, 0, QString(), "s1"))
                           .insertInc(3, Order(6, 3, 0, QString(), "s1"))
                           .insertInc(4, Order(7, 4, 0, QString(), "s1")))
                .insertInc("s2", OrderPlan()
                           .insertInc(1, Order(2, 1, 10, "s1", "s2"))
                           .insertInc(2, Order(3, 2, 10, "s1", "s2"))
                           .insertInc(3, Order(4, 3, 10, "s1", "s2"))
                           .insertInc(4, Order(5, 4, 10, "s1", "s2"))
                           .insertInc(5, Order(6, 5, 10, "s1", "s2"))
                           .insertInc(6, Order(7, 6, 10, "s1", "s2")))
                .insertInc("s3", OrderPlan()
                           .insertInc(1, Order(2, 1, 5, "s1", "s3"))
                           .insertInc(2, Order(3, 2, 5, "s1", "s3"))
                           .insertInc(3, Order(4, 3, 5, "s1", "s3"))
                           .insertInc(4, Order(5, 4, 5, "s1", "s3"))
                           .insertInc(5, Order(6, 5, 5, "s1", "s3"))
                           .insertInc(6, Order(7, 6, 5, "s1", "s3"))));

}

void TOrderGenerator::TestCalcOrderPlans()
{
    QFETCH(TreeOrderTable, orderTable);
    QFETCH(StorageTree, tree);
    QFETCH(int, days);
    QFETCH(TreeOrderTable, expected);

    OrderGenerator::calcOrderPlans(orderTable, tree, days);

    QCOMPARE(orderTable, expected);

}
