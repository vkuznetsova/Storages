#include"TableModel.h"

TableModel::TableModel(const StorageTree &tree) :
    tree_(tree)
{
    nodeOrder_ = tree_.order();
}

QModelIndex TableModel::index(int row, int column, const QModelIndex &parent) const
{
    if (!hasIndex(row, column, parent)) {
        return QModelIndex();
    }

    if (!parent.isValid()){
        return createIndex(row, column);
    }
}

QModelIndex TableModel::parent(const QModelIndex &child) const
{
    if (!child.isValid()) {
        return QModelIndex();
    }
    return QModelIndex();
}

int TableModel::rowCount(const QModelIndex &parent) const
{
    if (!parent.isValid()) {
        return tree_.count();
    }
}

int TableModel::columnCount(const QModelIndex &parent) const
{
    return 4;
}

QVariant TableModel::recursiveData(const StorageTreeNode &parent, const QModelIndex &index) const
{
    if(index.isValid())
    {
        QStringList children = tree_.childrenIDs(parent.id());
        for(int i = 0; i < children.size(); i++)
        {
            QString idChild = children.at(i);
            if(index.row() == i)
            {
                switch(index.column())
                {
                case 0: return idChild; break;
                case 1: return tree_.parent(idChild); break;
                case 2: return tree_.node(idChild).getBalance();break;
                case 3: return tree_.node(idChild).getExpence();break;
                }
            }
            recursiveData(tree_.node(idChild), index);
        }
    }
    return QVariant();
}

QVariant TableModel::data(const QModelIndex &index, int role) const
{
    const QString nodeID = nodeOrder_.value(index.row());
    const StorageTreeNode node = tree_.node(nodeID);
    if (!index.isValid()) {
        return QVariant();
    }
    if (role == Qt::BackgroundRole && node.getBalance() < 0) {
        int row = index.row();
        QColor color = Qt::red;
        return QBrush(color);
    }
    if(role == Qt::DisplayRole || role == Qt::EditRole)
    {
        switch(index.column())
        {
        case 0: return node.id(); break;
        case 1: return node.getParent(); break;
        case 2: return node.getBalance();break;
        case 3: return node.getExpence();break;
        }
    }
    return QVariant();
}

QVariant TableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(role == Qt::DisplayRole)
    {
        if(orientation == Qt::Horizontal)
        {
            switch(section)
            {
            case 0: return "Потомок";
            case 1: return "Родитель";
            case 2: return "Баланс Потомка";
            case 3: return "Расход";
            }
        }
    }

    return QVariant();
}

void TableModel::addNewChild(const QString &parentID, const QString &childID)
{
    tree_.addChild(parentID, StorageTreeNode(childID));
    nodeOrder_ = tree_.order();
    int row =rowCount(QModelIndex());
    insertRow(row);
    layoutChanged();
}

QString TableModel::rowID(const int row) const
{
    return nodeOrder_.at(row);
}


QString TableModel::columnID(const int column) const
{
    return nodeOrder_.at(column);
}

Qt::ItemFlags TableModel::flags(const QModelIndex &index) const
{
    Qt::ItemFlags flags = QAbstractItemModel::flags(index);
    if(index.isValid() && index.column() == columnBalance_ || index.column() == columnExpense_)
        flags |= Qt::ItemIsEditable;
    return flags;
}

bool TableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if(index.isValid() && role == Qt::EditRole)
    {
        const QString id = data(createIndex(index.row(), 0), Qt::DisplayRole).toString();
        if(index.column() == columnBalance_){
            tree_.setBalance(id, value.toInt());
        }
        if(index.column() == columnExpense_)
        {
            tree_.setExpense(id, value.toInt());
        }
        emit dataChanged(index, index);
        return true;
    }
    return false;
}

void TableModel::sort(int column, Qt::SortOrder order)
{
    QList< QPair<QString, QVariant> > modelData;

    for(int i = 0; i < rowCount(); i++)
    {
        modelData << QPair<QString, QVariant>(rowID(i), data(index(i, column), Qt::EditRole));
    }
    if(order == Qt::AscendingOrder)
    {
        std::sort(modelData.begin(), modelData.end(), greaterThan);
    }
    else
    {
        std::sort(modelData.begin(), modelData.end(), lessThan);
    }

    nodeOrder_.clear();

    for(int i = 0; i < modelData.size(); i++)
    {
        nodeOrder_ << modelData.at(i).first;
    }
    emit layoutChanged();
}

bool TableModel::greaterThan(const QPair<QString, QVariant> &pair1, const QPair<QString, QVariant> &pair2)
{
    return pair1.second > pair2.second;
}

bool TableModel::lessThan(const QPair<QString, QVariant> &pair1, const QPair<QString, QVariant> &pair2)
{
    return pair1.second < pair2.second;
}

void TableModel::removeNode(QString &parentID)
{
    for(int i = 0; i < rowCount(); i++)
    {
        QModelIndex index = this->index(i, 0);
        QVariant value = this->data(index);

        if(value.toString() == parentID)
        {
            tree_.removeNode(parentID);
            nodeOrder_ = tree_.order();
            layoutChanged();
            return;
        }
    }
}

