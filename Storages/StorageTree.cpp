#include "StorageTree.h"
#include <QDebug>

StorageTree::StorageTree()
{

}

StorageTree::StorageTree(const StorageTreeNode &root)
{
    rootID_ = root.id();
    nodes_.insert(root.id(), root);
}

StorageTree &StorageTree::setRoot(const StorageTreeNode &root)
{
    nodes_.remove(root.id());
    rootID_ = root.id();
    nodes_.insert(root.id(), root);
    return *this;
}

StorageTreeNode StorageTree:: root()const
{
    return nodes_[rootID_];
}

StorageTree &StorageTree::addChild(const QString &parent, const StorageTreeNode &child)
{
    if(!nodes_.contains(parent))
        return *this;

    StorageTreeNode newChild = child;
    newChild.setParent(parent);

    nodes_.insert(newChild.id(),newChild);
    nodes_[parent].addChild(newChild);
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

QString StorageTree::parent(const QString &child) const
{
    return nodes_.value(child).getParent();
}

bool StorageTree::operator ==(const StorageTree &tree) const
{
    return toString() == tree.toString();
}

void StorageTree::recursiveSubTree(const StorageTreeNode &parentNode, StorageTree &tree) const
{
    QStringList children = parentNode.childrenIDs();
    for(int i = 0; i < children.size(); i++)
    {
        QString idChild = children.at(i);
        StorageTreeNode elCopy = nodes_.value(idChild);
        tree.addChild(parentNode.id(),elCopy);
        recursiveSubTree(elCopy, tree);
    }
}


StorageTree StorageTree::subTree(const QString &root) const
{
    StorageTree treeCopy;
    treeCopy.setRoot(StorageTreeNode(root));
    recursiveSubTree(nodes_.value(root), treeCopy);
    return treeCopy;

}

void StorageTree::recursive(const StorageTreeNode &parent, QString &sRecord) const
{
    QStringList children  = parent.childrenIDs();
    sRecord += "(" + parent.id();
    for(int i = 0; i < children.size(); i++)
    {
        QString idChild = children.at(i);
        recursive(nodes_.value(idChild), sRecord);
    }
    sRecord += ")";

}
QString StorageTree:: toString() const
{
    QString sRecord;
    recursive(nodes_.value(rootID_), sRecord);
    return sRecord;
}

bool StorageTree::isLeaf(const QString &node)
{
    return nodes_[node].childrenIDs().isEmpty();
}

bool StorageTree::recursiveISBoolean(const StorageTreeNode &parent) const
{
    QStringList children  = parent.childrenIDs();
    if(!children.isEmpty() && children.size() != 2)
        return false;
    for(int i = 0; i < children.size(); i++)
    {
        QString idChild = children.at(i);
        if(!recursiveISBoolean(nodes_.value(idChild)))
            return false;
    }
    return true;
}

bool StorageTree:: isBoolean()
{

    return recursiveISBoolean(root());
}

/*bool StorageTree::isBalanced()
{

}*/


void StorageTree::recursiveLeafs(const StorageTreeNode &parent, QStringList &children) const
{
    QStringList childs  = parent.childrenIDs();
    if(nodes_.value(parent.id()).childrenIDs().isEmpty()) return;
    for(int i = 0; i < childs.size(); i++)
    {
        QString idChild = childs.at(i);
        if(!nodes_[idChild].childrenIDs().isEmpty())
        {
        recursiveLeafs(nodes_[idChild], children);
        }
        else
        {
            children += idChild;
        }
    }
}

QStringList StorageTree::leafs(const QString &node)
{
    QStringList children;
    StorageTree(nodes_[node]).subTree(node);
    recursiveLeafs(nodes_[node], children);
    return children;

}
