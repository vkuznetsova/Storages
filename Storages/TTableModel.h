#ifndef TTABLEMODEL_H

#define TTABLEMODEL_H

#include <QtTest/QtTest>

#include "TableModel.h"


class TTableModel : public QObject
{
    Q_OBJECT
public:
    TTableModel();

    static const int headerColumnNode = 0;
    static const int headerColumnRoot = 1;
    static const int headerColumnBalance = 2;
    static const int headerColumnExpense = 3;

private slots:
    void TestColumnCount();

    void TestHorizontalHeader();

    void TestRowCount_data();
    void TestRowCount();

    void TestRowData_data();
    void TestRowData();

    void TestAddNewChild_data();
    void TestAddNewChild();

    void TestSort_data();
    void TestSort();

    void TestRemoveNode_data();
    void TestRemoveNode();

};

#endif // TTABLEMODEL_H
