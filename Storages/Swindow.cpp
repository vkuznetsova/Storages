#include"Swindow.h"


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
    //   StorageTree tree = StorageTree::generateTree(15);
    StorageTree tree =(StorageTree("fourth")
                       .setRoot(StorageTreeNode("root"))
                       .addChild("root", "node1")
                       .addChild("node1", "leaf1")
                       .addChild("root", "node2")
                       .addChild("node2", "leaf2")
                       .addChild("node2", "leaf3"))
            .setBalance("leaf3", -100)
            .setExpense("leaf3", 100)
            .setBalance("root", 3)
            .setExpense("root", 6)
            .setBalance("node1", 6)
            .setExpense("node1", 5)
            .setBalance("leaf1", 5)
            .setExpense("leaf1", 1)
            .setBalance("node2", 88)
            .setExpense("node2", 100)
            .setBalance("leaf2", 8)
            .setExpense("leaf2", 10);

    // tableModel_ = new TableModel(tree);
    StorageDatabaseReader reader("dataBaseName");
    reader.read(tree.id());
    comboBox_ = new QComboBox();
    comboBox_->addItem(reader.read(tree.id()).id());
}

void Swindow::createView()
{
    addChildButton_ = new QPushButton("Добавить потомка");
    //    tableView_ = new QTableView();
    //        tableView_->setModel(tableModel_);
    //        tableView_->setEditTriggers(QAbstractItemView::DoubleClicked);
    //        tableView_->setSortingEnabled(true);

    menu_ = new QMenu(this);

    QVBoxLayout *mainLayout = new QVBoxLayout();
    mainLayout->addWidget(addChildButton_);
    // mainLayout->addWidget(tableView_);
    mainLayout->addWidget(comboBox_);

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
