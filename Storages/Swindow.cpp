#include"Swindow.h"


Swindow::Swindow(int argc,
                 char *argv[],
                 QApplication *app,
                 QWidget *parent,
                 Qt::WindowFlags flags):
    QMainWindow(parent, flags)
{
    StorageTree tree (StorageTree(StorageTreeNode("root", QList<QString>(), 1, 3, -100))
            .addChild("root", StorageTreeNode("leaf1", QList<QString>(), 2, 1, -1))
            .addChild("root", StorageTreeNode("leaf2", QList<QString>(), 2, 5, 10))
            .addChild("leaf1", StorageTreeNode("leaf3", QList<QString>(), 3, 10, 5))
            .addChild("leaf2", StorageTreeNode("leaf4", QList<QString>(), 3, 5, 5))
            .addChild("leaf2", StorageTreeNode("leaf5", QList<QString>(), 3, 1, 0)));

    QTableView *tableView = new QTableView();
    TableModel *model = new TableModel(tree);
    tableView->setModel(model);

    setCentralWidget(tableView);
}

Swindow::~Swindow()
{

}
