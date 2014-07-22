#include "Swindow.h"


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

    if(comboBox_->count() > 0)
    {
        currentTreeChanged(0);
    }
}

Swindow::~Swindow()
{

}

void Swindow::createModel()
{
    tableModel_ = new TableModel();
    reader_ = new StorageDatabaseReader("dataBaseName");
}

void Swindow::createView()
{
    comboBox_ = new QComboBox();
    comboBox_->addItems(reader_->readID());
    addChildButton_ = new QPushButton("Добавить потомка");
    tableView_ = new QTableView();
    tableView_->setModel(tableModel_);
    tableView_->setEditTriggers(QAbstractItemView::DoubleClicked);
    tableView_->setSortingEnabled(true);
    tabWgt_ = new QTabWidget();

    menu_ = new QMenu(this);

    QVBoxLayout *mainLayout = new QVBoxLayout();
    mainLayout->addWidget(addChildButton_);
    mainLayout->addWidget(comboBox_);
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

    connect(comboBox_, SIGNAL(currentIndexChanged(int)),
            this, SLOT(currentTreeChanged(int)));
}

void Swindow::addNewChild()
{
    const QString childID = QInputDialog::getText(this,
                                                  tr("ID потомка"),
                                                  tr("Введите ID потомка"));
    const QModelIndex index = tableView_->currentIndex();
    QString parentID = tableModel_->data(index).toString();
    if(parentID.isNull() || childID.isNull())
    {
        QMessageBox::information(0, "Information", tr("Узел не может быть с пустым id"));
        return;
    }
    tableModel_->addNewChild(parentID, childID);
}

void Swindow::removeNode()
{
    const QModelIndex index = tableView_->currentIndex();
    QString parentID = tableModel_->data(index).toString();
    tableModel_->removeNode(parentID);
}

void Swindow::currentTreeChanged(const int index)
{
    StorageDatabaseReader reader("dataBaseName");
    const QString treeID = comboBox_->itemText(index);
    StorageTree tree = reader.read(treeID);
    tableModel_->setTree(tree);
}

void Swindow::contextMenuEvent(QContextMenuEvent *event)
{
    menu_->exec(event->globalPos());
}
