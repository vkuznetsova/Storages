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

    addChildButton_ = new QPushButton("Добавить потомка");

    tableView_ = new QTableView();
    tableModel_ = new TableModel(tree);
    tableView_->setModel(tableModel_);

    QVBoxLayout *mainLayout = new QVBoxLayout();
    mainLayout->addWidget(addChildButton_);
    mainLayout->addWidget(tableView_);

    QWidget *centralWidget = new QWidget();
    centralWidget->setLayout(mainLayout);

    setCentralWidget(centralWidget);

    connect(addChildButton_, SIGNAL(clicked()),
            this, SLOT(addNewChild()));
}

Swindow::~Swindow()
{

}

void Swindow::addNewChild()
{
    const QString childID = QInputDialog::getText(this,
                                                  tr("ID потомка"),
                                                  tr("Введите ID потомка"));
    const QModelIndexList selected = tableView_->selectionModel()->selectedIndexes();

    if(selected.size() == 1)
    {
        const QString parentID = tableModel_->rowID(selected.first().row());
        qWarning() << parentID << " " << childID;
        tableModel_->addNewChild(parentID, childID);
        tableView_->reset();
    }
}
