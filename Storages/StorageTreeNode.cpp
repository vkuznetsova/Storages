#include "StorageTreeNode.h"

const QString StorageTreeNode::idKey = "id";
const QString StorageTreeNode::balanceKey = "balance";
const QString StorageTreeNode::expenseKey = "expense";

QJsonObject StorageTreeNode::toJSON() const
{
    QJsonObject json;
    json.insert(idKey,id());
    json.insert(balanceKey, getBalance());
    json.insert(expenseKey, getExpence());
    return json;
}
