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
#include <QSpinBox>
#include <QHBoxLayout>
#include <QProgressBar>

#include "TableModel.h"
#include "StorageDatabaseReader.h"
#include "TableModelOrder.h"
#include "OrderGenerator.h"

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
    void calcOrderPlans();
    void currentTreeChangedForOrder(const int index);

private:
    QTableView *tableView_;

    TableModel *tableModel_;

    TableModelOrder *tableModelOrder_;

    QPushButton *addChildButton_;

    QPushButton *calcOrderPlansButton_;

    QSpinBox *spBox_;

    QMenu *menu_;

    QComboBox *comboBox_;
    QComboBox *comboBoxOrder_;

    StorageDatabaseReader *reader_;

    QTabWidget *tabWgt_;

    QTableView *viewOrder_;

protected:
    virtual void contextMenuEvent(QContextMenuEvent* event);



};

#endif // SWINDOW_H
