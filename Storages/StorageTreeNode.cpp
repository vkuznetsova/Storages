#include "StorageTreeNode.h"

const QString StorageTreeNode::idKey = "id";
const QString StorageTreeNode::balanceKey = "balance";
const QString StorageTreeNode::expenseKey = "expense";
const QString StorageTreeNode::deliveryTimeKey = "deliveryTime";

bool StorageTreeNode::operator >=(const StorageTreeNode &node) const
{
    return  level_ >= node.level_
            && balance_ >= node.balance_
            && expense_ >= node.expense_ ;
}

QJsonObject StorageTreeNode::toJSON() const
{
    QJsonObject json;
    json.insert(idKey,id());
    json.insert(balanceKey, getBalance());
    json.insert(expenseKey, getExpence());
    json.insert(deliveryTimeKey, getDeliveryTime());
    return json;
}
