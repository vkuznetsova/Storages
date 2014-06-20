#ifndef SWINDOW_H

#define SWINDOW_H

#include <QMainWindow>
#include <QTableView>
#include <QVBoxLayout>
#include <QPushButton>
#include <QInputDialog>
#include <QAction>
#include <QToolButton>
#include <QMenu>
#include <QContextMenuEvent>
#include <QAbstractItemView>
#include <QComboBox>
#include <QDataWidgetMapper>
#include <QMessageBox>

#include "TableModel.h"
#include "StorageDatabaseReader.h"

class Swindow:public QMainWindow
{
    Q_OBJECT
public:
    Swindow(int argc, char *argv[],
            QApplication* app,
            QWidget *parent = 0,
            Qt::WindowFlags flags = 0);
    ~Swindow();

    void createModel();

    void createView();

    void createConnections();

private slots:
    void addNewChild();
    void removeNode();
    void currentTreeChanged(const int index);

private:
    QTableView *tableView_;
    TableModel *tableModel_;

    QPushButton *addChildButton_;

    QMenu *menu_;

    QComboBox *comboBox_;

    StorageDatabaseReader *reader_;

protected:
    virtual void contextMenuEvent(QContextMenuEvent* event);



};

#endif // SWINDOW_H
