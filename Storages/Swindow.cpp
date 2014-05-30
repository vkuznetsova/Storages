#include"Swindow.h"
#include<QAbstractItemView>

Swindow::Swindow(int argc,
                 char *argv[],
                 QApplication *app,
                 QWidget *parent,
                 Qt::WindowFlags flags):
    QMainWindow(parent, flags)
{
    createModel();
    createView();
    createConnections();

}

Swindow::~Swindow()
{

}

void Swindow::createModel()
{
    StorageTree tree (StorageTree(StorageTreeNode("root", QList<QString>(), 1, 3, -100))
                      .addChild("root", StorageTreeNode("leaf1", QList<QString>(), 2, 1, -1))
                      .addChild("root", StorageTreeNode("leaf2", QList<QString>(), 2, 5, 10))
                      .addChild("leaf1", StorageTreeNode("leaf3", QList<QString>(), 3, 10, 5))
                      .addChild("leaf2", StorageTreeNode("leaf4", QList<QString>(), 3, 5, 5))
                      .addChild("leaf2", StorageTreeNode("leaf5", QList<QString>(), 3, 1, 0)));
    tableModel_ = new TableModel(tree);
}

void Swindow::createView()
{
    addChildButton_ = new QPushButton("Добавить потомка");

    tableView_ = new QTableView();
    tableView_->setModel(tableModel_);
    tableView_->setEditTriggers(QAbstractItemView::DoubleClicked);
    tableView_->setSortingEnabled(true);

    menu_ = new QMenu(this);

    QVBoxLayout *mainLayout = new QVBoxLayout();
    mainLayout->addWidget(addChildButton_);
    mainLayout->addWidget(tableView_);

    QWidget *centralWidget = new QWidget();
    centralWidget->setLayout(mainLayout);

    setCentralWidget(centralWidget);
}

void Swindow::createConnections()
{
    QAction *removeAct = new QAction(tr("Удалить вершину"), this);

    menu_->addAction(removeAct);

    connect(removeAct, SIGNAL(triggered()), SLOT(removeNode()));
    connect(addChildButton_, SIGNAL(clicked()),
            this, SLOT(addNewChild()));
}

void Swindow::addNewChild()
{
    const QString childID = QInputDialog::getText(this,
                                                  tr("ID потомка"),
                                                  tr("Введите ID потомка"));
    const QModelIndex index = tableView_->currentIndex();
    QString parentID = tableModel_->data(index).toString();
    tableModel_->addNewChild(parentID, childID);
}

void Swindow::removeNode()
{
    const QModelIndex index = tableView_->currentIndex();
    QString parentID = tableModel_->data(index).toString();
    tableModel_->removeNode(parentID);
}
