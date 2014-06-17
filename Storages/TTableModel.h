#ifndef TTABLEMODEL_H

#define TTABLEMODEL_H

#include <QtTest/QtTest>

#include "TableModel.h"

static int headerColumnNode_ = 0;
static int headerColumnRoot_ = 1;
static int headerColumnBalance_ = 2;
static int headerColumnExpense_ = 3;

class TTableModel : public QObject
{
    Q_OBJECT
public:
    TTableModel();

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
