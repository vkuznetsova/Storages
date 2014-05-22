#ifndef SWINDOW_H

#define SWINDOW_H

#include <QMainWindow>
#include<QTableView>
#include<QHBoxLayout>
#include<QWidget>
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
};

#endif // SWINDOW_H
