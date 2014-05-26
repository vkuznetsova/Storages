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
        QStringList children = parent.childrenID();
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
    if(role == Qt::DisplayRole)
    {
        switch(index.column())
        {
        case 0: return node.id(); break;
        case 1: return node.getParent(); break;
        case 2: return node.getBalance();break;
        case 3: return node.getExpence();break;
        }
    }
    return  QVariant();
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

//void TableModel::sort(int column, Qt::SortOrder order)
//{
//    TableModel model(tree_);

//}

//bool TableModel::setData(const QModelIndex &index, const QVariant &value, int role)
//{
//    TableModel model(tree_);
//    if(index.isValid() && role == Qt::EditRole)
//    {
//        QString text = index.data(Qt::DisplayRole).toString();
//        model.sort(0, nodeOrder_);
//        tree_.node(text);
//        emit dataChanged(index, index);
//        return true;
//    }
//    return false;
//}

void TableModel::addNewChild(const QString &parentID, const QString &childID)
{
    tree_.addChild(parentID, StorageTreeNode(childID));
    nodeOrder_ = tree_.order();
    insertRows(1, 1);
    emit dataChanged(index(0,0, QModelIndex()), index(tree_.count(), 4, QModelIndex()));
}

QString TableModel::rowID(const int row) const
{
    return nodeOrder_.at(row);
}
