#include"TableModel.h"

TableModel::TableModel(const StorageTree &tree) :
    tree_(tree)
{

}

QModelIndex TableModel::index(int row, int column, const QModelIndex &parent) const
{
    return createIndex(row, column);
}

QModelIndex TableModel::parent(const QModelIndex &child) const
{
    return QModelIndex();
}

int TableModel::rowCount(const QModelIndex &parent) const
{
    return tree_.count();
}

int TableModel::columnCount(const QModelIndex &parent) const
{
    return 3;
}

QVariant TableModel::data(const QModelIndex &index, int role) const
{
    if(role == Qt::DisplayRole)
    {
        if(index.row() == 1)
        {
            switch(index.column())
            {
            case 0: return "";
            case 1: return tree_.root().id();
            case 2: return 10;
            }
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
            }
        }
    }

    return QVariant();
}
