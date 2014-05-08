#include "StorageTree.h"

StorageTree::StorageTree()
{

}

StorageTree::StorageTree(const StorageTreeNode &root)
{
    nodes_.insert(root.id(), root);
}

StorageTree &StorageTree::setRoot(const StorageTreeNode &root)
{
    nodes_.remove(root.id());
    rootID_ = root.id();
    nodes_.insert(root.id(), root);
    return *this;
}

StorageTree &StorageTree::addChild(const QString &parent, const StorageTreeNode &child)
{
    nodes_[parent].addChild(child);
    return *this;
}

QStringList StorageTree::children(const QString &id) const
{   
    return nodes_.value(id).childrenIDs();
}

int StorageTree::level(const QString &node) const
{
    return level("root", node,  1);
}

int StorageTree::level(const QString &node, const QString &find, const int l) const
{
    const StorageTreeNode current = nodes_.value(node);
    if(node == find)
    {
        return l;
    }
    else
    {
        foreach(const StorageTreeNode &child, current.children())
        {
            return level(child.id(), find,  l + 1);
        }
        return 0;
    }
}
