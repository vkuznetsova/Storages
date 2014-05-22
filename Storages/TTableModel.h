#ifndef TTABLEMODEL_H

#define TTABLEMODEL_H

#include <QtTest/QtTest>
#include"TableModel.h"

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
};

#endif // TTABLEMODEL_H
