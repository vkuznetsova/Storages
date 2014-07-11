#ifndef ORDERGENERATOR_H

#define ORDERGENERATOR_H

#include "Order.h"
#include "StorageTree.h"

class OrderGenerator
{
public:
    OrderGenerator();

    //после вызова метода в orderTable должен появиться OrderPlan для storage
    static void calcOrderPlan(TreeOrderTable &orderTable,
                              const StorageTree &tree,
                              const QString &storage,
                              const int days);
};

#endif // ORDERGENERATOR_H
