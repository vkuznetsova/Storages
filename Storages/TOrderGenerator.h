#ifndef TORDERGENERATOR_H

#define TORDERGENERATOR_H

#include <QtTest/QtTest>

#include "StorageTree.h"
#include "OrderGenerator.h"

class TOrderGenerator: public QObject
{
    Q_OBJECT
public:
    TOrderGenerator();

private slots:

    void TestCalcOrderPlan_data();
    void TestCalcOrderPlan();

    void TestCalcOrderPlans_data();
    void TestCalcOrderPlans();
};

#endif // TORDERGENERATOR_H
