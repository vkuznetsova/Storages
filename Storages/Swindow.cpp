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
    if(comboBoxOrder_->count() > 0)
    {
        currentTreeChanged(0);
    }
    Q_UNUSED(argc)
    Q_UNUSED(argv)
    Q_UNUSED(app)
}

Swindow::~Swindow()
{

}

void Swindow::createModel()
{
    tableModel_ = new TableModel();
    reader_ = new StorageDatabaseReader("dataBaseName");
    tableModelOrder_ = new TableModelOrder();
}

void Swindow::createView()
{
    comboBox_ = new QComboBox();
    comboBoxOrder_ = new QComboBox();
    comboBox_->addItems(reader_->readID());
    comboBoxOrder_->addItems(reader_->readID());
    addChildButton_ = new QPushButton("Добавить потомка");
    tableView_ = new QTableView();
    tableView_->setModel(tableModel_);
    tableView_->setEditTriggers(QAbstractItemView::DoubleClicked);
    tableView_->setSortingEnabled(true);
    tabWgt_ = new QTabWidget();
    spBox_ = new QSpinBox();
    spBox_->setMinimum(1);
    calcOrderPlansButton_ = new QPushButton("Рассчитать план заказов");

    QTableView *viewOrder = new QTableView();
    viewOrder->setModel(tableModelOrder_);
    viewOrder->setSortingEnabled(true);

    menu_ = new QMenu(this);

    QVBoxLayout *mainLayout = new QVBoxLayout();
    mainLayout->addWidget(addChildButton_);
    mainLayout->addWidget(comboBox_);
    mainLayout->addWidget(tableView_);

    QVBoxLayout *vbLayout = new QVBoxLayout();
    vbLayout->addWidget(spBox_);
    vbLayout->addWidget(comboBoxOrder_);
    vbLayout->addWidget(calcOrderPlansButton_);
    vbLayout->addWidget(viewOrder);

    QWidget *centralWidget = new QWidget();
    centralWidget->setLayout(mainLayout);

    QWidget *wgt = new QWidget();
    wgt->setLayout(vbLayout);

    setCentralWidget(centralWidget);
    tabWgt_->addTab(centralWidget, "Склады");
    tabWgt_->addTab(wgt, "Расчет плана закупок");
    setCentralWidget(tabWgt_);
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

    connect(calcOrderPlansButton_, SIGNAL(clicked()), this, SLOT(calcOrderPlans()));

    connect(comboBoxOrder_, SIGNAL(currentIndexChanged(int)),
            this, SLOT(currentTreeChangedForOrder(int)));

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

void Swindow::calcOrderPlans()
{
    TreeOrderTable orderTable;
    int days = spBox_->value();
    QString idTree = comboBoxOrder_->itemText(comboBoxOrder_->currentIndex());
    const StorageTree tree = reader_->read(idTree);
    tableModelOrder_->calcOrderPlans(orderTable, tree, days);
    tableModelOrder_->setOrderTable(orderTable);
}

void Swindow::currentTreeChangedForOrder(const int index)
{
    StorageDatabaseReader reader("dataBaseName");
    const QString treeID = comboBox_->itemText(index);
    StorageTree tree = reader.read(treeID);
}

void Swindow::contextMenuEvent(QContextMenuEvent *event)
{
    menu_->exec(event->globalPos());
}
