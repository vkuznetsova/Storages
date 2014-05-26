#ifndef SWINDOW_H

#define SWINDOW_H

#include <QMainWindow>
#include <QTableView>
#include <QVBoxLayout>
#include <QPushButton>
#include <QInputDialog>

#include"TableModel.h"

class Swindow:public QMainWindow
{
    Q_OBJECT
public:
    Swindow(int argc, char *argv[],
            QApplication* app,
            QWidget *parent = 0,
            Qt::WindowFlags flags = 0);
    ~Swindow();
private slots:
    void addNewChild();

private:
    QTableView *tableView_;
    TableModel *tableModel_;

    QPushButton *addChildButton_;
};

#endif // SWINDOW_H
