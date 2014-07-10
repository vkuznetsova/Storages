#include "StorageDatabaseReader.h"

StorageDatabaseReader::StorageDatabaseReader()
{
}

StorageDatabaseReader::StorageDatabaseReader(const QString &dataBaseName):
    StorageDatabaseInterface(dataBaseName)
{
}

StorageTree StorageDatabaseReader::read(const QString &idTree)
{
    if(idTree.isNull())
    {
        return StorageTree();
    }

    StorageTree tree = StorageTree(idTree);
    QSqlQuery query(database());
    query.prepare("SELECT parent, child, balance, expense, deliveryTime FROM nodes INNER JOIN trees"
                  " ON nodes.id = trees.child WHERE trees.id = :id");
    query.bindValue(":id", idTree);

    if(!query.exec())
    {
        qDebug()<<"Запрос для соединенных таблиц не выполнен.....";
    }
    checkLastError(query);
    while(query.next())
    {
        const QString parent = query.value(0).toString();
        const QString child = query.value(1).toString();
        const int balance = query.value(2).toInt();
        const int expense = query.value(3).toInt();
        const int deliveryTime = query.value(4).toInt();

        tree.addChild(parent, child);
        tree.setBalance(child, balance);
        tree.setExpense(child, expense);
        tree.setDeliveryTime(child, deliveryTime);
    }
    tree.autoSetRoot();
    tree.autoSetLevel();

    return tree;
}

QList<QString> StorageDatabaseReader::readID()
{
    QList<QString> ids;
    QSqlQuery queryID(database());
    queryID.prepare("select distinct id from trees order by id asc");
    if(!queryID.exec())
    {
        qWarning()<<"Запрос для выборки всех id деревьев не выполнен.....";
    }
    checkLastError(queryID);
    while(queryID.next())
    {
        ids << queryID.value(0).toString();
    }
    return ids;
}

void StorageDatabaseReader::writeToFile(const QString &fileName)
{
    QFile file(fileName);
    if(!file.open(QIODevice::WriteOnly))
    {
        qWarning() << QObject::tr("Ошибка открытия файла для записи..");
        return;
    }
    QList<QString> allID = StorageDatabaseReader::readID();
    QJsonObject obj;
    QJsonArray nodes;
    QJsonArray graphs;
    QHash<QString, QJsonValue> nodesHash;
    for(int i = 0; i < allID.count(); i++)
    {
        StorageTree tree = StorageDatabaseReader::read(allID[i]);
        QJsonObject jsonGraph = tree.toJSON();
        QJsonArray nodeArray = jsonGraph.value(StorageTree::nodesKey).toArray();
        for(int j = 0; j < nodeArray.size(); j++)
        {
            const QJsonObject node = nodeArray[j].toObject();
            nodesHash.insert(node.value(StorageTreeNode::idKey).toString(), QJsonValue(node));
        }
        graphs.append(jsonGraph.value(StorageTree::graphsKey));
    }
    foreach (const QString &nodeID, nodesHash.keys())
    {
        nodes.append(nodesHash.value(nodeID));
    }
    obj.insert(StorageTree::nodesKey, nodes);
    obj.insert(StorageTree::graphsKey, graphs);
    QJsonDocument doc = QJsonDocument(obj);
    QByteArray data = doc.toJson();
    file.write(data);
    file.close();
}
