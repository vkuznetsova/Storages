#ifndef ORDERGENERATOR_H

#define ORDERGENERATOR_H

#include "Order.h"
#include "StorageTree.h"

class OrderGenerator
{
public:
    OrderGenerator();
    static void calcOrderPlan(TreeOrderTable &orderTable,
                              const StorageTree &tree,
                              const QString &storage,
                              const int days);

    static void calcOrderPlans(TreeOrderTable &orderTable,
                               const StorageTree &tree,
                               const int days);
};

#endif // ORDERGENERATOR_H
