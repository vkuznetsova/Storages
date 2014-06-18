#include "StorageTreeNode.h"

QJsonObject StorageTreeNode::toJSON() const
{
    QJsonObject json;
    json.insert("id" + QString(":"),id());
    json.insert("balance" + QString(":"), getBalance());
    json.insert("expense" + QString(":"), getExpence());
    return json;
}
