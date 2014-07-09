#include "StorageTree.h"
#include "BooleanStorageTreePredicat.h"
#include "BalancedStorageTreePredicat.h"
#include "NSunsStorageTreePredicat.h"
#include "IDStorageTreePredicat.h"

#include <QDebug>

const QString StorageTree::fromKey = "from";
const QString StorageTree::toKey = "to";
const QString StorageTree::idKey = "id";
const QString StorageTree::edgesKey = "edges";
const QString StorageTree::nodesKey = "nodes";
const QString StorageTree::graphsKey = "graphs";

StorageTree::StorageTree() :
    rootID_()
{
}

StorageTree::StorageTree(const StorageTreeNode &root)
{
    rootID_ = root.id();
    tree_[rootID_] = QSet<QString>();
    nodes_.insert(root.id(), root);
    nodes_[root.id()].setLevel(1);
}

StorageTree::StorageTree(const QString id) :
    id_(id)
{
}

StorageTree::StorageTree(const QString &graphID, const QJsonObject &object)
{
    const QJsonArray edges = object.value(edgesKey).toArray();
    for(int i = 0; i < edges.size(); i++)
    {
        const QJsonObject edge = edges.at(i).toObject();
        const QString from = edge.value(fromKey).toString();
        const QString to = edge.value(toKey).toString();
        addChild(from, to);
    }
    setID(graphID);
    const QJsonArray nodes = object.value(nodesKey).toArray();
    for(int i = 0; i < nodes.size(); i++)
    {
        const QJsonObject node = nodes.at(i).toObject();
        const int balance = node.value(StorageTreeNode::balanceKey).toInt();
        const int expense = node.value(StorageTreeNode::expenseKey).toInt();
        const QString idNode = node.value(StorageTreeNode::idKey).toString();
        nodes_[idNode] = StorageTreeNode(idNode, level(parent(idNode)) + 1);
        if(!parent(idNode).isNull())
        {
            tree_[parent(idNode)] << idNode;
        }
        if(!tree_.contains(idNode))
        {
            tree_[idNode] = QSet<QString>();
        }
        this->setBalance(idNode, balance);
        this->setExpense(idNode, expense);
        QHash<QString, QSet<QString> > structData = structure();
        foreach(const QString &parent, structData.keys())
        {
            foreach(const QString &child, structData.value(parent))
            {
                if(idNode == child)
                {
                    nodes_[idNode].setParent(parent);
                }
            }
        }
    }
}

QString StorageTree::id() const
{
    return id_;
}

void StorageTree::setID(const QString &idTrees)
{
    id_ = idTrees;
}

StorageTree StorageTree::setLevel(const QString &nodeID, const int lvl)
{
    nodes_[nodeID].setLevel(lvl);
    return *this;
}

StorageTree &StorageTree::setLeaf(const QString &nodeID, const bool value)
{
    nodes_[nodeID].setLeaf(value);
    return *this;
}

StorageTree &StorageTree::setRoot(const StorageTreeNode &root)
{
    nodes_.remove(root.id());
    tree_.remove(root.id());
    rootID_ = root.id();
    nodes_.insert(root.id(), root);
    nodes_[root.id()].setLevel(1);

    if(!tree_.contains(root.id()))
    {
        tree_[root.id()] = QSet<QString>();
    }

    return *this;
}

StorageTree &StorageTree::setRoot(const QString &rootID)
{
    rootID_ = rootID;
    addChild(QString(), rootID_);

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
    {
        if(!nodes_.contains(parent) && !tree_.contains(parent))
        {
            return *this;
        }
    }
    StorageTreeNode newChild = child;
    newChild.setParent(parent);
    newChild.setLevel(nodes_[parent].level() + 1);
    nodes_[parent].setLeaf(false);
    nodes_.insert(newChild.id(),newChild);
    nodes_[newChild.id()].setLeaf(true);
    tree_[parent] << newChild.id();
    return *this;

}

StorageTree &StorageTree::addChild(const QString &parent, const QString &child)
{
    if(!parent.isNull())
    {
        tree_[parent] << child;
    }
    if(!tree_.contains(child))
    {
        tree_[child] = QSet<QString>();
    }

    nodes_[child] = StorageTreeNode(child, level(parent) + 1);
    nodes_[child].setParent(parent);
    return *this;
}

QStringList StorageTree::childrenIDs(const QString &id) const
{
    return tree_.value(id).toList();
}

QList<StorageTreeNode> StorageTree::children(const QString &id) const
{
    QList<StorageTreeNode> ch;

    foreach(const QString &childID, childrenIDs(id))
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
        foreach(const QString &childID, childrenIDs(current.id()))
        {
            return level(childID, find,  l + 1);
        }
        return 0;
    }
}

QStringList StorageTree::order(const QString &nodeID) const
{
    QStringList nodes;

    nodes << nodeID;

    foreach(const QString childID, childrenIDs(nodeID))
    {
        nodes << order(childID);
    }

    return nodes;
}

QJsonArray StorageTree::nodesToJSONArray() const
{
    QJsonArray array;
    QHash<QString, StorageTreeNode> data = structureData();
    foreach(const StorageTreeNode &child, data.values())
    {
        array.append(child.toJSON());
    }
    return array;
}

QJsonObject StorageTree::edgeToJSON(const QString &from, const QString &to)
{
    if(from.isEmpty() && to.isEmpty())
    {
        return QJsonObject();
    }
    QJsonObject edge;
    edge.insert(fromKey, from);
    edge.insert(toKey, to);
    return edge;
}

QJsonArray StorageTree::edgesToJSONArray() const
{
    QJsonArray array;
    QJsonObject obj;
    QString from;
    QString to;
    const QHash<QString, QSet<QString> > structureTree = structure();
    if(structureTree.size() == 0 || structureTree.size() == 1)
    {
        return array;
    }
    if(this->childrenIDs(root().id()).size() != 0)
    {
        foreach(const QString &parent, structureTree.keys())
        {
            foreach(const QString &child, structureTree.value(parent))
            {
                from  = parent;
                to = child;
                obj = edgeToJSON(from, to);
                array.append(obj);
            }
        }
    }
    return array;
}

QJsonObject StorageTree::toJSON() const
{
    QJsonObject obj;
    QJsonObject innerObj;
    QJsonArray edges;
    QJsonArray nodes;
    edges = edgesToJSONArray();
    nodes = nodesToJSONArray();
    innerObj.insert(idKey, id());
    innerObj.insert(edgesKey, edges);
    obj.insert(nodesKey, nodes);
    obj.insert(graphsKey, innerObj);
    return obj;
}

QString StorageTree::parent(const QString &child) const
{
    return nodes_.value(child).getParent();
}

bool StorageTree::operator ==(const StorageTree &tree) const
{
    return id_ == tree.id_
            && rootID_ == tree.rootID_
            && nodes_ == tree.nodes_
            && tree_ == tree.tree_;
}

void StorageTree::recursiveSubTree(const StorageTreeNode &parentNode, StorageTree &tree) const
{
    QStringList children = childrenIDs(parentNode.id());
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
    if(root == "")
    {
        return StorageTree();
    }
    StorageTree treeCopy;
    treeCopy.setRoot(StorageTreeNode(root));
    recursiveSubTree(nodes_.value(root), treeCopy);
    return treeCopy;

}

void StorageTree::recursiveToString(const StorageTreeNode &parent, QString &sRecord) const
{
    QStringList children  = childrenIDs(parent.id());
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
    return childrenIDs(node).isEmpty();
}

bool StorageTree:: isBoolean()
{
    BooleanStorageTreePredicat p;
    return all(&p);
}

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
            count = childrenIDs(nodeID).size();
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
    QStringList childs  = childrenIDs(parent.id());
    if(childrenIDs(parent.id()).isEmpty())
    {
        return;
    }
    for(int i = 0; i < childs.size(); i++)
    {
        QString idChild = childs.at(i);
        if(!childrenIDs(idChild).isEmpty())
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

    return StorageTree(rootID_, nodes, tree_);
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
    foreach(const QString &childID, childrenIDs(nodeID))
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
                         const QHash<QString, StorageTreeNode> &nodes,
                         const QHash<QString, QSet<QString> > &tree) :
    rootID_(rootID),
    nodes_(nodes),
    tree_(tree)
{
}

StorageTree StorageTree::run() const
{
    STNConsumptionMap m(nodes_.value(root().id()).getExpence());

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
        if(!(nodes_.value(nodeID).getBalance() < 0))
        {
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
        data<<static_cast<int>(pow(nodes_.value(nodeID).getBalance(), 2));
    }
    return static_cast<int>(sqrt(STNTotalSum().sum(data)));

}

int StorageTree::recursiveAccumBalance(const QString &id)
{
    int balance = nodes_.value(id).getBalance();
    foreach(const QString &child, childrenIDs(id))
    {
        balance += recursiveAccumBalance(child);
    }

    nodes_[id].setBalance(balance);

    return balance;
}

StorageTree StorageTree::accumBalance() const
{
    if(nodes_.isEmpty())
    {
        return StorageTree();
    }
    StorageTree tree = *this;
    tree.recursiveAccumBalance(tree.root().id());
    return tree;
}

void StorageTree::recursiveIns(StorageTree &tree, const StorageTreeNode &parent, const int maxLvl, int lvl)
{
    if(lvl == maxLvl)
    {
        return;
    }
    StorageTreeNode node("leaf" + QString::number(tree.nodes_.size()));
    tree.addChild(parent.id(),node);
    StorageTreeNode node1("leaf" + QString::number(tree.nodes_.size()));
    tree.addChild(parent.id(),node1);
    lvl++;
    recursiveIns(tree,node,maxLvl,lvl);
    recursiveIns(tree,node1,maxLvl,lvl);
}

StorageTree StorageTree::generateTree(const int maxLevel)
{
    if(maxLevel == 0)
    {
        return StorageTree();
    }

    StorageTreeNode node("root");
    StorageTree tree(node);
    recursiveIns(tree, node,maxLevel,1);

    return tree;
}

int StorageTree::count() const
{
    return nodes_.size();

}

StorageTreeNode StorageTree::recursiveNodeForNum(const StorageTreeNode &parent, const int num,
                                                 int &findNum)
{
    QStringList children = childrenIDs(parent.id());
    for(int i = 0; i < children.size(); i++)
    {
        QString idChild = children.at(i);
        findNum++;
        if(findNum == num)
        {
            return nodes_.value(idChild);
        }

        StorageTreeNode node = recursiveNodeForNum(nodes_.value(idChild),num,findNum);
        if(!node.id().isEmpty())
        {
            return node;
        }
    }
    return StorageTreeNode();
}
QString StorageTree::nodeForNum(const int num)
{
    if(num <= 1)
    {
        return rootID_;
    }

    int find = 1;
    return static_cast<StorageTreeNode>(recursiveNodeForNum(nodes_[rootID_], num, find)).id();
}

QStringList StorageTree::order() const
{
    if(!rootID_.isNull())
    {
        return order(rootID_);
    }
    else
    {
        return QStringList();
    }
}

void StorageTree::removeNode(const QString &subTreeRoot)
{
    if(nodes_.isEmpty() && tree_.isEmpty())
    {
        return;
    }
    if(subTreeRoot == rootID_)
    {
        rootID_ = QString();
        nodes_.clear();
        tree_.clear();
        return;
    }
    foreach(const QString &childID, childrenIDs(subTreeRoot))
    {
        removeNode(childID);
    }
    QString parentSubTree =  parent(subTreeRoot);
    if(tree_.value(parentSubTree).isEmpty())
    {
        tree_.remove(parentSubTree);
    }
    tree_[parentSubTree].remove(subTreeRoot);
    tree_.remove(subTreeRoot);
    nodes_.remove(subTreeRoot);
}

StorageTree &StorageTree::setBalance(const QString &nodeID, const int balance)
{
    nodes_[nodeID].setBalance(balance);
    return *this;
}

StorageTree &StorageTree::setExpense(const QString &nodeID, const int expense)
{
    nodes_[nodeID].setExpence(expense);
    return *this;
}

StorageTree &StorageTree::setDeliveryTime(const QString &nodeID, const int deliveryTime)
{
    nodes_[nodeID].setDeliveryTime(deliveryTime);
    return *this;
}

void StorageTree::autoSetRoot()
{
    if(tree_.isEmpty())
    {
        return;
    }

    foreach (const QString &nodeID, nodes_.keys())
    {
        if(parent(nodeID).isNull())
        {
            rootID_ = nodeID;
            break;
        }
    }
    if(!tree_.contains(rootID_))
    {
        tree_[rootID_] = QSet<QString>();
    }
}

void StorageTree::autoSetLevel()
{
    if(tree_.isEmpty())
    {
        return;
    }
    foreach (const QString &nodeID, nodes_.keys())
    {
        int lvl = this->level(parent(nodeID)) + 1;
        nodes_[nodeID].setLevel(lvl);
    }
}

void StorageTree::autoSetLeaf()
{
    if(tree_.isEmpty())
    {
        return;
    }

    foreach (const QString &nodeID, nodes_.keys())
    {
        bool leaf = this->isLeaf(parent(nodeID));
        nodes_[nodeID].setLeaf(leaf);
    }
}

QHash<QString, QSet<QString> > StorageTree::structure() const
{
    return tree_;
}

QHash<QString, StorageTreeNode> StorageTree::structureData() const
{
    return nodes_;
}
