#include "StorageTreeNode.h"

bool StorageTreeNode::operator <=(const StorageTreeNode &node) const
{
    return id_ <= node.id_
            && parent_ <= node.parent_
            && level_ <= node.level_
            && balance_ <= node.balance_
            && expense_ <= node.expense_ ;
}

QJsonObject StorageTreeNode::toJSON() const
{
    QJsonObject json;
    json.insert("id" + QString(":"),id());
    json.insert("balance" + QString(":"), getBalance());
    json.insert("expense" + QString(":"), getExpence());
    return json;
}

