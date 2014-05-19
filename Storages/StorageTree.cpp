#include "StorageTree.h"
#include"BooleanStorageTreePredicat.h"
#include"BalancedStorageTreePredicat.h"
#include"NSunsStorageTreePredicat.h"
#include"IDStorageTreePredicat.h"

#include <QDebug>


StorageTree::StorageTree()
{

}

StorageTree::StorageTree(const StorageTreeNode &root)
{
    rootID_ = root.id();
    nodes_.insert(root.id(), root);
    nodes_[root.id()].setLevel(1);
}

StorageTree &StorageTree::setRoot(const StorageTreeNode &root)
{
    nodes_.remove(root.id());
    rootID_ = root.id();
    nodes_.insert(root.id(), root);
    nodes_[root.id()].setLevel(1);
    return *this;
}

StorageTreeNode StorageTree:: root()const
{
    return nodes_.value(rootID_);
}

StorageTreeNode StorageTree::node(const QString &id) const
{
    return nodes_.value(id);
}

StorageTree &StorageTree::addChild(const QString &parent, const StorageTreeNode &child)
{
    if(!nodes_.contains(parent))
        return *this;

    StorageTreeNode newChild = child;
    newChild.setParent(parent);
    newChild.setLevel(nodes_[parent].level() + 1);
    nodes_[parent].setLeaf(false);


    nodes_.insert(newChild.id(),newChild);
    nodes_[parent].addChild(newChild.id());
    nodes_[newChild.id()].setLeaf(true);
    return *this;
}

QStringList StorageTree::childrenIDs(const QString &id) const
{
    return nodes_.value(id).childrenID();
}

QList<StorageTreeNode> StorageTree::children(const QString &id) const
{
    QList<StorageTreeNode> ch;

    foreach(const QString &childID, nodes_.value(id).childrenID())
    {
        ch << nodes_.value(childID);
    }

    return ch;
}

int StorageTree::level(const QString &node) const
{
    return nodes_.value(node).level();
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
        foreach(const QString &childID, current.childrenID())
        {
            return level(childID, find,  l + 1);
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
    QStringList children = parentNode.childrenID();
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

void StorageTree::recursiveToString(const StorageTreeNode &parent, QString &sRecord) const
{
    QStringList children  = parent.childrenID();
    sRecord += "(" + parent.id();
    for(int i = 0; i < children.size(); i++)
    {
        QString idChild = children.at(i);
        recursiveToString(nodes_.value(idChild), sRecord);
    }
    sRecord += ")";

}
QString StorageTree:: toString() const
{
    QString sRecord;
    recursiveToString(nodes_.value(rootID_), sRecord);
    return sRecord;
}

bool StorageTree::isLeaf(const QString &node) const
{
    return nodes_.value(node).childrenID().isEmpty();
}

/*bool StorageTree::recursiveISBoolean(const StorageTreeNode &parent) const
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
}*/

bool StorageTree:: isBoolean()
{
    BooleanStorageTreePredicat p;
    return all(&p);
}

/*bool StorageTree::recursiveIsBalanced(const StorageTreeNode &parent) const
{
    QStringList children = parent.childrenIDs();
    if(children.isEmpty())
        return false;
    for(int i = 0; i < children.size(); i++)
    {
        QString idChild = children.at(i);
        if(!recursiveIsBalanced(nodes_.value(idChild)))
        {
            if(children.size() == nodes_.value(parent.id()).childrenIDs().size()
                    && StorageTree(nodes_[idChild]).isLeaf(idChild)
                    && StorageTree(nodes_[nodes_.value(idChild).id()]).isLeaf(nodes_.value(idChild).id()) && level(idChild) == level(nodes_.value(idChild).id()))
            {
                return true;
            }
        }
    }
    return false;

}*/

bool StorageTree::isBalanced()
{
    int count = -1;
    int level = -1;

    foreach(const QString &nodeID, nodes_.keys())
    {
        if(isLeaf(nodeID))
        {
            level = this->level(nodeID);
        }
        else
        {

            count = nodes_.value(nodeID).childrenID().size();
        }

        if(count >= 0 && level >= 0)
        {
            break;
        }
    }

    BalancedStorageTreePredicat p(count, level);

    return all(&p);
}


void StorageTree::recursiveLeafs(const StorageTreeNode &parent, QStringList &children) const
{
    QStringList childs  = parent.childrenID();
    if(nodes_.value(parent.id()).childrenID().isEmpty()) return;
    for(int i = 0; i < childs.size(); i++)
    {
        QString idChild = childs.at(i);
        if(!nodes_[idChild].childrenID().isEmpty())
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

bool StorageTree::all(StorageTreePredicat *predicat) const
{
    foreach(const QString &nodeID, nodes_.keys())
    {
        if(!predicat->check(*this, nodeID))
        {
            return false;
        }
    }
    return true;
}

bool StorageTree::any(StorageTreePredicat *predicat) const
{
    foreach(const QString &nodeID, nodes_.keys())
    {
        if(predicat->check(*this, nodeID))
        {
            return true;
        }
    }
    return false;
}

StorageTree StorageTree::map(StorageTreeNodeMap *map) const
{
    QHash<QString, StorageTreeNode> nodes;

    foreach(const QString nodeID, nodes_.keys())
    {
        nodes.insert(nodeID, map->map(nodes_.value(nodeID)));
    }

    return StorageTree(rootID_, nodes);
}

int StorageTree::sum(STNTotalSum *sum) const
{
    QList<int> elems;
    foreach(const QString &nodeID, nodes_.keys())
    {
        elems << sum->map(nodes_.value(nodeID));
    }

    return sum->sum(elems);
}

QString StorageTree::fold(const QString &acc, const QString &nodeID, STNFold *f) const
{
    QString res = acc;
    foreach(const QString &childID, nodes_.value(nodeID).childrenID())
    {
        res = fold(res, childID, f);
    }
    res = f->left(res, nodes_.value(nodeID));

    return res;
}

bool StorageTree::idSize(const int size) const
{
    IDStorageTreePredicat p(size);
    return all(&p);
}

bool StorageTree:: moreNSuns(const int count) const
{
    NSunsStorageTreePredicat p(count, StorageUtils::greater);
    return any(&p);
}

bool StorageTree::nSuns(const int count) const
{
    NSunsStorageTreePredicat p(count, StorageUtils::equal);
    return any(&p);

}

StorageTree::StorageTree(const QString &rootID,
                         const QHash<QString, StorageTreeNode> &nodes) :
    rootID_(rootID),
    nodes_(nodes)
{
}

StorageTree StorageTree::run() const
{
    STNConsumptionMap m(StorageTreeNode().getExpence());

    return map(&m);
}

int StorageTree::totalSum()
{
    QList<int> data;
    foreach(const QString &nodeID, nodes_.keys())
    {
        data<<nodes_.value(nodeID).getBalance();
    }
    return STNTotalSum().sum(data);
}

int StorageTree::PositiveElemsSum()
{
    QList<int> data;
    foreach(const QString &nodeID, nodes_.keys())
    {
        if(nodes_.value(nodeID).getBalance() < 0)
            continue;
        else{
            data<<nodes_.value(nodeID).getBalance();
        }
    }
    return STNTotalSum().sum(data);

}

int StorageTree::euclidMetric()
{
    QList<int> data;
    foreach(const QString &nodeID, nodes_.keys())
    {
          data<<pow((nodes_.value(nodeID).getExpence()- nodes_.value(nodeID).getBalance()), 2);
    }
    return sqrt(STNTotalSum().sum(data));

}

StorageTree StorageTree::accumBalance(const StorageTree &tree) const
{

}

