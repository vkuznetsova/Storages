#ifndef TTABLEMODELORDER_H

#define TTABLEMODELORDER_H

#include <QtTest/QTest>

#include "TableModelOrder.h"

class TTableModelOrder : public QObject
{
    Q_OBJECT
public:
    TTableModelOrder();

    static const int headerColumnFrom = 0;
    static const int headerColumnTo = 1;
    static const int headerColumnOrderDate = 2;
    static const int headerColumnDeliveryDate = 3;

private slots:
    void TestColumnCount();

    void TestHorizontalHeader();

    void TestRowCount_data();
    void TestRowCount();
};

#endif // TTABLEMODELORDER_H
