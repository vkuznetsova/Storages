#include"Swindow.h"


Swindow::Swindow(int argc,
                 char *argv[],
                 QApplication *app,
                 QWidget *parent,
                 Qt::WindowFlags flags):
    QMainWindow(parent, flags)
{
    StorageTree tree (StorageTree(StorageTreeNode("root"))
                      .addChild("root", StorageTreeNode("node1"))
                      .addChild("node1", StorageTreeNode("leaf1"))
                      .addChild("root", StorageTreeNode("node2"))
                      .addChild("node2", StorageTreeNode("leaf2"))
                      .addChild("node2", StorageTreeNode("leaf3"))
                      .addChild("node1", StorageTreeNode("leaf4")));

    QTableView *tableView = new QTableView();
    TableModel *model = new TableModel(tree);
    tableView->setModel(model);

    setCentralWidget(tableView);
}

Swindow::~Swindow()
{

}
