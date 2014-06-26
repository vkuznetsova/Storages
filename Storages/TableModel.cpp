#include "TableModel.h"

 const int TableModel::columnNode = 0;
 const int TableModel::columnParent = 1;
 const int TableModel::columnBalance = 2;
 const int TableModel::columnExpense = 3;

TableModel::TableModel(const StorageTree tree)
{
    writer_ = StorageDatabaseWriter("dataBaseName");
    setTree(tree);
}

QModelIndex TableModel::index(int row, int column, const QModelIndex &parent) const
{
    if (!hasIndex(row, column, parent))
    {
        return QModelIndex();
    }

    if (!parent.isValid())
    {
        return createIndex(row, column);
    }

    return QModelIndex();
}

QModelIndex TableModel::parent(const QModelIndex &child) const
{
    if (!child.isValid())
    {
        return QModelIndex();
    }

    return QModelIndex();
}

int TableModel::rowCount(const QModelIndex &parent) const
{
    if (!parent.isValid())
    {
        return tree_.count();
    }
    return 0;
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

                if(index.column() == columnNode)
                {
                    return idChild;
                    break;
                }
                if(index.column() == columnParent)
                {
                    return tree_.parent(idChild);
                    break;
                }
                if(index.column() == columnBalance)
                {
                    tree_.node(idChild).getBalance();
                    break;
                }
                if(index.column() == columnExpense)
                {
                    return tree_.node(idChild).getExpence();
                    break;
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
        QColor color = Qt::red;
        return QBrush(color);
    }
    if(role == Qt::DisplayRole || role == Qt::EditRole)
    {
        if(index.column() == columnNode)
        {
            return node.id();
        }
        if(index.column() == columnParent)
        {
            return node.getParent();
        }
        if(index.column() == columnBalance)
        {
            return node.getBalance();
        }
        if(index.column() == columnExpense)
        {
            return node.getExpence();
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
            if(section == columnNode)
            {
                return "Потомок";
            }
            if(section == columnParent)
            {
                return "Родитель";
            }
            if(section == columnBalance)
            {
                return "Баланс Потомка";
            }
            if(section == columnExpense)
            {
                return "Расход";
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
    writer_.write(tree_);
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
    if(index.isValid() && (index.column() == columnBalance || index.column() == columnExpense))
        flags |= Qt::ItemIsEditable;
    return flags;
}

bool TableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if(index.isValid() && role == Qt::EditRole)
    {
        const QString id = data(createIndex(index.row(), 0), Qt::DisplayRole).toString();
        if(index.column() == columnBalance)
        {
            tree_.setBalance(id, value.toInt());
            StorageDatabaseWriter writer("dataBaseName");
            writer.updateBalance(value.toInt(), id);

        }
        if(index.column() == columnExpense)
        {
            tree_.setExpense(id, value.toInt());
            StorageDatabaseWriter writer("dataBaseName");
            writer.updateExpense(value.toInt(), id);
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
            writer_.write(tree_);
            layoutChanged();
            return;
        }
    }
}

void TableModel::setTree(const StorageTree &tree)
{
    tree_ = tree;
    nodeOrder_ = tree_.order();
    emit layoutChanged();
}

